import React, {useEffect, useState} from "react";
import {Button, ButtonGroup} from "reactstrap";
import {useParams} from "react-router-dom";
import "../styles/StudentList.css";
import {subjectService} from "../services/subjectService";
import StudentCard from "../components/StudentCard";
import _ from 'lodash';


export default function StudentList() {
    const {subject_id} = useParams();
    const [view, setView] = useState("list");
    const [students, setStudents] = useState([]);
    const [isModified, setIsModified] = useState(false);

    const [updatedStudents, setUpdatedStudents] = useState([]);

    useEffect(() => {
        fetchStudentsBySubject()
            .catch(error => console.error('Error getting data:', error));
    }, [subject_id]);

    async function fetchStudentsBySubject() {
        try {
            const fetchedStudents = await subjectService.getStudentsBySubject(subject_id);
            fetchedStudents.sort((a, b) => a.id - b.id);
            setStudents(fetchedStudents);
            setUpdatedStudents([...fetchedStudents])
        } catch (error) {
            console.error('Error fetching Students:', error);
        }
    }

    const handleStudentDataChange = (studentId, updatedStudentData) => {
        setUpdatedStudents(prevStudents => {
            if ( prevStudents.length === 0 ){
                prevStudents = students;
            }

            const studentIndex = prevStudents?.findIndex(student => student.id === studentId);
            if (studentIndex !== -1) {
                const classPerformanceIndex = prevStudents[studentIndex].performances?.findIndex(performance => performance.classes === updatedStudentData.classes);
                if (classPerformanceIndex !== -1) {
                    const isPerformanceModified = !_.isEqual(prevStudents[studentIndex].performances[classPerformanceIndex], updatedStudentData);
                    if (isPerformanceModified) {
                        let newUpdatedStudents = [...prevStudents];
                        newUpdatedStudents[studentIndex].performances[classPerformanceIndex] = updatedStudentData;
                        setIsModified(true);
                        return newUpdatedStudents;
                    }
                } else {
                    if (updatedStudentData.interpretation === null && updatedStudentData.autonomy === null && updatedStudentData.interventions === null) {
                        return prevStudents;
                    }
                    if (updatedStudentData.interpretation !== null || updatedStudentData.autonomy !== null || updatedStudentData.interventions !== null) {
                        let newUpdatedStudents = [...prevStudents];
                        newUpdatedStudents[studentIndex].performances.push(updatedStudentData);
                        setIsModified(true);
                        return newUpdatedStudents;
                    }
                }
            }
            return prevStudents;
        });
    };

    const handleSave = () => {
        setStudents(updatedStudents);
        setIsModified(false);
        console.log(JSON.stringify(updatedStudents));
        subjectService.postStudentsBySubject(subject_id, updatedStudents)
            .then(response => {
                console.log(response);
            })
            .then(refresh => fetchStudentsBySubject())
            .catch(error => {
                console.error('Error:', error);
            });
        //window.location.reload()
    };

    return (
        <div className="studentList">
            <h3>Students</h3>
            <div className="studentListSaveContainer">
                {isModified && <Button onClick={handleSave}>Save</Button>}
            </div>
            <ButtonGroup>
                <ButtonGroup>
                    <Button
                        color="primary"
                        onClick={() => setView("list")}
                        active={view === "list"}
                    >
                        List
                    </Button>
                    <Button
                        color="primary"
                        onClick={() => setView("grid")}
                        active={view === "grid"}
                    >
                        Grid
                    </Button>
                </ButtonGroup>
            </ButtonGroup>

            <div className={view}>
                {students.length === 0 ? (
                    <p>No students assigned.</p>
                ) : (
                    students.map((student) => (
                        <StudentCard key={student.id} student={student} onStudentDataChange={handleStudentDataChange}/>
                    )))}
            </div>
        </div>
    );
}
