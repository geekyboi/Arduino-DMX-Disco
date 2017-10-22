/* spinner.h */
#include "lightObject.h"

#ifndef spinner_h
#define spinner_h

class spinner: public lightObject {
private:
    int _dmx;
    int _brightness;
public:
    spinner(int pin);
    void update();   
    void randomOnOff(int Time);
    void setBright(int brightness);
};

#endif  

