
import io from 'socket.io-client';
// import io from "socket.io-client";
import { useContext, useEffect } from 'react';
import { Appcontext } from '../context/AppContext';
export default function SocketReciever() {
    const ENDPOINT = 'https://edw-tfub.onrender.com';
    // const ENDPOINT = 'http://localhost:5000';
    var socket = io(ENDPOINT);
    let { setTableTennisTeamA, setTableTennisTeamB, teamWin, selectedGame, setSelectedGame, setTeamWin, BadmintonTeamA, setBadmintonTeamA, BadmintonTeamB, setBadmintonTeamB, HockeyTeamA,
        setHockeyTeamA, HockeyTeamB, setHockeyTeamB, HockeyQuarter, setHockeyQuarter,      HockeyTime, setHockeyTime, HockeyStart, setHockeyStart } = useContext(Appcontext);
    socket.on('connect', () => {
        console.log('Connected to server');
    });
    socket.on('disconnected', () => {
        console.log('Disconnected from server');
    });
    socket.on('TennisScoreUpdate', (score) => {
        try {
            console.log(teamWin);
            setTableTennisTeamA(score.data.teamA);
            setTableTennisTeamB(score.data.teamB);
            if ((teamWin == "A" || teamWin == "B")) {
                setTeamWin("None");
                // console.log("object");
            }

            if (score.data.teamA.set >= 2 || score.data.teamB.set >= 2) {
                setTeamWin(score.data.teamA.set > score.data.teamB.set ? 'A' : 'B');
            }

            if (selectedGame !== 'tableTennis') {
                setSelectedGame('tableTennis');
            }
            if (!socket.disconnected) {
                socket.disconnect();
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
            if ((teamWin == "A" || teamWin == "B")) {
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
            if (!socket.disconnected) {
                socket.disconnect();
            }
        } catch (error) {
            console.log('Error occurred while updating score for Team A ', error.message);

        }
    }
    );
    socket.on("HockeyQuarterUpdate", (score) => {
        try {
            console.log(score);
            // console.log(teamWin);
            setHockeyStart(true);
            setHockeyTime(10);
            setHockeyQuarter(score.data.quarter);
            setHockeyTeamA(score.data.teamA);
            setHockeyTeamB(score.data.teamB);   
            if ((teamWin == "A" || teamWin == "B")) {
                setTeamWin("None");
                // console.log("object");
            }
            if (selectedGame != 'hockey') {
                setSelectedGame('hockey');
            }
            // console.log(selectedGame);
            // setTableTennisTeamA(score.data.teamA);
            // setTableTennisTeamB(score.data.teamB);
            if (!socket.disconnected) {
                socket.disconnect();
            }
        } catch (error) {
            console.log('Error occurred while updating score for Team A ', error.message);

        }
    }
    );
    socket.on('HockeyScoreUpdate', (score) => {
        try {
            console.log(score);
            // console.log(teamWin);
            setHockeyTeamA(score.data.teamA);
            setHockeyTeamB(score.data.teamB);
            if ((teamWin == "A" || teamWin == "B")) {
                setTeamWin("None");
                // console.log("object");
            }
            if (selectedGame != 'hockey') {
                setSelectedGame('hockey');
            }
            // console.log(selectedGame);
            // setTableTennisTeamA(score.data.teamA);
            // setTableTennisTeamB(score.data.teamB);
            if (!socket.disconnected) {
                socket.disconnect();
            }
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
        <>

        </>
    )
};
