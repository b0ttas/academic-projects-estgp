import React, {useState} from "react";
import '../styles/Register.css'
import {authenticationService} from "../services/authenticationService";

export default function App() {
    const [isSubmitted, setIsSubmitted] = useState(false);
    const [status, setStatus] = useState("");
    const [username, setUsername] = useState("");
    const [password, setPassword] = useState("");
    const [confirmPassword, setConfirmPassword] = useState("");
    const handleSubmit = async (event) => {
        //Prevent page reload
        event.preventDefault();

        if (password !== confirmPassword) {
            setStatus("Passwords do not match");
        } else {
            try {
                const user = await authenticationService.register(username, password);

                if (user) {
                    setIsSubmitted(true);
                }
            } catch (error) {
                if (error && error.startsWith("message: ")) {
                    setStatus(error.substring("message: ".length));
                } else {
                    setStatus("Registration failed");
                }
            }
        }
    };

    const renderForm = (
        <div className="register-form-group">
            <img
                src="//ssl.gstatic.com/accounts/ui/avatar_2x.png"
                alt="profile-img"
                className="profile-img-card"
            />

            <form className={status ? 'error' : ''} onSubmit={handleSubmit}>
                <div className="input-container">
                    <label>Username:</label>
                    <input type="text" name="uname" required onChange={e => setUsername(e.target.value)}/>
                </div>
                <div className="input-container">
                    <label>Password:</label>
                    <input type="password" name="pass" required onChange={e => setPassword(e.target.value)}/>
                </div>
                <div className="input-container">
                    <label>Confirm Password:</label>
                    <input type="password" name="confirmPass" required
                           onChange={e => setConfirmPassword(e.target.value)}/>
                </div>
                <div className="button-container">
                    <button className="submit" value="Register">Register</button>
                </div>
                {status && <div className={'alert alert-danger'}>{status}</div>}
            </form>
        </div>
    );

    return (
        <div className="register">
            <div className="register-card">
                {isSubmitted ? <div>User is successfully created</div> : renderForm}
            </div>
        </div>
    );
}