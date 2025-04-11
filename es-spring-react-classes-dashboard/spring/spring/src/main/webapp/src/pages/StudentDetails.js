import Chart from "../components/Chart";
import '../styles/StudentDetails.css';
import {subjectService} from "../services/subjectService";
import {useEffect, useState} from "react";
import {useParams} from "react-router-dom";

export default function StudentDetails(props) {
    const {subject_id, class_id, student_id} = useParams();
    const [students, setStudents] = useState([]);

    let useruuid;
    student_id === undefined ? useruuid = props.userId : useruuid = student_id;

    useEffect(() => {
        fetchStudentsBySubject()
            .catch(error => console.error('Error getting data:', error));
    }, [subject_id]);

    async function fetchStudentsBySubject() {
        try {
            console.log(subject_id)
            const fetchedStudents = await subjectService.getStudentsBySubject(useruuid);
            setStudents(fetchedStudents);
        } catch (error) {
            console.error('Error fetching Students:', error);
        }
    }

    function getSortedDates(classes) {
        let datesAndIds = classes.map(c => ({id: c.id, date: new Date(c.date).toLocaleString().split(',')[0]}));
        datesAndIds.sort((a, b) => new Date(a.date) - new Date(b.date));
        return datesAndIds;
    }

    function getDisplayData(ordered_classes, performances) {
        if (performances) {
            let classIds = ordered_classes.map(c => c.id);
            let sortedPerformances = [];
            let totalInterpretation = 0;
            let totalAutonomy = 0;
            let totalInterventions = 0;
            let emptyCount = 0;
            for (let id of classIds) {
                let performance = performances.find(obj => obj.classes_id === id);
                if (performance) {
                    sortedPerformances.push(performance);
                    totalInterpretation += performance.interpretation;
                    totalAutonomy += performance.autonomy;
                    totalInterventions += performance.interventions;
                } else {
                    sortedPerformances.push({
                        "id": null,
                        "user_id": null,
                        "classes_id": id,
                        "interpretation": 0,
                        "autonomy": 0,
                        "interventions": 0
                    });
                    emptyCount++;
                }
            }
            let avgInterpretation = totalInterpretation / (sortedPerformances.length - emptyCount);
            let avgAutonomy = totalAutonomy / (sortedPerformances.length - emptyCount);
            let avgInterventions = totalInterventions / (sortedPerformances.length - emptyCount);
            return {
                sortedPerformances,
                avgInterpretation,
                avgAutonomy,
                avgInterventions,
                totalPerformances: sortedPerformances.length,
                emptyCount
            };
        }
    }

    const dates = getSortedDates(JSON.parse(localStorage.getItem('classes')));

    const student = students.find(student => student.id === Number(useruuid));
    const performance = student?.performances.find(item => item.classes_id === Number(class_id));

    const data = getDisplayData(dates, student?.performances);

    if (!student || !performance) {
        return <div className="student-details">Data not found</div>;
    } else {
    }

    return (
        <div className="student-details">
            <h1>
                {student.firstName && student.lastName ?
                    `${student.firstName} ${student.lastName}` : `User ID - ${student.id}`}
            </h1>
            <Chart data={data} dates={dates}></Chart>
            <div className="student-details-container">
                <p>Avg. Autonomy - {data.avgAutonomy} <br/>
                    Avg. Interpretation - {data.avgInterpretation} <br/>
                    Avg. Interventions - {data.avgInterventions} </p>
            </div>
        </div>
    )
}