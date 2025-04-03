import React, {useEffect, useState} from 'react';
//import { Routes, Route } from "react-router-dom";
import {BrowserRouter as Router, Route, Routes} from 'react-router-dom';
import './styles/App.css';
import Header from './components/Header';
import Footer from './components/Footer';
import Home from './pages/Home';
import SignIn from './pages/LogIn';
import SignUp from './pages/Register';
import Subject from './pages/Subject';
import Classes from './pages/Classes';
import AdminDashboard from './pages/AdminDashboard';
import StudentList from './components/StudentList';

import {useCookies} from "react-cookie";
import {PrivateRoute} from "./components/PrivateRoute";
import {authenticationService} from "./services/authenticationService";
import {Role} from "./helpers/Role";
import StudentDetails from "./pages/StudentDetails";


export default function App() {
    const [cookies, setCookie, removeCookie] = useCookies(["user"]);
    const isLoggedIn = cookies?.user || false;

    const [currentUser, setCurrentUser] = useState(null);
    const [isAdmin, setIsAdmin] = useState(false);

    const updateCurrentUser = (x) => {
        setCurrentUser(x);
        setIsAdmin(x && x.role === Role.Admin);
    };

    useEffect(() => {
        authenticationService.onCurrentUserChange(updateCurrentUser);
        // Cleanup function
        return () => {
            authenticationService.removeCurrentUserChangeCallback(updateCurrentUser);
        };
    }, []);

    return (
        <div className="wrapper">
            <Router>
                <Header/>
                <Routes>
                    <Route path="/" element={<Home/>}/>
                    <Route path="/signIn" element={<SignIn/>}/>
                    <Route path="/signup" element={<SignUp/>}/>
                    <Route exact path='/' element={<PrivateRoute/>}>
                        <Route path="subjects/:subject_id" element={<Subject/>}/>
                        <Route path="subjects/:subject_id/classes/:class_id" element={<Classes/>}/>
                        <Route path="subjects/:subject_id/classes/:class_id/student/:student_id" element={<StudentDetails/>}/>
                    </Route>
                    <Route exact path='/' element={<PrivateRoute roles={3}/>}>
                        <Route path="admin" element={<AdminDashboard/>}/>
                    </Route>
                    <Route path="/*" element={<Home/>}/>
                </Routes>
                <Footer/>
            </Router>
        </div>
    );
}