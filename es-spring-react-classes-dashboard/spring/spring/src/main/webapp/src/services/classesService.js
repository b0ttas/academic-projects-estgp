import {handleResponse} from "../helpers/handleResponse";

export const classesService = {
    get,
    post,
};

function get(subject_id) {
    const requestOptions = {
        method: 'GET',
        headers: {
            'Content-Type': 'application/json',
            'Authorization': 'Bearer ' + localStorage.getItem('token')
        }
    };

    return fetch(`/api/subjects/${subject_id}/classes`, requestOptions)
        .then(handleResponse)
        .then(classes => {
            localStorage.setItem('classes', JSON.stringify(classes));
            return classes;
        });

}

function post(subject_id, classData) {
    const requestOptions = {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json',
            'Authorization': 'Bearer ' + localStorage.getItem('token')
        },
        body: JSON.stringify(classData)
    };

    return fetch(`/api/subjects/${subject_id}/classes`, requestOptions)
        .then(handleResponse)
}