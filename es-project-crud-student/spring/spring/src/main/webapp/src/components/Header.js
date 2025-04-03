import {useNavigate} from 'react-router-dom';
import {useCookies} from 'react-cookie';
import logoIPPCores from '../resources/logoIPPCores.png';
import '../styles/Header.css'
import {authenticationService} from '../services/authenticationService';
export default function Header() {
    const isUserAuth = authenticationService.currentUserValue || false;
    const navigate = useNavigate();
    const [cookies, setCookie, removeCookie] = useCookies(["user"]);

    function goHome() {
        navigate("/");
    }

    function goSignIn() {
        navigate("/signin");
    }

    function goSignUp() {
        navigate("/signup");
    }

    function handleSignOut() {
        authenticationService.logout();
        goHome();
    }

    return (
        <header className='header'>
            <div className='headerButtons'>
                {isUserAuth ? (
                    <a className='signIn' onClick={handleSignOut} type="button">Sign Out</a>
                ) : (
                    <div>
                        <a className='signIn' onClick={goSignIn} type="button">Sign In</a>
                        <button className='signup' onClick={goSignUp} type="button">Sign Up</button>
                    </div>
                )}
            </div>
            <div><img className='logo' src={logoIPPCores} onClick={goHome} alt="Logo"/></div>
        </header>
    )
}