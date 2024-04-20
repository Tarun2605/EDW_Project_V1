import { createContext, useState } from "react";

export const Appcontext = createContext();

export default function AppcontextProvider({children}){
    const [selectedGame, setSelectedGame] = useState("tableTennis");
    const [teamWin, setTeamWin] = useState("none");
    const [TableTennisTeamA, setTableTennisTeamA] = useState({score:0, set:0});
    const [TableTennisTeamB, setTableTennisTeamB] = useState({score:0, set:0});

    function resetTableTennis(){
        setTableTennisTeamA({score:0, set:0});
        setTableTennisTeamB({score:0, set:0});
        setTeamWin();
    }
    const value = {
        selectedGame,
        setSelectedGame,
        teamWin, // Add this
        setTeamWin, // Add this
        TableTennisTeamA,
        setTableTennisTeamA,
        TableTennisTeamB,
        setTableTennisTeamB,
        resetTableTennis,
    };

    return (
        <Appcontext.Provider value={value}>
            {children}
        </Appcontext.Provider>
    );
}