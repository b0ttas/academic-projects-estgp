import {handleResponse} from "../helpers/handleResponse";

export const adminService = {
    getUsers,
    getSubjects,
    getClasses,
    deleteUser,
    deleteSubject,
    deleteClasses,
    deleteUserSubject,
    postUser,
    postSubject,
    postClasses,
    postUserSubject,
};

function deleteUser(id){
    const requestOptions = {
        method: 'DELETE',
        headers: {
            'Content-Type': 'application/json',
            'Authorization': 'Bearer ' + localStorage.getItem('token')
        }
    };

    return fetch(`/api/users/${id}`, requestOptions)
        .then(handleResponse)
        .then(users => { return users; });
}

function deleteSubject(id){
    const requestOptions = {
        method: 'DELETE',
        headers: {
            'Content-Type': 'application/json',
            'Authorization': 'Bearer ' + localStorage.getItem('token')
        }
    };

    return fetch(`/api/subjects/${id}`, requestOptions)
        .then(handleResponse)
        .then(users => { return users; });
}
function deleteClasses(id){
    const requestOptions = {
        method: 'DELETE',
        headers: {
            'Content-Type': 'application/json',
            'Authorization': 'Bearer ' + localStorage.getItem('token')
        }
    };

    return fetch(`/api/classes/${id}`, requestOptions)
        .then(handleResponse)
        .then(users => { return users; });
}
function deleteUserSubject(user_id, class_id){
    const requestOptions = {
        method: 'GET',
        headers: {
            'Content-Type': 'application/json',
            'Authorization': 'Bearer ' + localStorage.getItem('token')
        }
    };

    return fetch(`/api/users`, requestOptions)
        .then(handleResponse)
        .then(users => { return users; });
}
function getUsers() {
    const requestOptions = {
        method: 'GET',
        headers: {
            'Content-Type': 'application/json',
            'Authorization': 'Bearer ' + localStorage.getItem('token')
        }
    };

    return fetch(`/api/users`, requestOptions)
        .then(handleResponse)
        .then(users => { return users; });
}
function getSubjects() {
    const requestOptions = {
        method: 'GET',
        headers: {
            'Content-Type': 'application/json',
            'Authorization': 'Bearer ' + localStorage.getItem('token')
        }
    };

    return fetch(`/api/subjects`, requestOptions)
        .then(handleResponse)
        .then(subjects => { return subjects; });
}
function getClasses() {
    const requestOptions = {
        method: 'GET',
        headers: {
            'Content-Type': 'application/json',
            'Authorization': 'Bearer ' + localStorage.getItem('token')
        }
    };

    return fetch(`/api/admin/classes`, requestOptions)
        .then(handleResponse)
        .then(classes => { return classes; });
}

function postUser(modalData) {
    const requestOptions = {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json',
            'Authorization': 'Bearer ' + localStorage.getItem('token')
        },
        body: JSON.stringify(modalData)
    };

    return fetch(`/api/users`, requestOptions)
        .then(handleResponse)
}
function postSubject(modalData) {
    const requestOptions = {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json',
            'Authorization': 'Bearer ' + localStorage.getItem('token')
        },
        body: JSON.stringify(modalData)
    };

    return fetch(`/api/subjects`, requestOptions)
        .then(handleResponse)
}
function postClasses(modalData) {
    const requestOptions = {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json',
            'Authorization': 'Bearer ' + localStorage.getItem('token')
        },
        body: JSON.stringify(modalData)
    };

    return fetch(`/api/classes`, requestOptions)
        .then(handleResponse)
}
function postUserSubject(modalData) {
    const requestOptions = {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json',
            'Authorization': 'Bearer ' + localStorage.getItem('token')
        },
        body: JSON.stringify(modalData)
    };

    return fetch(`/api/users`, requestOptions)
        .then(handleResponse)
}