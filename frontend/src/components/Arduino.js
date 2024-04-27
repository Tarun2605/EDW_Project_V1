import { useContext } from 'react';
import { Appcontext } from '../context/AppContext';
import './Arduino.css';
export default function Arduino(){
  const {bootUp} = useContext(Appcontext);
  return (
    <div className='arduino-cont'>
      Arduino
      <div className={bootUp?'arduino-info-cont green': 'arduino-info-cont red'}>
      </div>
    </div>
  )
};
