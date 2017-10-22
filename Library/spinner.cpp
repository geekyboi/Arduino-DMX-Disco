#include "spinner.h"

spinner::spinner(int pin) {
    _dmx = pin;
    pinMode(_dmx, OUTPUT);
}
void spinner::update() {
    if(_masterOnOff && _softOnOff) {
        //Set light brightness
        sendDMX( _dmx, _brightness);
        //analogWrite(_dmx, _brightness);
    } else {
        //light off
        sendDMX( _dmx, 0);
        //analogWrite(_dmx, 0);
    }
}

void spinner::randomOnOff(int Time) {
  if (readTimer() >= Time) {
    bool tmp = rand() % 2;
    if (tmp) {
      softOn();
    } else {
      softOff();
    }
    setTimer();
  }
}

void spinner::setBright(int brightness) {
      _brightness = brightness;
}

