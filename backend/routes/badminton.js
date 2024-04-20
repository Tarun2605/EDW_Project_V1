const express = require('express');
const router = express.Router();


router.get('/', (req, res) => {
    res.status(200);
    res.send("Welcome to Badminton API");
});

//#region Team A
router.get('/teamA/inc', (req, res) => {
    try {
        const {teamAinc} = require('../controllers/badminton');
        teamAinc(req, res);
    } catch (error) {
        res.status(500);
        res.send("Error occurred while updating score for badminton of Team A");
    }
});

//#endregion

//#region Team B
router.get('/teamB/inc', (req, res) => {
    try {
        const {teamBinc} = require('../controllers/badminton');
        teamBinc(req, res);
        
    } catch (error) {
        res.status(500);
        res.send("Error occurred while updating score for badminton of Team B");
        
    }
});

//#endregion

module.exports = router;