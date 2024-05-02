
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
  let {tableTennisTeamA, setTableTennisTeamA, setTableTennisTeamB, teamWin, selectedGame, setSelectedGame, setTeamWin, BadmintonTeamA, setBadmintonTeamA, BadmintonTeamB, setBadmintonTeamB, HockeyTeamA, setBootUp,
    setHockeyTeamA, HockeyTeamB, setHockeyTeamB, HockeyQuarter, setHockeyQuarter,      HockeyTime, setHockeyTime, HockeyStart, setHockeyStart } = useContext(Appcontext);

        useEffect(() => {
          const fetchAllData = async () => {
            try {
              const response = await axios.get('https://edw-tfub.onrender.com/config/getAllData');
              // const response = await axios.get('http://localhost:5000/config/getAllData');
              console.log('Data fetched successfully ', response);
              const gameData= await response?.data?.gameData;
              // console.log('Game Data ', gameData);
              gameData?.map((gameEach)=>{
                // if (gameEach.game == 'tableTennis') {
                  // setTableTennisTeamA(gameEach.gamedata.teamA);
                  // setTableTennisTeamB(gameEach.gamedata.teamB);
                // }
                if(gameEach.game === 'tableTennis'){
                  setTableTennisTeamA(gameEach.gamedata.teamA);
                  setTableTennisTeamB(gameEach.gamedata.teamB);
                  if ((teamWin == "A" || teamWin == "B")) {
                      setTeamWin("None");
                  }
                  if (gameEach.gamedata.teamA.set >= 2 || gameEach.gamedata.teamB.set >= 2) {
                    // console.log("Satisfied for table tennis");
                      setTeamWin(gameEach.gamedata.teamA.set > gameEach.gamedata.teamB.set ? 'A' : 'B');
                  }
                }
                if(gameEach.game === 'badminton'){
                  // console.log("checkpoint 1");
                  gameEach = gameEach.gamedata;
                  setBadmintonTeamA(gameEach.teamA);
                  setBadmintonTeamB(gameEach.teamB);
                  if ((teamWin == "A" || teamWin == "B")) {
                      setTeamWin("None");
                  }
                  if (gameEach.teamA.set >= 2 || gameEach.teamB.set >= 2) {
                    // console.log("Satisfied for badminton");
                      setTeamWin(gameEach.teamA.set > gameEach.teamB.set ? 'A' : 'B');
                  }
                }
                if(gameEach.game === 'hockey'){
                  gameEach = gameEach.gamedata;
                  // console.log("Checkpoint 1");
                  setHockeyTeamA(gameEach.teamA);
                  setHockeyTeamB(gameEach.teamB);
                  setHockeyQuarter(gameEach.quarter);
                  // setHockeyTime(gameEach.time);
                  // setHockeyStart(gameEach.start);
                  if ((teamWin == "A" || teamWin == "B")) {
                      setTeamWin("None");
                  }
                  if (gameEach.quarter == 4 && gameEach.time == 0) {
                    // console.log("Satisfied for hockey");
                    setTeamWin(gameEach.teamA.score > gameEach.teamB.score ? 'A' : 'B');
                  }

                }
              }
            );
            const latestGame = gameData.reduce((prev, current) => {
              
              return prev.updatedAt > current.updatedAt ? prev : current;
            });

            setSelectedGame(latestGame.game);
            console.log('Latest Game ', latestGame.game);
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
