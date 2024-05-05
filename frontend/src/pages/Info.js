import InfoCont from '../components/InfoCont';
import './Info.css';
export default function Info(){
  return (
    <div className="info-cont">
      <div className='info-cont-cont'>
        <div className='info-cont-cont-img'>
          <img src={require('../assets/vidit_profile_pic.png')} alt="Info Image" />
        </div>
        <div className='info-cont-cont-text'>
          <div className='info-cont-cont-text-name'>Vidit Pant (2022UEC2656)</div>
          <div className='info-cont-cont-text-displayText'>

          In my role, I excelled in Arduino programming, testing, component layout, soldering, and encasing. With precision and dedication, I ensured efficient assembly, component integrity, and the creation of robust final products, emphasizing quality assurance throughout.
          </div>
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
        <img src={require('../assets/prasun_profile_pic.png')} alt="Info Image" />
      </div>
      <div className='info-cont-cont-text'>
          <div className='info-cont-cont-text-name'>Prasun Sharma (2022UEC2679)</div>
          <div className='info-cont-cont-text-displayText'>

          I am a have a strong proficiency in frontend programming and soldering. I played a pivotal role by planning the project and my contributions include programming the  layouting, soldering and encasing components, and developing the frontend infrastructure of the system.
          </div>
        </div>
      </div>
    </div>
  )
};
