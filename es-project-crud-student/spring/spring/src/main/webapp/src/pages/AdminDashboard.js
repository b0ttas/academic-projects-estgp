import React, {useEffect, useState} from 'react';
import "../styles/AdminDashboard.css";
import Modal from "react-modal";
import {classesService} from "../services/classesService";
import {adminService} from "../services/adminService";


export default function AdminDashboard() {
    const [users, setUsers] = useState([]);
    const [subjects, setSubjects] = useState([]);
    const [classes, setClasses] = useState([]);
    const [usersSubjects, setUserSubjects] = useState([]);
    const [currentData, setCurrentData] = useState([]);

    const [selectedEntity, setSelectedEntity] = useState('users');
    const [refreshData, setRefreshData] = useState(false);

    const [modalIsOpen, setModalIsOpen] = useState(false);

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

    const getInitialModalState = (selectedEntity) => {
        switch (selectedEntity) {
            case 'users':
                return {
                    id: '',
                    username: '',
                    password: '',
                    firstName: '',
                    lastName: '',
                    email: '',
                    role: {id: ''}
                };
            case 'subjects':
                return {
                    id: '',
                    name: '',
                };
            case 'classes':
                return {
                    id: '',
                    date: '',
                    subject_id: '',
                };
            case 'user_subject':
                return {
                    id: '',
                    username: '',
                    password: '',
                    firstName: '',
                    lastName: '',
                    email: '',
                    role: {id: ''},
                    subjects: {id: ''}
                };
            default:
                return {};
        }
    };
    const [modalData, setModalData] = useState(getInitialModalState(selectedEntity));

    useEffect(() => {
        setCurrentData(users);
    }, [users]);

    useEffect(() => {
        setCurrentData(subjects);
    }, [subjects]);

    useEffect(() => {
        setCurrentData(classes);
    }, [classes]);

    useEffect(() => {
        setCurrentData(usersSubjects);
    }, [usersSubjects]);

    useEffect(() => {
        setRefreshData(false)
        switch (selectedEntity) {
            case 'users':
                const fetchUsers = async () => {
                    const data = await adminService.getUsers();
                    setUsers(data);
                    //setCurrentData(users)
                }
                fetchUsers()
                    .catch(error => console.error('Error getting data:', error))
                return;
            case 'subjects':
                const fetchSubjects = async () => {
                    const data = await adminService.getSubjects();
                    setSubjects(data);
                    //setCurrentData(subjects);
                }
                fetchSubjects().catch(error => console.error('Error getting data:', error));
                return;
            case 'classes':
                const fetchClasses = async () => {
                    if (modalData?.subject_id) {
                        const modalClassData = await classesService.get(modalData.subject_id);
                        setClasses(modalClassData);
                    }
                    const subjects = await adminService.getSubjects();
                    setSubjects(subjects);
                }
                fetchClasses().catch(error => console.error('Error getting data:', error));
                return;
            case 'user_subject':
                const fetchUserSubjects = async () => {
                    const subjects = await adminService.getSubjects();
                    setSubjects(subjects);
                    const users = await adminService.getUsers()
                    setUsers(users);
                }
                fetchUserSubjects().catch(error => console.error('Error getting data:', error));
                return;
        }
    }, [selectedEntity, refreshData, modalData?.subject_id]);

    const handleSubmit = async (event) => {
        event.preventDefault();
        try {
            switch (selectedEntity) {
                case 'users':
                    await adminService.postUser(modalData);
                    setModalIsOpen(false);
                    break;
                case 'subjects':
                    await adminService.postSubject(modalData);
                    setModalIsOpen(false);
                    break;
                case 'classes':
                    await classesService.post(modalData?.subject_id, modalData);
                    break;
            }
            setRefreshData(true)
        } catch (error) {
            console.error('Error creating class', error);
        }
    };
    const handleCreateAndEdit = (item) => {
        let modalTemp = getInitialModalState(selectedEntity);

        if (item) {
            let matchingKeys = []
            switch (selectedEntity) {
                case 'users':
                    // "password",
                    matchingKeys = ["id", "username", "firstName", "lastName", "email", "role"];
                    break;
                case 'subjects':
                    matchingKeys = ["id", "name"];
                    break;
                case 'classes': //id
                    matchingKeys = ["id", "date"];
                    break;
                case 'user_subject':
                    matchingKeys = ["id", "username", "firstName", "lastName", "email", "role", "subjects"];
                    break;
                default: //id
                    return;
            }

            for (const key of matchingKeys) {
                if (item.hasOwnProperty(key) && modalTemp.hasOwnProperty(key)) {
                    modalTemp[key] = item[key];
                    if (selectedEntity === 'classes') {
                        modalTemp.id = "";
                        modalTemp.subject_id = item.id;
                    }
                }
            }

            if (selectedEntity === 'user_subject') {
                //modalTemp.subjects = item.subjects.map(subject => subject.id);
                modalTemp.subjects = item.subjects.map((subject) => ({ id: subject.id }));
            }
        }
        setModalData(modalTemp)
        setModalIsOpen(true)
    };

    const handleDelete = (id) => {
        switch (selectedEntity) {
            case 'users':
                const deleteUser = async () => {
                    await adminService.deleteUser(id);
                }
                deleteUser()
                    .catch(error => console.error('Error getting data:', error))
                setRefreshData(true)
                return;
            case 'subjects':
                const deleteSubjects = async () => {
                    await adminService.deleteSubject(id);
                }
                deleteSubjects()
                    .catch(error => console.error('Error getting data:', error))
                setRefreshData(true)
                return;
            case 'classes':
                const deleteClasses = async () => {
                    await adminService.deleteClasses(id);
                }
                deleteClasses()
                    .catch(error => console.error('Error getting data:', error))
                setRefreshData(true)
                return;
            case 'user_subject':
                const deleteUserSubject = async () => {
                    //const data = //await adminService.deleteUserSubject(user_id, class_id); //todo
                }
                deleteUserSubject()
                    .catch(error => console.error('Error getting data:', error))
                setRefreshData(true)
                return;
        }
    };

    const handleEntityChange = (entity) => {
        setSelectedEntity(entity);
    };

    const Table = ({data, handleEdit, handleDelete}) => {
        switch (selectedEntity) {
            case 'users':
                return (
                    <table>
                        <thead>
                        <tr>
                            <th>ID</th>
                            <th>Username</th>
                            <th>First Name</th>
                            <th>Last Name</th>
                            <th>E-Mail</th>
                            <th>Actions</th>
                        </tr>
                        </thead>
                        <tbody>
                        {data.map((item) => (
                            <tr key={item.id}>
                                <td>{item.id}</td>
                                <td>{item.username}</td>
                                <td>{item.firstName}</td>
                                <td>{item.lastName}</td>
                                <td>{item.email}</td>
                                <td>
                                    <button onClick={() => handleEdit(item)}>Edit</button>
                                    <button onClick={() => handleDelete(item.id)}>Delete</button>
                                </td>
                            </tr>
                        ))}
                        </tbody>
                    </table>
                );
            case 'subjects':
                return (
                    <table>
                        <thead>
                        <tr>
                            <th>ID</th>
                            <th>Name</th>
                            <th>Actions</th>
                        </tr>
                        </thead>
                        <tbody>
                        {data ? data.map((item) => (
                            <tr key={item.id}>
                                <td>{item.id}</td>
                                <td>{item.name}</td>
                                <td>
                                    <button onClick={() => handleEdit(item)}>Edit</button>
                                    <button onClick={() => handleDelete(item.id)}>Delete</button>
                                </td>
                            </tr>
                        )) : <p> Loading </p>}
                        </tbody>
                    </table>
                );
            case 'classes':
                return (
                    <table>
                        <thead>
                        <tr>
                            <th>ID</th>
                            <th>Subject</th>
                            <th>Actions</th>
                        </tr>
                        </thead>
                        <tbody>
                        {data.map((item) => (
                            <tr key={item.id}>
                                <td>{item.id}</td>
                                <td>{item.name}</td>
                                <td>
                                    <button onClick={() => handleEdit(item)}>View</button>
                                    {/*<button onClick={() => handleDelete(item.id)}>Delete</button>*/}
                                </td>
                            </tr>
                        ))}
                        </tbody>
                    </table>
                );
            case 'user_subject':
                return (
                    <table>
                        <thead>
                        <tr>
                            <th>ID</th>
                            <th>Username</th>
                            <th>First Name</th>
                            <th>Last Name</th>
                            <th>E-Mail</th>
                            <th>Actions</th>
                        </tr>
                        </thead>
                        <tbody>
                        {data.map((item) => (
                            <tr key={item.id}>
                                <td>{item.id}</td>
                                <td>{item.username}</td>
                                <td>{item.firstName}</td>
                                <td>{item.lastName}</td>
                                <td>{item.email}</td>
                                <td>
                                    <button onClick={() => handleEdit(item)}>Assign</button>
                                    {/*<button onClick={() => handleDelete(item.id)}>Delete</button>*/}
                                </td>
                            </tr>
                        ))}
                        </tbody>
                    </table>
                );
        }
    };

    const Title = ({selectedEntity}) => {
        let titleText;

        switch (selectedEntity) {
            case 'users':
                titleText = "Users";
                break;
            case 'subjects':
                titleText = "Subjects";
                break;
            case 'classes':
                titleText = "Classes";
                break;
            case 'user_subject':
                titleText = "Assign User to Subject";
                break;
            default:
                titleText = "Default Title";
        }

        return <h1>{titleText}</h1>;
    };

    return (
        <div className="admin-content">
            <div>
                <button onClick={() => handleEntityChange('users')}>Users</button>
                <button onClick={() => handleEntityChange('subjects')}>Subjects</button>
                <button onClick={() => handleEntityChange('classes')}>Classes</button>
                <button onClick={() => handleEntityChange('user_subject')}>Assign User to Subject</button>
            </div>

            <div className="admin-content">
                <div className="admin-dashboard-data">
                    <Title selectedEntity={selectedEntity}/>
                    {selectedEntity !== 'user_subject' && selectedEntity !== 'classes' &&
                        <button onClick={() => handleCreateAndEdit()}>Create</button>
                    }
                    <br/>
                    <Table data={currentData} handleEdit={handleCreateAndEdit} handleDelete={handleDelete}/>
                    <Modal isOpen={modalIsOpen} onRequestClose={() => setModalIsOpen(false)} className="modal"
                           overlayClassName="overlay" appElement={document.getElementById('root')}>
                        {selectedEntity === 'users' &&
                            <div className="flex-container">
                                <h2>Create/Update User</h2>
                                <form onSubmit={handleSubmit}>
                                    <label>Username:</label>
                                    <input type="text"
                                           value={modalData?.username}
                                           onChange={(e) => setModalData({...modalData, username: e.target.value})}
                                           required/>
                                    <label>Password:</label>
                                    <input type="password"
                                           value={modalData?.password}
                                           onChange={(e) => setModalData({...modalData, password: e.target.value})}
                                           required/>

                                    <label>First Name:</label>
                                    <input type="text"
                                           value={modalData?.firstName}
                                           onChange={(e) => setModalData({...modalData, firstName: e.target.value})}
                                           required/>

                                    <label>Last Name:</label>
                                    <input type="text"
                                           value={modalData?.lastName}
                                           onChange={(e) => setModalData({...modalData, lastName: e.target.value})}
                                           required/>

                                    <label>Email:</label>
                                    <input type="email"
                                           value={modalData?.email}
                                           onChange={(e) => setModalData({...modalData, email: e.target.value})}
                                           required/>

                                    <label>Role ID:</label>
                                    <input type="number"
                                           value={modalData?.role?.id}
                                           onChange={(e) => setModalData({...modalData, role: {id: e.target.value}})}
                                           required/>

                                    <button type="submit">Submit</button>
                                    <button type="button" onClick={() => setModalIsOpen(false)}>Close</button>
                                </form>
                            </div>
                        }
                        {selectedEntity === 'subjects' &&
                            <div className="flex-container">
                                <h2>Create/Update Subject</h2>
                                <form onSubmit={handleSubmit}>
                                    <label>Name:</label>
                                    <input type="text"
                                           value={modalData?.name}
                                           onChange={(e) => setModalData({...modalData, name: e.target.value})}
                                           required/>

                                    <button type="submit">Submit</button>
                                    <button type="button" onClick={() => setModalIsOpen(false)}>Close</button>
                                </form>
                            </div>
                        }
                        {selectedEntity === 'classes' &&
                            <div className="flex-container">
                                <h2>Manage
                                    Classes</h2>                                    {classes === null ? null : (classes.length === 0 ?
                                (<p>No classes assigned.</p>) :
                                (<div>
                                    <p>Classes: (click to delete)</p>
                                    {classes.map((classes) => (
                                        <button className="subjectsButton"
                                                key={classes.id}
                                                onClick={() => handleDelete(classes.id)}>
                                            {classes.id} - {convertDate(classes.date)}
                                        </button>
                                    ))}
                                </div>))}
                                <form onSubmit={handleSubmit}>
                                    <p>Create</p>
                                    <label>Date:</label>
                                    <input type="date"
                                           value={modalData?.date}
                                           onChange={(e) => setModalData({...modalData, date: e.target.value})}
                                           required/>
                                    <button type="submit">Create</button>
                                    <button type="button" onClick={() => setModalIsOpen(false)}>Close</button>
                                </form>
                            </div>}
                        {selectedEntity === 'user_subject' &&
                            <div className="flex-container">
                                <h2>Subject Assignment</h2>
                                <form onSubmit={handleSubmit}>
                                    {subjects.map((subject) => {
                                        let backgroundColor = usersSubjects?.subjects?.id === subject.id ? "green" : "yellow";
                                        return (
                                            <button className="subjectsButton" style={{ backgroundColor: backgroundColor }}
                                                    key={subject.id}
                                                    onClick={() => handleDelete(subject.id)}>
                                                {subject.name}
                                            </button>
                                        );
                                    })}
                                    <div>
                                        <p></p>
                                        {/*<button type="submit">Submit</button>*/}
                                        <button type="button" onClick={() => setModalIsOpen(false)}>Close</button>
                                    </div>
                                </form>
                            </div>
                        }
                    </Modal>
                </div>
            </div>
        </div>
    );
}