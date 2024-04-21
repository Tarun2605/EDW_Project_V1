import { useContext } from 'react';
import './Hockey.css';
import { Appcontext } from '../context/AppContext';
import TimerComponent from './TimerComponent';
export default function Hockey() {
    const { HockeyTeamA, setHockeyTeamA, HockeyTeamB, setHockeyTeamB, HockeyQuarter,
        setHockeyQuarter, HockeyTime, setHockeyTime, HockeyStart, setHockeyStart, setTeamWin, teamWin} = useContext(Appcontext);
    
    return (
        <>
            <div className='TableTennis-heading-cont'>
                <>Hockey</>
            </div>
            <div className='TableTennis-score-board-cont hockey-board-cont'>
                <div className='hockey-timer-cont'>
                    <TimerComponent startTime={10} start={HockeyStart}></TimerComponent>
                    <div>
                        Quarter: {HockeyQuarter}
                    </div>
                </div>
                <div className='hockey-score-cont'>
                    <div className='hockey-team-cont'>
                        <div className='hockey-team-heading-cont'>
                            Team A
                        </div>
                        <div className='hockey-team-score-cont'>
                            <div className='hockey-score-cont'>
                                Score: {HockeyTeamA.score}
                            </div>
                        </div>
                    </div>
                    <div className='hockey-team-cont'>
                        <div className='hockey-team-heading-cont'>
                            Team B
                        </div>
                        <div className='hockey-team-score-cont'>
                            <div className='hockey-score-cont'>
                                Score: {HockeyTeamB.score}
                            </div>
                        </div>
                    </div>
                </div>
            </div>
        </>
    )
};
