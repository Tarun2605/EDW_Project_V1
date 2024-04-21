
import './App.css';
import io from 'socket.io-client';
// import io from "socket.io-client";
import { useContext, useEffect } from 'react';
import { Routes, Route } from 'react-router';
import Home from './pages/Home';
import Navbar from './components/Navbar';
import Arduino from './components/Arduino';
import Info from './pages/Info';
import { Appcontext } from './context/AppContext';
import SocketReciever from './utils/Socket';
// Rest of the code...


function App() {
  
  return (
    <>
    <SocketReciever></SocketReciever>
    <div className='page-cont'>
      <Navbar />
      <Routes>
        <Route path='/' element={<Home />} />
        <Route path='/info' element={<Info />} />
      </Routes>
      <Arduino />
    </div>
    </>
  );
}

export default App;
