import {handleResponse} from "../helpers/handleResponse";

//const currentUserSubject = new BehaviorSubject(JSON.parse(localStorage.getItem('currentUser')));
let currentUser = JSON.parse(localStorage.getItem('currentUser'));
let currentUserChangeCallbacks = [];
export const subjectService = {
    get,
    getSubject,
    //currentUser: currentUserSubject.asObservable(),
    //get currentUserValue () { return currentUserSubject.value }
    currentUser: currentUser,
    get currentUserValue () { return currentUser },
    onCurrentUserChange: (callback) => currentUserChangeCallbacks.push(callback),
    removeCurrentUserChangeCallback: (callback) => {
        currentUserChangeCallbacks = currentUserChangeCallbacks.filter(cb => cb !== callback);
    },
    getStudentsBySubject,
    postStudentsBySubject,
};
function notifyCurrentUserChange() {
    currentUserChangeCallbacks.forEach(callback => callback(currentUser));
}
function get(user_id) {
    const requestOptions = {
        method: 'GET',
        headers: {
            'Content-Type': 'application/json',
            'Authorization': 'Bearer ' + localStorage.getItem('token')
        }
    };

    return fetch(`/api/users/${user_id}/subjects`, requestOptions)
        .then(handleResponse)
        .then(subjects => {
            localStorage.setItem('subjects', JSON.stringify(subjects));
            return subjects;
        });
}

function getSubject(subject_id) {
    const requestOptions = {
        method: 'GET',
        headers: {
            'Content-Type': 'application/json',
            'Authorization': 'Bearer ' + localStorage.getItem('token')
        }
    };

    return fetch(`/api/subjects/${subject_id}`, requestOptions)
        .then(handleResponse)
        .then(subject => {
            localStorage.setItem('subjects', JSON.stringify(subject));
            return subject;
        });
}
function getStudentsBySubject(subject_id) {
    const requestOptions = {
        method: 'GET',
        headers: {
            'Content-Type': 'application/json',
            'Authorization': 'Bearer ' + localStorage.getItem('token')
        }
    };

    return fetch(`/api/subjects/${subject_id}/users`, requestOptions)
        .then(handleResponse)
        .then(students => {
            localStorage.setItem('students', JSON.stringify(students));
            return students;
        });
}
function postStudentsBySubject(subject_id, students) {
    //let students = localStorage.getItem('students');
    //students = students ? JSON.parse(students) : [];

    const requestOptions = {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json',
            'Authorization': 'Bearer ' + localStorage.getItem('token')
        },
        body: JSON.stringify(students)
    };

    return fetch(`/api/subjects/${subject_id}/users`, requestOptions)
        .then(handleResponse)
        .then(response => {
            // nothing to do
        });
}
