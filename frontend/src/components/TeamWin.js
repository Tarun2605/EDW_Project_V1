import './TeamWin.css';
export default function TeamWin(props){
return (
    <div className="TableTennis-score-board-cont team-win-cont" style={
            {
                    backgroundColor: props.team == 'A' ? 'lightblue' : 'lightcoral'
            }
            
    }>
        Team {props.team} wins!
    </div>
)
};
