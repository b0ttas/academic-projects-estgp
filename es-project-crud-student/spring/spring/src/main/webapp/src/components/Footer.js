import '../styles/Footer.css'
import logoIPPBranco from '../resources/logoIPPBranco.png';
import {useNavigate} from 'react-router-dom';


export default function Footer() {
    const navigate = useNavigate();

    function goHome() {
        navigate("/");
    }

    return (
        <footer className='footer'>
            <img className='logoFooter' src={logoIPPBranco} onClick={goHome} alt="Logo"/>
        </footer>
    )
}