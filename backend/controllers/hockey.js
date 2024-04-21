const { sendViaSocket } = require('..');
const game = require('../models/gameModel');

const teamAinc = async (req, res) => {
    try {
        const gameDataExist = await game.findOne({ game: 'hockey' });
        if ((gameDataExist && gameDataExist.length !== 0)) {
            const updatedGame = await game.findOneAndUpdate(
                { game: 'hockey' },
                {
                    $set: {
                        'gamedata.teamA.score': gameDataExist.gamedata.teamA.score + 1,
                        'gamedata.teamB.score': gameDataExist.gamedata.teamB.score,
                        'updatedAt': new Date().toISOString(),
                    }
                },
                { new: true }
            );
            sendViaSocket("HockeyScoreUpdate", {
                data: updatedGame.gamedata
            })
            console.log(updatedGame);
            return res.status(200).json(updatedGame.gamedata);
        }


    } catch (error) {
        console.log('Error occurred while updating score for Team A ', error.message);
    }
}
const teamBinc = async (req, res) => {
    try {
        const gameDataExist = await game.findOne({ game: 'hockey' });
        if (gameDataExist && gameDataExist.length !== 0) {
            const updatedGame = await game.findOneAndUpdate(
                { game: 'hockey' },
                {
                    $set: {
                        'gamedata.teamA.score': gameDataExist.gamedata.teamA.score,
                        'gamedata.teamB.score': gameDataExist.gamedata.teamB.score + 1,
                        'updatedAt': new Date().toISOString(),
                    }
                },
                { new: true }
            );
            sendViaSocket("HockeyScoreUpdate", {
                data: updatedGame.gamedata
            })
            console.log(updatedGame);
            return res.status(200).json(updatedGame.gamedata);
        }

    } catch (error) {
        console.log('Error occurred while updating score for Team B ', error.message);
    }
}


const changeQuarter = async (req, res) => {
    try {
        const gameDataExist = await game.findOne({ game: 'hockey' });
        if (gameDataExist && gameDataExist.length !== 0) {
            const updatedGame = await game.findOneAndUpdate(
                { game: 'hockey' },
                {
                    $set: {
                        'gamedata.teamA.score': gameDataExist.gamedata.teamA.score,
                        'gamedata.teamB.score': gameDataExist.gamedata.teamB.score,
                        'gamedata.startedAt': new Date().toISOString(),
                        'gamedata.quarter': gameDataExist.gamedata.quarter + 1 > 4 ? 1 : gameDataExist.gamedata.quarter + 1,
                        'updatedAt': new Date().toISOString(),
                    }
                },
                { new: true }
            );
            sendViaSocket("HockeyQuarterUpdate", {
                data: updatedGame.gamedata
            })
            console.log(updatedGame);
            return res.status(200).json(updatedGame.gamedata);
        } else {
            //create game data
            const newGame = new game({
                game: 'hockey',

                gamedata: {
                    startedAt: new Date().toISOString(),
                    quarter: 1,
                    teamA: {
                        score: 0,
                        set: 0
                    },
                    teamB: {
                        score: 0,
                        set: 0
                    }

                }
            });
            await newGame.save();
            sendViaSocket("HockeyQuarterUpdate", {
                data: newGame.gamedata
            })
        }
        return res.status(200).json(newGame.gamedata);
    } catch (error) {
        console.log('Error occurred while changing quarter ', error.message);
    }
}

module.exports = { teamAinc, teamBinc, changeQuarter };