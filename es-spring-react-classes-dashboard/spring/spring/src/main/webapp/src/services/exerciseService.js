import {handleResponse} from "../helpers/handleResponse";

//const currentUserSubject = new BehaviorSubject(JSON.parse(localStorage.getItem('currentUser')));
let currentUser = JSON.parse(localStorage.getItem('currentUser'));
let currentUserChangeCallbacks = [];
export const subjectService = {
    get,
    getExercise,
    //currentUser: currentUserExercise.asObservable(),
    //get currentUserValue () { return currentUserExercise.value }
    currentUser: currentUser,
    get currentUserValue () { return currentUser },
    onCurrentUserChange: (callback) => currentUserChangeCallbacks.push(callback),
    removeCurrentUserChangeCallback: (callback) => {
        currentUserChangeCallbacks = currentUserChangeCallbacks.filter(cb => cb !== callback);
    },
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

    return fetch(`/api/users/${user_id}/exercises`, requestOptions)
        .then(handleResponse)
        .then(exercises => {
            localStorage.setItem('exercises', JSON.stringify(exercises));
            return exercises;
        });
}

function getExercise(subject_id) {
    const requestOptions = {
        method: 'GET',
        headers: {
            'Content-Type': 'application/json',
            'Authorization': 'Bearer ' + localStorage.getItem('token')
        }
    };

    return fetch(`/api/exercises/${subject_id}`, requestOptions)
        .then(handleResponse)
        .then(exercise => {
            localStorage.setItem('exercises', JSON.stringify(exercise));
            return exercise;
        });
}