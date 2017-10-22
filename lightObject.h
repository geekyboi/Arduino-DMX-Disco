/*
  disco.h
*/
#ifndef lightObject_h
#define lightObject_h

#include <Arduino.h>
#include <DmxSimple.h>

class lightObject
{
  /*------------------------------------------------------------------*/
  private:
    
  /*------------------------------------------------------------------*/
  public:
  /*------------------------------------------------------------------*/
    lightObject();
    bool _masterOnOff = false, _softOnOff = true;  
    unsigned long _timer;  /*                           effect timmers */
    
    void setTimer();
    unsigned long readTimer();
    
    void sendDMX(int aC, int aV);
    void sendDMX(int aC, int aV, int bC, int bV);
    void sendDMX(int aC, int aV, int bC, int bV, int cC, int cV);
    void sendDMX(int aC, int aV, int bC, int bV, int cC, int cV, int dC, int dV);
    void sendDMX(int aC, int aV, int bC, int bV, int cC, int cV, int dC, int dV, int eC, int eV);
    void sendDMX(int aC, int aV, int bC, int bV, int cC, int cV, int dC, int dV, int eC, int eV, int fC, int fV);
    
    void masterOn();
    void masterOff();
    void softOn() ;
    void softOff();
    void strobe(int onTime, int offTime);
    
};

#endif
