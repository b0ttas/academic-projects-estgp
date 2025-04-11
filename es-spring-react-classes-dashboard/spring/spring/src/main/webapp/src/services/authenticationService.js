import {handleResponse} from "../helpers/handleResponse";

//const currentUserSubject = new BehaviorSubject(JSON.parse(localStorage.getItem('currentUser')));
let currentUser = JSON.parse(localStorage.getItem('currentUser'));
let currentUserChangeCallbacks = [];
export const authenticationService = {
    login,
    register,
    logout,
    //currentUser: currentUserSubject.asObservable(),
    //get currentUserValue () { return currentUserSubject.value }
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
function login(username, password) {
    const requestOptions = {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({ username, password })
    };

    return fetch(`/api/login`, requestOptions)
        .then(handleResponse)
        .then(response => {
            localStorage.setItem('currentUser', JSON.stringify(response));
            localStorage.setItem('token', response.token);
            currentUser = response;
            notifyCurrentUserChange();
            return response;
        });
}

function register(username, password) {
    const requestOptions = {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({ username, password })
    };

    return fetch(`/api/register`, requestOptions)
        .then(handleResponse)
        .then(response => {
            localStorage.setItem('currentUser', JSON.stringify(response));
            localStorage.setItem('token', response.token);
            currentUser = response;
            notifyCurrentUserChange();
            return response;
        });
}

function logout() {
    //localStorage.removeItem('currentUser');
    //localStorage.removeItem('token');
    localStorage.clear();
    currentUser = null;
    notifyCurrentUserChange();
}