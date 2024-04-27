
import './App.css';
import io from 'socket.io-client';
// import io from "socket.io-client";
// import { useContext, useEffect } from 'react';
import { Routes, Route } from 'react-router';
import { useContext, useEffect } from 'react';
import Home from './pages/Home';
import Navbar from './components/Navbar';
import Arduino from './components/Arduino';
import Info from './pages/Info';
import { Appcontext } from './context/AppContext';
import SocketReciever from './utils/Socket';
import axios from 'axios';
// Rest of the code...


function App() {
  let { setTableTennisTeamA, setTableTennisTeamB, teamWin, selectedGame, setSelectedGame, setTeamWin, BadmintonTeamA, setBadmintonTeamA, BadmintonTeamB, setBadmintonTeamB, HockeyTeamA,
    setHockeyTeamA, HockeyTeamB, setHockeyTeamB, HockeyQuarter, setHockeyQuarter,      HockeyTime, setHockeyTime, HockeyStart, setHockeyStart } = useContext(Appcontext);

        useEffect(() => {
          const fetchAllData = async () => {
            try {
              const response = await axios.get('https://edw-tfub.onrender.com/config/getAllData');
              console.log('Data fetched successfully ', response.data);
            } catch (error) {
              console.log('Error occurred while fetching data ', error.message);
            }
          }
          fetchAllData();
        }, []);
        
  return (
    <>
    <SocketReciever></SocketReciever>
    <div className='page-cont'>
      <Navbar />
      <Routes>
        <Route path='/' element={<Home />} />
        <Route path='/info' element={<Info />} />
      </Routes>
      <Arduino />
    </div>
    </>
  );
}

export default App;
