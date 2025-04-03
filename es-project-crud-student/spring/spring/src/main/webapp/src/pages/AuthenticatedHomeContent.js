import {authenticationService} from '../services/authenticationService';
import {subjectService} from '../services/subjectService';
import {Navigate, useNavigate} from "react-router-dom";
import React, {useEffect, useState} from "react";
import SubjectList from "../components/SubjectList";
import AdminDashboard from "./AdminDashboard";

export default function App() {
    const navigate = useNavigate();
    const currentUser = authenticationService.currentUserValue;

    useEffect(() => {
        if (currentUser.role.name === 'ROLE_ADMIN') {
            navigate("/admin");
        }
    }, [currentUser, navigate]);

    function Content() {
        if (!currentUser) {
            return <p>No user is currently authenticated.</p>;
        }
        switch (currentUser.role.name) {
            case 'ROLE_STUDENT':
            case 'ROLE_TEACHER':
                return <SubjectList userId={currentUser.id} />;
            case 'ROLE_ADMIN':
                return;
            default:
                return <p>Roles not maintained. Please contact your systems administrator</p>;
        }
    }

    return (
        <div>
            <p>Welcome, {currentUser.firstName + ' ' + currentUser.lastName}:</p>
            <Content/>
        </div>
    );
}