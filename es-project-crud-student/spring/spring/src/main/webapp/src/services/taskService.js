import {handleResponse} from "../helpers/handleResponse";

//const currentUserTask = new BehaviorTask(JSON.parse(localStorage.getItem('currentUser')));
let currentUser = JSON.parse(localStorage.getItem('currentUser'));
let currentUserChangeCallbacks = [];
export const taskService = {
    get,
    getTask,
    //currentUser: currentUserTask.asObservable(),
    //get currentUserValue () { return currentUserTask.value }
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

    return fetch(`/api/users/${user_id}/tasks`, requestOptions)
        .then(handleResponse)
        .then(tasks => {
            localStorage.setItem('tasks', JSON.stringify(tasks));
            return tasks;
        });
}

function getTask(task_id) {
    const requestOptions = {
        method: 'GET',
        headers: {
            'Content-Type': 'application/json',
            'Authorization': 'Bearer ' + localStorage.getItem('token')
        }
    };

    return fetch(`/api/tasks/${task_id}`, requestOptions)
        .then(handleResponse)
        .then(task => {
            localStorage.setItem('tasks', JSON.stringify(task));
            return task;
        });
}