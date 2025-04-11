import React from 'react';
import {Navigate, Outlet} from 'react-router-dom';
import {authenticationService} from '../services/authenticationService';

export const PrivateRoute = ({roles, children}) => {
    const isUserAuth = authenticationService.currentUserValue || false;

    // check if route is restricted by role
    if (isUserAuth && isUserAuth.role.id === -1) {
        // role not authorised so redirect to home page
        return <Navigate to={{pathname: '/'}}/>
    }

    if (roles && isUserAuth && isUserAuth.role.id !== roles) {
        return <Navigate to={{pathname: '/'}}/>
    }

    // If authorized, return an outlet that will render child elements
    // If not, return element that will navigate to login page
    return isUserAuth ? <Outlet/> : <Navigate to="/signIn" state={{fromPrivate: true}}/>;
}