const { sendViaSocket } = require('..');
const game = require('../models/gameModel');
//#region Team A
const teamAinc =async (req, res) => {
    try {
        const gameDataExist = await game.findOne({game: 'tableTennis'});
        if ((gameDataExist && gameDataExist.length !== 0)) {
            const updatedGame = await game.findOneAndUpdate(
                { game: 'tableTennis' },
                {
                    $set: {
                        'gamedata.teamA.score': gameDataExist.gamedata.teamA.score + 1 >= 11 && gameDataExist.gamedata.teamA.score - gameDataExist.gamedata.teamB.score >= 2 ? 0 : gameDataExist.gamedata.teamA.score + 1,
                        'gamedata.teamA.set': gameDataExist.gamedata.teamA.score + 1 >= 11 && gameDataExist.gamedata.teamA.score - gameDataExist.gamedata.teamB.score >= 2 ? 
                            (gameDataExist.gamedata.teamA.set <= 1 || (gameDataExist.gamedata.teamA.set === 2 && gameDataExist.gamedata.teamA.set === gameDataExist.gamedata.teamB.set) ? gameDataExist.gamedata.teamA.set + 1 : 0)
                            : 
                            (gameDataExist.gamedata.teamB.set==2 || gameDataExist.gamedata.teamA.set==2 ? 0 : gameDataExist.gamedata.teamA.set),
                        'gamedata.teamB.score': gameDataExist.gamedata.teamA.score + 1 >= 11 && gameDataExist.gamedata.teamA.score - gameDataExist.gamedata.teamB.score >= 2 ? 0 : gameDataExist.gamedata.teamB.score,
                        'gamedata.teamB.set': gameDataExist.gamedata.teamA.set === 2 || gameDataExist.gamedata.teamB.set === 2 ? 
                            0 : gameDataExist.gamedata.teamB.set
                    }
                },
                { new: true }
            );
            sendViaSocket("TennisScoreUpdate", {
                data:updatedGame.gamedata})
            console.log(updatedGame);
            return res.status(200).json(updatedGame.gamedata);
            } else {
            //create game data
            const newGame = new game({
                game : 'tableTennis',
               
                    gamedata: {
                        teamA: {
                            score: 1,
                            set: 0
                        },
                        teamB: {
                            score: 0,
                            set: 0
                        }
                    
                }
            });
            await newGame.save();
            sendViaSocket("TennisScoreUpdate", {
                data:newGame.gamedata})
        }

        
    } catch (error) {
        console.log('Error occurred while updating score for Team A ', error.message);
    }
}
const teamBinc = async (req, res) => {
    try {
        const gameDataExist = await game.findOne({ game: 'tableTennis' });
        if (gameDataExist && gameDataExist.length !== 0) {
            const updatedGame = await game.findOneAndUpdate(
                { game: 'tableTennis' },
                {
                    
                        $set: {
                            'gamedata.teamB.score': gameDataExist.gamedata.teamB.score + 1 >= 11 && gameDataExist.gamedata.teamB.score - gameDataExist.gamedata.teamA.score >= 2 ? 0 : gameDataExist.gamedata.teamB.score + 1,
                            'gamedata.teamB.set': gameDataExist.gamedata.teamB.score + 1 >= 11 && gameDataExist.gamedata.teamB.score - gameDataExist.gamedata.teamA.score >= 2 ? 
                                (gameDataExist.gamedata.teamB.set <= 1 || (gameDataExist.gamedata.teamB.set === 2 && gameDataExist.gamedata.teamB.set === gameDataExist.gamedata.teamA.set) ? gameDataExist.gamedata.teamB.set + 1 : 0) 
                                :
                            (gameDataExist.gamedata.teamB.set==2 || gameDataExist.gamedata.teamA.set==2 ? 0 : gameDataExist.gamedata.teamB.set),
                            'gamedata.teamA.score': gameDataExist.gamedata.teamB.score + 1 >= 11 && gameDataExist.gamedata.teamB.score - gameDataExist.gamedata.teamA.score >= 2 ? 0 : gameDataExist.gamedata.teamA.score,
                            'gamedata.teamA.set': gameDataExist.gamedata.teamA.set==2 || gameDataExist.gamedata.teamB.set==2 ? 
                                0 : gameDataExist.gamedata.teamA.set
                        }
                
                },
                { new: true }
            );
            sendViaSocket("TennisScoreUpdate", {
                data: updatedGame.gamedata
            });
            console.log(updatedGame);
            return res.status(200).json(updatedGame.gamedata);
        } else {
            //create game data
            const newGame = new game({
                game: 'tableTennis',
                gamedata: {
                    teamA: {
                        score: 0,
                        set: 0
                    },
                    teamB: {
                        score: 1,
                        set: 0
                    }
                }
            });
            await newGame.save();
            sendViaSocket("TennisScoreUpdate", {
                data: newGame.gamedata
            });
        }
    } catch (error) {
        console.log('Error occurred while updating score for Team B ', error.message);
    }
}
//#endregion
module.exports = {teamAinc, teamBinc};