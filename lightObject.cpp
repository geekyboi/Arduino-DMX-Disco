#include "lightObject.h"

lightObject::lightObject() {
  
}
void lightObject::setTimer() {
    _timer = millis();
}

unsigned long lightObject::readTimer() {
    unsigned long i = millis() - _timer;
    return i;
}

void lightObject::sendDMX(int aC, int aV) {
    DmxSimple.write(aC, constrain(aV,0,255));
}
void lightObject::sendDMX(int aC, int aV, int bC, int bV) {
    DmxSimple.write(aC, constrain(aV,0,255));
    DmxSimple.write(bC, constrain(bV,0,255));
}
void lightObject::sendDMX(int aC, int aV, int bC, int bV, int cC, int cV) {
    DmxSimple.write(aC, constrain(aV,0,255));
    DmxSimple.write(bC, constrain(bV,0,255));
    DmxSimple.write(cC, constrain(cV,0,255));
}
void lightObject::sendDMX(int aC, int aV, int bC, int bV, int cC, int cV, int dC, int dV) {
    DmxSimple.write(aC, constrain(aV,0,255));
    DmxSimple.write(bC, constrain(bV,0,255));
    DmxSimple.write(cC, constrain(cV,0,255));
    DmxSimple.write(dC, constrain(dV,0,255));
}
void lightObject::sendDMX(int aC, int aV, int bC, int bV, int cC, int cV, int dC, int dV, int eC, int eV) {
    DmxSimple.write(aC, constrain(aV,0,255));
    DmxSimple.write(bC, constrain(bV,0,255));
    DmxSimple.write(cC, constrain(cV,0,255));
    DmxSimple.write(dC, constrain(dV,0,255));
    DmxSimple.write(eC, constrain(eV,0,255));
}
void lightObject::sendDMX(int aC, int aV, int bC, int bV, int cC, int cV, int dC, int dV, int eC, int eV, int fC, int fV) {
    DmxSimple.write(aC, constrain(aV,0,255));
    DmxSimple.write(bC, constrain(bV,0,255));
    DmxSimple.write(cC, constrain(cV,0,255));
    DmxSimple.write(dC, constrain(dV,0,255));
    DmxSimple.write(eC, constrain(eV,0,255));
    DmxSimple.write(fC, constrain(fV,0,255));
}

/*----------------------------------------------------------------*
 * Generic Fixture functions                                      *
 *----------------------------------------------------------------*/

void lightObject::masterOn() { /*                             User on function */
    _masterOnOff = true;
}

void lightObject::masterOff() { /*                           User off function */
    _masterOnOff = false;
}

void lightObject::softOn() { /*                           software on function */
    _softOnOff = true;
}

void lightObject::softOff() { /*                         software off function */
    _softOnOff = false;
}

void lightObject::strobe(int onTime, int offTime) {
    if (!_softOnOff && readTimer() >= offTime) {
        softOn();
        setTimer();
    } else if (_softOnOff && readTimer() >= onTime) {
        softOff();
        setTimer();
    }
}

