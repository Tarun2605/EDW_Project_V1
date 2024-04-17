const express = require('express');
const router = express.Router();


router.get('/', (req, res) => {
    res.status(200);
    res.send("Welcome to Table Tennis API");
});

//#region Team A
router.get('/teamA/inc', (req, res) => {
    try {
        const {teamAinc} = require('../controllers/tableTennis');
        teamAinc(req, res);
        res.status(200);
        res.send("Team A Scored a Point");
    } catch (error) {
        res.status(500);
        res.send("Error occurred while updating score for Team A");
    }
});

router.get('/teamA/win', (req, res) => {
    try {
        res.status(200);
        res.send("Team A Won the Match");
    } catch (error) {
        res.status(500);
        res.send("Error occurred while updating score for Team A");
    }
});
//#endregion

//#region Team B
router.get('/teamB/inc', (req, res) => {
    res.status(200);
    res.send("Team B Scored a Point");
});

router.get('/teamB/win', (req, res) => {
    res.status(200);
    res.send("Team B Won the Match");
});
//#endregion

module.exports = router;