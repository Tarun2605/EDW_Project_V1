import React, { useState, useEffect, useContext } from 'react';
import { Appcontext } from '../context/AppContext';

const TimerComponent = ({ startTime, start }) => {
    const [time, setTime] = useState(startTime);
    const {HockeyTime, setHockeyTime, setTeamWin, teamWin,HockeyTeamA, HockeyTeamB,HockeyQuarter} = useContext(Appcontext);
    useEffect(() => {
        if (start) {
            const interval = setInterval(() => {
                setHockeyTime((prevTime) => {
                    const newTime = (prevTime - 1);
                    return newTime >= 0 ? newTime : 0;
                });
            }, 1000);

            return () => {
                clearInterval(interval);
            };
        }
    }, [start]);
    useEffect(() => {
        if (HockeyTime === 0 && HockeyQuarter == 4) {

            setTeamWin(HockeyTeamA.score > HockeyTeamB.score ? 'A' : 'B');
        }
    }
    , [HockeyTime]);
    return (
        <div style={{ textAlign: 'center' }}>
            <h1 style={{ fontSize: '2vw', color: 'blue' }}>Timer: {HockeyTime}</h1>
        </div>
    );
};

export default TimerComponent;