import "../styles/Home.css";
//import Header from "../components/Header";
//import Footer from "../components/Footer";
//import Login from './LogIn.js';
//import Register from './Register.js';
import {useNavigate} from "react-router-dom";
import {authenticationService} from '../services/authenticationService';
import AuthenticatedHomeContent from "./AuthenticatedHomeContent";

export default function App() {
    const isUserAuth = authenticationService.currentUserValue || false;
    const navigate = useNavigate();

    const navigateLogin = () => {
        navigate("/signin");
    };
    const navigateRegister = () => {
        navigate("/signup");
    };

    function Content() {
        if (!isUserAuth === false) {
            return (
                <AuthenticatedHomeContent/>
            );
        } else {
            return (
                <div>
                    <p>Do you have an account?</p>
                    <button onClick={navigateLogin} type="button">
                        Login
                    </button>
                    <p>or</p>
                    <button onClick={navigateRegister} type="button">
                        Register
                    </button>
                </div>
            );
        }
    }

    return (
        <div className="App">
            <div className="flex-container">
                <div className="flex-item">
                    <h1>Sistema de Controlo de Presenças e Participações</h1>
                </div>
                <div className="flex-item">
                    <Content/>
                </div>
            </div>
        </div>
    );
}
