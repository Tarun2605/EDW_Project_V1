import logo from './logo.svg';
import './App.css';
import io from 'socket.io-client';
// import io from "socket.io-client";
import { useEffect } from 'react';
// Rest of the code...
var socket;

function App() {
  const ENDPOINT = 'http://localhost:5000';
  socket = io(ENDPOINT);
  useEffect(() => {
    try {
      
      socket.on('connect', () => {
        console.log('Connected to server');
      });
      socket.on('disconnected', () => {
        console.log('Disconnected from server');
      });
      return () => {
        socket.emit('disconnected');
        socket.off();
      }
    } catch (error) {
      console.log("Error occurred while connecting to server", error);
    }
  }
  , [ENDPOINT]);
  socket.on('scoreUpdate', (score) => {
    console.log('Score updated to', score);
  }
  );
  socket.on('message', (data) => {
    console.log('Message received', data);
  }
  );
  return (
    <div className="App">
      <h1>React App</h1>
    </div>
  );
}

export default App;
