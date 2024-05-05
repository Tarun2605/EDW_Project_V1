const express = require('express');
const router = express.Router();


router.get('/', (req, res) => {
    res.status(200);
    res.send("Welcome to Hockey API");
});

router.get('/changeQuarter', (req, res) => {
    try {
        const {changeQuarter} = require('../controllers/hockey');
        changeQuarter(req, res);
    } catch (error) {
        res.status(500);
        res.send("Error occurred while changing quarter");
    }
}
);
//#region Team A
router.get('/teamA/inc', (req, res) => {
    try {
        const {teamAinc} = require('../controllers/hockey');
        teamAinc(req, res);
    } catch (error) {
        res.status(500);
        res.send("Error occurred while updating score for Team A");
    }
});

//#endregion

//#region Team B
router.get('/teamB/inc', (req, res) => {
    try {
        const {teamBinc} = require('../controllers/hockey');
        teamBinc(req, res);
    } catch (error) {
        res.status(500);
        res.send("Error occurred while updating score for tableTennis of Team B");
    }
});

//#endregion

module.exports = router;