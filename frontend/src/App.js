
import './App.css';
import io from 'socket.io-client';
// import io from "socket.io-client";
import { useContext, useEffect } from 'react';
import { Routes, Route } from 'react-router';
import Home from './pages/Home';
import Navbar from './components/Navbar';
import Arduino from './components/Arduino';
import Info from './pages/Info';
import { Appcontext } from './context/AppContext';
// Rest of the code...
var socket;

function App() {
  // const ENDPOINT = 'https://edw-tfub.onrender.com';
  const ENDPOINT = 'http://localhost:5000';
  socket = io(ENDPOINT);
  let { setTableTennisTeamA, setTableTennisTeamB, teamWin, selectedGame, setSelectedGame, setTeamWin, BadmintonTeamA, setBadmintonTeamA, BadmintonTeamB, setBadmintonTeamB, } = useContext(Appcontext);
  useEffect(() => {
    try {
      socket.on('connect', () => {
        console.log('Connected to server');
      });
      socket.on('disconnected', () => {
        console.log('Disconnected from server');
      });
      return () => {
        socket.emit('disconnected');
        socket.off();
      }
    } catch (error) {
      console.log("Error occurred while connecting to server", error);
    }
  }
    , [ENDPOINT]);
  socket.on('TennisScoreUpdate', (score) => {
    try {

      console.log(teamWin);
      setTableTennisTeamA(score.data.teamA);
      setTableTennisTeamB(score.data.teamB);
      if (!(teamWin == "A" || teamWin == "B")) {
        setTeamWin("None");
        // console.log("object");
      }

      if (score.data.teamA.set >= 2 || score.data.teamB.set >= 2) {
        setTeamWin(score.data.teamA.set > score.data.teamB.set ? 'A' : 'B');
      }

      if (selectedGame !== 'tableTennis') {
        setSelectedGame('tableTennis');
      }
    } catch (error) {
      console.log('Error occurred while updating score for Team A ', error.message);
    }
    // console.log(score);
  }
  );
  socket.on('BadmintonScoreUpdate', (score) => {
    try {

      console.log(score);
      // console.log(teamWin);
      setBadmintonTeamA(score.data.teamA);
      setBadmintonTeamB(score.data.teamB);
      if (!(teamWin == "A" || teamWin == "B")) {
        setTeamWin("None");
        // console.log("object");
      }
      if (selectedGame != 'badminton') {
        setSelectedGame('badminton');
      }
      if (score.data.teamA.set >= 2 || score.data.teamB.set >= 2) {
        setTeamWin(score.data.teamA.set > score.data.teamB.set ? 'A' : 'B');
      }
      // console.log(selectedGame);
      // setTableTennisTeamA(score.data.teamA);
      // setTableTennisTeamB(score.data.teamB);

    } catch (error) {
      console.log('Error occurred while updating score for Team A ', error.message);

    }
  }
  );
  socket.on('message', (data) => {
    console.log('Message received', data);
  }
  );
  return (
    <div className='page-cont'>
      <Navbar />
      <Routes>
        <Route path='/' element={<Home />} />
        <Route path='/info' element={<Info />} />
      </Routes>
      <Arduino />
    </div>
  );
}

export default App;
