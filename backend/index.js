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
        origin: "https://edw-project-v1-1.onrender.com",
        methods: ["GET", "POST"],
    },
});

io.on("connection", (socket) => {
    console.log("New client connected");

    socket.on("disconnect", () => {
        // your code here
    });
});
module.exports = {io,server}; 
//#endregion

server.listen(5000, () => console.log(`Listening on port ${PORT}`));

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

