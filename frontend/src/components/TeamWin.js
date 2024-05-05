import './TeamWin.css';
export default function TeamWin(props) {
    return (
        props.teamWin =="A" ? (
            <div className="TableTennis-score-board-cont team-win-cont" style={{
                backgroundColor: props.teamWin === "A" ? 'lightblue' : 'lightcoral'
            }}>
                Team {props.teamWin} wins!
            </div>
        ) :
        props.teamWin =="B" ? 
        (
            <div className="TableTennis-score-board-cont team-win-cont" style={{
                backgroundColor: props.teamWin === "A" ? 'lightblue' : 'lightcoral'
            }}>
                Team {props.teamWin} wins!
            </div>
        ) :
        props.teamWin =="Both" ?
        (
            <div className="TableTennis-score-board-cont team-win-cont">
                It's a draw!
            </div>
        )
        :
        <></>
    );
};
