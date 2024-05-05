//import home.css
import { useContext } from 'react';
import TableTennis from '../components/TableTennis';
import './Home.css';
import { Appcontext } from '../context/AppContext';
import TeamWin from '../components/TeamWin';
import Badminton from '../components/Badminton';
import Hockey from '../components/Hockey';
export default function Home(){
  const {selectedGame, teamWin} = useContext(Appcontext);
  // let {selectedGame} = useContext(AppcontextProvider);
  return (
    <div className='home-cont'>
      <div className='game-cont'>
      {
        selectedGame == 'tableTennis' ? (
          (teamWin =="A" || teamWin=="B") ? <TeamWin team={teamWin}/> : <TableTennis/>
        ) : null
      }
      {
        selectedGame == 'badminton' ? (
          (teamWin =="A" || teamWin=="B") ? <TeamWin team={teamWin}/> : <Badminton/>
        ) : null
      }
      {
        selectedGame == 'hockey' ? (
          (teamWin =="A" || teamWin=="B" || teamWin=="Both") ? <TeamWin team={teamWin}/> : <Hockey/>
        ) : null
      }
    {/* <TeamWin team='A'/> */}
      </div>
    </div>
  )
};
