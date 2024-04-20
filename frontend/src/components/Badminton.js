import { useContext } from 'react';
import './TableTennis.css';
import { Appcontext } from '../context/AppContext';
export default function Badminton(){
    let {BadmintonTeamA, BadmintonTeamB} = useContext(Appcontext);
  return (
    <>
        <div className='TableTennis-heading-cont'>
          <>Badminton</>
        </div>
        <div className='TableTennis-score-board-cont'>
          <div className='TableTennis-team-cont'>
            <div className='TableTennis-team-heading-cont'>
              Team A
            </div>
            <div className='TableTennis-team-score-cont'>
                <div className='TableTennis-score-cont'>
                    Score: {BadmintonTeamA.score}
                </div>
                <div className='TableTennis-score-cont'>
                    Set: {BadmintonTeamA.set}
                </div>
            </div>
          </div>
          <div className='TableTennis-team-cont'>
            <div className='TableTennis-team-heading-cont'>
              Team A
            </div>
            <div className='TableTennis-team-score-cont'>
                <div className='TableTennis-score-cont'>
                    Score: {BadmintonTeamB.score}
                </div>
                <div className='TableTennis-score-cont'>
                    Set: {BadmintonTeamB.set}
                </div>
            </div>
          </div>
        </div>
    </>
  )
};
