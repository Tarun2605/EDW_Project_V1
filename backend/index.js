const express = require('express'); 
const http = require('http');
const app = express(); 
const PORT = 5000; 
const socketIo = require('socket.io');
app.use(express.json());
var cors = require('cors');
var corsOptions = {
    origin: ['https://edw-project-v1-1.onrender.com', 'http://localhost:3000'],
    optionsSuccessStatus: 200 // some legacy browsers (IE11, various SmartTVs) choke on 204
}
app.use(cors(corsOptions));

//#region socket set up
const server = http.createServer(app);
const io = socketIo(server, {
    cors: {
        origin: ["https://edw-project-v1-1.onrender.com", "http://localhost:3000"],
        methods: ["GET", "POST"],
    },
});

io.on("connection", (socket) => {
    // console.log("New client connected");
    
    socket.on("disconnect", () => {
        // your code here
    });
});
function sendViaSocket(message,data){
    console.log('message emitting');
    io.emit(message,data);
}
module.exports = {sendViaSocket};
// module.exports = {io,server}; 
//#endregion

server.listen(5000, () => console.log(`Listening on port ${PORT}`));

const dbconnect=require("./config/database");
dbconnect();

app.get('/', (req, res)=>{ 
	res.status(200); 
	res.send("Welcome to root URL of Server"); 
}); 

app.use('/config/bootUp', (req, res)=>{ 
    io.emit("BootUp",{data: 'Arduino is up and running'});
    res.status(200); 
    res.send({
        message: 'Arduino is up and running',
        dateTime: new Date()
    }); 
});
app.get('/config/getAllData', async (req, res)=>{
    try {
        console.log("getting all data");
        const game= require('./models/gameModel');
        const gameData = await game.find();
        console.log(gameData);
        res.status(200);
        res.send({
            message: 'Data fetched successfully',
            gameData: gameData,
            dateTime: new Date()
        });
        
    } catch (error) {
        console.log('Error occurred while fetching data ', error.message);
        res.status(500);
        res.send({
            message: 'Error while fetching data',
            dateTime: new Date()
        });
    }
});
app.get('/config/resetAllData', async (req, res)=>{
    try {
        console.log("Resetting all data");
        const game= require('./models/gameModel');
        const updateHockeyGame = await game.findOneAndUpdate(
            { game: 'hockey' },
            {
                $set: {
                    'gamedata.teamA.score': 0,
                    'gamedata.teamB.score': 0,
                    'gamedata.quarter': 1,
                    'updatedAt': new Date().toISOString(),
                }
            },
            { new: true }
        );
        const updatedTableTennisGame = await game.findOneAndUpdate(
            { game: 'tableTennis' },
            {
                $set: {
                    'gamedata.teamA.score': 0,
                    'gamedata.teamA.set': 0,
                    'gamedata.teamB.score': 0,
                    'gamedata.teamB.set': 0
                }
            },
            { new: true }
        );
        const updatedBadmintonGame = await game.findOneAndUpdate(
            { game: 'badminton' },
            {
                $set: {
                    'gamedata.teamA.score': 0,
                    'gamedata.teamA.set': 0,
                    'gamedata.teamB.score': 0,
                    'gamedata.teamB.set': 0
                }
            },
            { new: true }
        );
        
        // console.log(gameData);
        res.status(200);
        res.send({
            message: 'Data reset successfully',
            gameData: [updateHockeyGame, updatedTableTennisGame, updatedBadmintonGame],
            dateTime: new Date()
        });
        
    } catch (error) {
        console.log('Error occurred while resetting data ', error.message);
        res.status(500);
        res.send({
            message: 'Error while resetting data',
            dateTime: new Date()
        });
    }
});
app.use('/game/tableTennis', require('./routes/tableTennis'));
app.use('/game/badminton', require('./routes/badminton'));
app.use('/game/hockey', require('./routes/hockey'));

