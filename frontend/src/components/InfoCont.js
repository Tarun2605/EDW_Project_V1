import React from 'react';

const InfoCont = ({ imageLink, displayText, personName }) => {
    return (
        <div className='info-cont'>
            <img className='info-cont-image' src={require(`${imageLink}`)} alt="Info Image" />
            <div className='info-cont-text'>
                <div className='info-cont-text-name'>{personName}</div>
                <div className='info-cont-text-displayText'>{displayText}</div>
            </div>
        </div>
    );
};

export default InfoCont;