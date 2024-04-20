import './Navbar.css';
import { NavLink} from "react-router-dom"
export default function Navbar(){
  return (
    <div className="navbar-cont">
        <div className='navbar-info-cont'>
            <h1>EDW Project</h1>
        </div>
        <div className='navbar-links-cont'>
            <NavLink to={'/'} className='navbar-link'>Home</NavLink>
            <NavLink to={'/info'} className='navbar-link'>Info</NavLink>
        </div>    
    </div>
  )
};
