import { createContext, useState } from "react";

export const Appcontext = createContext();

export default function AppcontextProvider({children}){
    const [bootUp, setBootUp] = useState(false);
    const [selectedGame, setSelectedGame] = useState("none");
    const [teamWin, setTeamWin] = useState("none");
    const [TableTennisTeamA, setTableTennisTeamA] = useState({score:0, set:0});
    const [TableTennisTeamB, setTableTennisTeamB] = useState({score:0, set:0});
    const [BadmintonTeamA, setBadmintonTeamA] = useState({score:0, set:0});
    const [BadmintonTeamB, setBadmintonTeamB] = useState({score:0, set:0});
    const [HockeyTeamA, setHockeyTeamA] = useState({score:0});
    const [HockeyTeamB, setHockeyTeamB] = useState({score:0});
    const [HockeyQuarter, setHockeyQuarter] = useState(1);
    const [HockeyTime, setHockeyTime] = useState(0);
    const [HockeyStart, setHockeyStart] = useState(false);
    function resetTableTennis(){
        setTableTennisTeamA({score:0, set:0});
        setTableTennisTeamB({score:0, set:0});
        setTeamWin();
    }
    const value = {
        bootUp,
        setBootUp,
        selectedGame,
        setSelectedGame,
        teamWin, // Add this
        setTeamWin, // Add this
        TableTennisTeamA,
        setTableTennisTeamA,
        TableTennisTeamB,
        setTableTennisTeamB,
        resetTableTennis,
        BadmintonTeamA,
        setBadmintonTeamA,
        BadmintonTeamB,
        setBadmintonTeamB,
        HockeyTeamA,
        setHockeyTeamA,
        HockeyTeamB,
        setHockeyTeamB,
        HockeyQuarter,
        setHockeyQuarter,
        HockeyTime,
        setHockeyTime,
        HockeyStart,
        setHockeyStart
    };

    return (
        <Appcontext.Provider value={value}>
            {children}
        </Appcontext.Provider>
    );
}