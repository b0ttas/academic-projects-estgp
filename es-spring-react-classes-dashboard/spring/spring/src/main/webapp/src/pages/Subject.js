import React, {useEffect, useState} from 'react';
import {useNavigate, useParams} from 'react-router-dom';
import {subjectService} from '../services/subjectService';
import {classesService} from "../services/classesService";
import Modal from 'react-modal';
import {authenticationService} from "../services/authenticationService";

import '../styles/Subject.css'

export default function Subject() {
    const {subject_id} = useParams(); // Get the subject_id from the URL
    const [subject, setSubject] = useState(null);
    const [classes, setClasses] = useState(null);
    const [modalIsOpen, setModalIsOpen] = useState(false);
    const [classDate, setClassDate] = useState('');
    //const [classId, setClassId] = useState('');
    const navigate = useNavigate();
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

        async function fetchClasses() {
            try {
                const fetchedClasses = await classesService.get(subject_id);
                fetchedClasses.sort((a, b) => a.id - b.id);
                setClasses(fetchedClasses);
            } catch (error) {
                console.error('Error fetching Classes:', error);
            }
        }

        fetchSubject()
            .then(fetchClasses) // Fetch classes after subject is fetched
            .catch(error => console.error('Error getting data:', error));
    }, [subject_id]);

    if (!subject) {
        return (
            <div className="App">
                <div className="flex-container">Loading...</div>
            </div>
        );
    }

    function convertDate(inputDate) {
        let date = new Date(inputDate);
        let day = date.getDate();
        let month = date.getMonth() + 1;
        let year = date.getFullYear();

        // Ensure day and month are 2 digits
        day = day < 10 ? '0' + day : day;
        month = month < 10 ? '0' + month : month;

        return `${day}-${month}-${year}`;
    }

    const handleButtonClick = (class_id) => {
        console.log(`Button clicked for class with ID: ${class_id}`);
        navigate(`/subjects/${subject_id}/classes/${class_id}`);
    };

    const handleSubmit = async (event) => {
        event.preventDefault();

        const classData = {
            date: classDate,
        };

        try {
            await classesService.post(subject_id, classData);
            window.location.reload();
        } catch (error) {
            console.error('Error creating class', error);
        }
        setModalIsOpen(false);
    };

    return (
        <div className="App">
            <div className="flex-container">
                <h1>{subject.name}</h1>
                <p>{subject.description}</p>
                {currentUser.role === 'ROLE_TEACHER' || 'ROLE_ADMIN' ? (
                    <div>
                        <button onClick={() => setModalIsOpen(true)}>Create Class</button>
                        <Modal isOpen={modalIsOpen} onRequestClose={() => setModalIsOpen(false)} className="modal"
                               overlayClassName="overlay">
                            <div className="flex-container">
                                <h2>Create Class</h2>
                                <form onSubmit={handleSubmit}>
                                    <label> Date:</label>
                                    <input type="date" value={classDate}
                                           onChange={(e) => setClassDate(e.target.value)}
                                           required/>
                                    <button type="submit">Submit</button>
                                    <button onClick={() => setModalIsOpen(false)}>Close</button>
                                </form>
                            </div>
                        </Modal>
                    </div>
                ) : null}
                <div className="classesGrid">
                    {classes === null ? null : (classes.length === 0 ?
                        (<p>No classes assigned.</p>) :
                        (<div>
                            <p>Classes:</p>
                            {classes.map((classes) => (
                                <button className="subjectsButton"
                                        key={classes.id}
                                        onClick={() => handleButtonClick(classes.id)}>
                                    {classes.id} - {convertDate(classes.date)}
                                </button>
                            ))}
                        </div>))}
                </div>
            </div>
        </div>
    );
}
