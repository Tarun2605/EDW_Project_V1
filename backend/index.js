const express = require('express'); 
const http = require('http');
const app = express(); 
const PORT = 5000; 
const socketIo = require('socket.io');
app.use(express.json());

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
    io.emit('message',{data: 'Arduino is up and running'});
    res.status(200); 
    res.send({
        message: 'Arduino is up and running',
        dateTime: new Date()
    }); 
});

app.use('/game/tableTennis', require('./routes/tableTennis'));
app.use('/game/badminton', require('./routes/badminton'));

