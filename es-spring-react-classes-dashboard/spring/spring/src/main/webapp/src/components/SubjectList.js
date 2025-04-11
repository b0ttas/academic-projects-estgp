import '../styles/SubjectList.css'
import React, {useState, useEffect} from 'react';
import {subjectService} from '../services/subjectService';
import {useNavigate} from "react-router-dom";

export default function SubjectList({userId}) {
    const [subjects, setSubjects] = useState([]);
    const navigate = useNavigate();

    useEffect(() => {
        async function fetchSubjects() {
            try {
                const userSubjects = await subjectService.get(userId);
                userSubjects.sort((a, b) => a.name.localeCompare(b.name));
                setSubjects(userSubjects);
            } catch (error) {
                console.error('Error fetching subjects:', error);
            }
        }

        fetchSubjects()
            .catch(error => console.error('Error getting SubjectList:', error));
    }, [userId]);

    const handleButtonClick = (id) => {
        console.log(`Button clicked for subject with ID: ${id}`);
        navigate(`/subjects/${id}`);
    };

    return (
        <div className="subjectsGrid">
            {subjects.length === 0 ? (
                <p>No subjects assigned.</p>
            ) : (
                subjects.map((subject) => (
                            <button className="subjectsButton"
                                    key={subject.id}
                                    onClick={() => handleButtonClick(subject.id)}>
                                {subject.name}
                            </button>
                    )
                )
            )}
        </div>
    )
        ;
}