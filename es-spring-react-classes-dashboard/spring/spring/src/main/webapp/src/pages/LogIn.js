import React, {useState} from "react";
import "../styles/Login.css";
import {useNavigate} from "react-router-dom";
import {useCookies} from "react-cookie";
import {useLocation} from 'react-router-dom';
import {authenticationService} from '../services/authenticationService';

export default function App() {
    const location = useLocation();
    const fromPrivate = location.state?.fromPrivate;
    const [cookies, setCookie, removeCookie] = useCookies(["user"]);
    const [username, setUsername] = useState("");
    const [password, setPassword] = useState("");
    const [status, setStatus] = useState("");
    const navigate = useNavigate();

    const navigateHome = () => {
        navigate("/");
    };

    const handleSubmit = async (event) => {
        event.preventDefault();
        try {
            const user = await authenticationService.login(username, password);

            if (user) {
                navigateHome();
            }
        } catch (error) {
            // Handle login failure
            setStatus("Invalid username or password");
        }
    };

    return (
        <div className="login">
            <div className="card card-container">

                <img
                    src="//ssl.gstatic.com/accounts/ui/avatar_2x.png"
                    alt="profile-img"
                    className="profile-img-card"
                />

                <form className={status ? 'error' : ''} onSubmit={handleSubmit}>
                    <div className="form-group">
                        <label>Username:
                            <br/>
                            <input
                                type="text"
                                id="username"
                                value={username}
                                onChange={(e) => setUsername(e.target.value)}
                            /></label>
                    </div>
                    <div className="form-group">
                        <label>Password:
                            <br/>
                            <input className="form-control"
                                   type="password"
                                   id="password"
                                   value={password}
                                   onChange={(e) => setPassword(e.target.value)}
                            /></label>
                    </div>
                    <div className="form-group">
                        <button className="submit" type="" value="Submit">Submit</button>
                    </div>
                    {status && <div className="alert alert-danger">{status}</div>}
                </form>
            </div>
            <div>
                {fromPrivate && <div className="alert alert-danger">You must sign in to view this page</div>}
            </div>
        </div>
    );
}