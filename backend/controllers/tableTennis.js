
//#region Team A
const teamAinc = (req, res) => {
    try {
        const io = require('../index').io;
        console.log('Team A Scored a Point');
        io.emit('scoreUpdate', {
            data:{
            game: 'Table Tennis',
            team: 'A',
            score: 1
            }
        });
    } catch (error) {
        console.log('Error occurred while updating score for Team A');
    }
}

//#endregion
module.exports = {teamAinc};