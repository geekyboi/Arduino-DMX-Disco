#include "RGBCan.h"

RGBCan::RGBCan(int brightCh, int redCh, int greenCh, int blueCh) {
    _dmx[0] = redCh;
    _dmx[1] = greenCh;
    _dmx[2] = blueCh;
    _dmx[3] = brightCh;
}

void RGBCan::update() {
    if(_masterOnOff && _softOnOff) {
        //Turn light on i.e. transmit requested DMX
        sendDMX( _dmx[0], _red[1], _dmx[1], _green[1], _dmx[2], _blue[1], _dmx[3], _bright[1]);
    } else {
        //Turn light off i.e. transmit 0 on all DMX
        sendDMX( _dmx[0], 0, _dmx[1], 0, _dmx[2], 0, _dmx[3], 0);
    }
}
    
void RGBCan::setRed(int red) {
    _red[1] = red;
}

void RGBCan::setGreen(int green) {
    _green[1] = green;
}

void RGBCan::setBlue(int blue) {
    _blue[1] = blue;
}

void RGBCan::setBright(int bright) {
    _bright[1] = bright;
};

void RGBCan::setColor(int red, int green, int blue) {
    setRed(red);
    setGreen(green);
    setBlue(blue);
}

void RGBCan::setRandomColor() {
    setColor(randomColor(),randomColor(),randomColor());
}

void RGBCan::setPrevColor() {
    _red[0] = _red[1];
    _green[0] = _green[1];
    _blue[0] = _blue[1];
}

void RGBCan::setPrevBright() {
    _bright[0] = _bright[1];
}

void RGBCan::setNextRed(int red){
    _red[2] = red;
}
void RGBCan::setNextGreen(int green){
    _green[2] = green;
}
void RGBCan::setNextBlue(int blue){
    _blue[2] = blue;
}
void RGBCan::setNextBright(int bright){
    _bright[2] = bright;
}
void RGBCan::setNextColor(int red, int green, int blue){
    setNextRed(red);
    setNextGreen(green);
    setNextBlue(blue);
}

int RGBCan::redValue() {
  return _red[1];
}

int RGBCan::blueValue() {
  return  _blue[1];
}
 
int RGBCan::greenValue() {
  return _green[1];
}

int RGBCan::brightValue() {
  return _bright[1];
}

void RGBCan::turnOn() {
    softOn();
}
void RGBCan::turnOff() {
    softOff();
}

int RGBCan::randomColor() {
  return random(0,3)*125;
}

void RGBCan::switchColor(int Time) {
  softOn();
  if (_softOnOff && readTimer() >= Time) {
    setPrevColor();
    setPrevBright();
    setRandomColor();
    setTimer();
   }
}

void RGBCan::randomFlash(int flashes, int Time) {
  
  if (readTimer() >= Time) {
    setPrevColor();
    setPrevBright();
    setRandomColor();
    setTimer();
  }
  
  flashTime = readTimer() % (Time/(flashes*2));
  if (!_softOnOff && flashTime < prevFlashTime) {
    softOn();
  } else if (_softOnOff && flashTime < prevFlashTime) {
    softOff();
  }
  prevFlashTime = flashTime;

}

void RGBCan::fadeColor(int Time) {
  softOn();
  if(readTimer() >= Time) {
    setTimer();
    setPrevColor();
    setNextColor(randomColor(),randomColor(),randomColor());
  }
  fade(Time);
}

void RGBCan::pulse(int fadeInTime, int fadeOutTime, int onTime, int offTime) {
      softOn();
  if (readTimer() <= fadeInTime) { // Fade to on
      fade(fadeInTime, readTimer());
  } else if (fadeInTime <= readTimer() && readTimer() < fadeInTime + onTime) { // Stay On
      setPrevColor();
      setPrevBright();
      setNextColor(0,0,0);
  } else if (fadeInTime + onTime <= readTimer() && readTimer() < fadeInTime + onTime + fadeOutTime ) { // Fade to black
      fade(fadeOutTime,readTimer()-(fadeInTime + onTime));
  } else if (fadeInTime + onTime + fadeOutTime + offTime <= readTimer() ) { //Stay black
      setPrevColor();
      setPrevBright();
      setNextColor(randomColor(),randomColor(),randomColor());
      setTimer();
  }

}

void RGBCan::fade(float Time) {
  softOn();
  float percent = readTimer()/Time;
  setColor(   _red[0] + (   _red[2] -    _red[0] )*percent,
            _green[0] + ( _green[2] -  _green[0] )*percent,
             _blue[0] + (  _blue[2] -   _blue[0] )*percent );
}
void RGBCan::fade(float Time,float currentTime) {
  softOn();
  float percent = currentTime/Time;
  setColor(   _red[0] + (   _red[2] -    _red[0] )*percent,
            _green[0] + ( _green[2] -  _green[0] )*percent,
             _blue[0] + (  _blue[2] -   _blue[0] )*percent );
}

