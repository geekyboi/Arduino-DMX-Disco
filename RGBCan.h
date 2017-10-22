#include "lightObject.h"

#ifndef RGBCan_h
#define RGBCan_h

class RGBCan: public lightObject {
private:
  int _dmx[4];
  int _red[3], _green[3], _blue[3], _bright[3];
  unsigned long prevFlashTime, flashTime;
public:
  RGBCan(int redCh, int greenCh, int blueCh, int brightCh);
  /* Generic Fixture fuctions */  
  void update(); // Must be called at the end of the loop or the light won't do anything
                 // if not called light will pause (this can be useful some times)
  
  /* Set Current */
  void setRed(int red);
  void setGreen(int green);
  void setBlue(int blue);
  void setBright(int bright);
  void setColor(int red, int green, int blue);
  void setRandomColor();
  //void fadeBetween(int color, int time);
  
  /* Set Previous (this is always a copy of the current) */
  // Previous color is used in functions like fade e.g. fade sets current to gradually change between previous and next
  void setPrevColor();
  void setPrevBright();
  
  /* Set Next - As it suggests sets the nect colours*/
  void setNextRed(int red);
  void setNextGreen(int green);
  void setNextBlue(int blue);
  void setNextBright(int bright);
  void setNextColor(int red, int green, int blue);
  void fade(float fadeTime);
  void fade(float fadeTime, float currentTime);
  
  /* Send Outputs - Useful if you need to sync lights together i.e. use in combination with setColor & setBright */
  int redValue();
  int blueValue();
  int greenValue();
  int brightValue();

  /* Other Functions */
  int randomColor();

  /* Special Fixture fuctions */
  void turnOn();
  void turnOff();
  void pulse(int fadeInTime, int fadeOutTime, int onTime, int offTime); //Fade through blank
  void switchColor(int Time); //Switch between random colours
  void randomFlash(int flashes, int Time); // randomly flashes the light
  void fadeColor(int Time);
  
};

#endif
