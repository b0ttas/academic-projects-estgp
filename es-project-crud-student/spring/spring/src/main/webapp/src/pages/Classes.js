import React, {useEffect, useState} from 'react';
import {useParams} from 'react-router-dom';
import {subjectService} from '../services/subjectService';
import StudentList from "../components/StudentList";
import {authenticationService} from "../services/authenticationService";
import StudentDetails from "./StudentDetails";

export default function Classes() {
    const {subject_id} = useParams();
    const [subject, setSubject] = useState(null);
    const currentUser = authenticationService.currentUserValue;

    useEffect(() => {
        async function fetchSubject() {
            try {
                const fetchedSubject = await subjectService.getSubject(subject_id);
                setSubject(fetchedSubject);

            } catch (error) {
                console.error('Error fetching Subject:', error);
            }
        }

        fetchSubject()
            .catch(error => console.error('Error getting data:', error));
    }, [subject_id]);

    if (!subject) {
        return (
            <div className="App">
                <div className="flex-container">Loading...</div>
            </div>
        );
    }


    switch (currentUser.role.name) {
        case 'ROLE_STUDENT':
            return (
                <StudentDetails userId={currentUser.id} />
            );
        case 'ROLE_TEACHER' || 'ROLE_ADMIN':
            return (
                <div className="App">
                    <div className="flex-container">
                        <h1>{subject.name}</h1>
                        <p>{subject.description}</p>
                    </div>
                    <StudentList/>
                </div>
            );
        default:
            return (<p>Roles not maintained. Please contact your systems administrator</p>);
    }
}
