import { useContext } from 'react';
import './TableTennis.css';
import { Appcontext } from '../context/AppContext';
export default function TableTennis(){
    let {TableTennisTeamA, TableTennisTeamB} = useContext(Appcontext);
  return (
    <>
        <div className='TableTennis-heading-cont'>
          <>Table Tennis</>
        </div>
        <div className='TableTennis-score-board-cont'>
          <div className='TableTennis-team-cont'>
            <div className='TableTennis-team-heading-cont'>
              Team A
            </div>
            <div className='TableTennis-team-score-cont'>
                <div className='TableTennis-score-cont'>
                    Score: {TableTennisTeamA.score}
                </div>
                <div className='TableTennis-score-cont'>
                    Set: {TableTennisTeamA.set}
                </div>
            </div>
          </div>
          <div className='TableTennis-team-cont'>
            <div className='TableTennis-team-heading-cont'>
              Team A
            </div>
            <div className='TableTennis-team-score-cont'>
                <div className='TableTennis-score-cont'>
                    Score: {TableTennisTeamB.score}
                </div>
                <div className='TableTennis-score-cont'>
                    Set: {TableTennisTeamB.set}
                </div>
            </div>
          </div>
        </div>
    </>
  )
};
