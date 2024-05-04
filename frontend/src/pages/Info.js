import InfoCont from '../components/InfoCont';
import './Info.css';
export default function Info(){
  return (
    <div className="info-cont">
      <div className='info-cont-cont'>
        <div className='info-cont-cont-img'>
          <img src={require('../assets/tarun_profile_pic.png')} alt="Info Image" />
        </div>
      </div>
      <div className='info-cont-cont'>
        <div className='info-cont-cont-img'>
          <img src={require('../assets/tarun_profile_pic.png')} alt="Info Image" />
        </div>
        <div className='info-cont-cont-text'>
          <div className='info-cont-cont-text-name'>Tarun Prakash (2022UEC2672)</div>
          <div className='info-cont-cont-text-displayText'>

          I am a passionate programmer with expertise in ESP8266 and backend development. I have contributed to this project by programming the ESP8266 microcontroller and developing the backend of this website. My contributions include implementing communication protocols, handling data storage and retrieval, and ensuring the smooth functioning of the website's backend infrastructure.
          </div>
        </div>
      </div>
      <div className='info-cont-cont'>
      <div className='info-cont-cont-img'>
        <img src={require('../assets/tarun_profile_pic.png')} alt="Info Image" />
      </div>
      </div>
    </div>
  )
};
