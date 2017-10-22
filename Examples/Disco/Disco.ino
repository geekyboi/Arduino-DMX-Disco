/*--------------------------------------------------------------------
  ############################# LIBRARIES ############################
  --------------------------------------------------------------------*/
#include <discoLib.h>

/*--------------------------------------------------------------------
  ######################## VARIABLES & OBJECTS #######################
  --------------------------------------------------------------------*/

/* ------------------------------------------------- Global Variables */
int mode = 5, prevMode;
int numberModes = 5;
unsigned long modeTimer = 0;
int modeTimeOn = 1000;
bool error = false;
int tempo = 800;
/* -------------------------------------------------- Define Fixtures */
RGBCan rightCan(1,2,3,4); //Red, Green, Blue, Bright
RGBCan leftCan(10,11,12,13); //Red, Green, Blue, Bright
spinner rightSpin(9); //Bright
spinner leftSpin(10); //Bright

void update(void) { /*                   Update all fixtures function */
  rightCan.update();
  leftCan.update();
  rightSpin.update();
  leftSpin.update();
}


/*--------------------------------------------------------------------
  ############################### SETUP ##############################
  --------------------------------------------------------------------*/
void setup() {
/* ----------------------------------------------- Setup DMX Universe */
  DmxSimple.usePin(3);
  DmxSimple.maxChannel(30);
  changeMode();
  Serial.begin(9600);
}

/*--------------------------------------------------------------------
  ############################# MAIN LOOP ############################
  --------------------------------------------------------------------*/
void loop() {
  int startMillis = millis();
/* ------------------------------------------------------ Change mode */
  if ((millis() - modeTimer >= modeTimeOn) || error) {
    changeMode();
    modeTimer = millis();
    error = false;
    //Serial.print("Change Mode: ");
    //Serial.println(mode);
  }

/* ------------------------------------------------------------ Modes */
switch (mode) {
   /* ||||||||||||||||||||||| MODE 1 - RANDOM ||||||||||||||||||||||| */
  case 1: /*                             Light turned on single color */
    /* -------------------------------------------------- Modes Setup */
    modeTimeOn = 12*tempo; /*             How long before changing mode? */
    rightCan.masterOn(); /*     which lights are active in this mode? */
    leftCan.masterOn();
    rightSpin.masterOn();
    leftSpin.masterOn();
    /* ------------------------------------------------ Mode Function */
    rightCan.setBright(255);
    leftCan.setBright(255);
    rightSpin.setBright(255);
    leftSpin.setBright(255);
    rightCan.switchColor(tempo);
    leftCan.switchColor(tempo);
    rightSpin.randomOnOff(tempo);
    leftSpin.randomOnOff(tempo);
    
  break;
  /* |||||||||||||||||||||||| MODE 2 - STROBE |||||||||||||||||||||||| */
  case 2: /*                                              strobe light */
    /* --------------------------------------------------- Modes Setup */
    modeTimeOn = 2*tempo; /*               How long before changing mode? */
    rightCan.masterOn(); /*      which lights are active in this mode? */
    leftCan.masterOn();
    rightSpin.masterOn();
    leftSpin.masterOn();
    /* ------------------------------------------------- Mode Function */
    if(prevMode != mode) {
      rightCan.setRandomColor();
      leftCan.setRandomColor();
    }
    rightCan.setBright(255);
    leftCan.setBright(255);
    rightSpin.setBright(255);
    leftSpin.setBright(255);
    rightCan.strobe(35,35);
    leftCan.strobe(35,35);
    rightSpin.strobe(50,50);
    leftSpin.strobe(100,100);
  break;
  
  /* ||||||||||||||||||||| MODE 3 - RANDOM FLASH ||||||||||||||||||||| */
  case 3: /*                                              strobe light */
    /* --------------------------------------------------- Modes Setup */
    modeTimeOn = 12*tempo; /*               How long before changing mode? */
    rightCan.masterOn(); /*      which lights are active in this mode? */
    leftCan.masterOn();
    rightSpin.masterOn();
    leftSpin.masterOn();
    /* ------------------------------------------------- Mode Function */
    if(mode != prevMode) {
      rightCan.turnOn();
      leftCan.turnOff();
    }
    rightCan.setBright(255);
    leftCan.setBright(255);
    rightSpin.setBright(255);
    leftSpin.setBright(255);
    rightCan.randomFlash(4, 2*tempo);
    leftCan.randomFlash(4, 2*tempo);
    rightSpin.randomOnOff(tempo);
    leftSpin.randomOnOff(tempo);
  break;

  /* ||||||||||||||||||||| MODE 4 - RANDOM FADE |||||||||||||||||||||| */
  case 4: /*                                              strobe light */
    /* --------------------------------------------------- Modes Setup */
    modeTimeOn = 12*tempo; /*               How long before changing mode? */
    rightCan.masterOn(); /*      which lights are active in this mode? */
    leftCan.masterOn();
    rightSpin.masterOn();
    leftSpin.masterOn();
    /* ------------------------------------------------- Mode Function */
    rightCan.setBright(255);
    leftCan.setBright(255);
    rightSpin.setBright(255);
    leftSpin.setBright(255);
    rightCan.fadeColor(tempo);
    rightSpin.randomOnOff(tempo);
    leftCan.randomFlash(2,tempo);
    leftSpin.randomOnOff(tempo);
  break;
  
  /* ||||||||||||||||| MODE 5 - PULSE THROUGH BLACK |||||||||||||||||| */
  case 5: /*                                              strobe light */
    /* --------------------------------------------------- Modes Setup */
    modeTimeOn = 12*tempo; /*               How long before changing mode? */
    rightCan.masterOn(); /*      which lights are active in this mode? */
    leftCan.masterOn();
    rightSpin.masterOn();
    leftSpin.masterOn();
    /* ------------------------------------------------- Mode Function */
    rightCan.setBright(255);
    leftCan.setBright(255);
    rightSpin.setBright(255);
    leftSpin.setBright(255);
    rightCan.fadeColor(tempo);
    leftCan.pulse(tempo/4,tempo/4,tempo/8,tempo/8);
    rightSpin.randomOnOff(tempo);
    leftSpin.randomOnOff(tempo);
  break;
  default: 
    /*               If the mode isn't defined above choose a new one */
    error = true;
  break;
}


/* -------------------------------------------------- Update fixtures */
  if (prevMode == mode) { /*    this prevents random flashes of light */
    update(); /*                must be called at the end of the loop */
  } else {
    rightCan.setTimer();
    leftCan.setTimer();
    rightSpin.setTimer();
    leftSpin.setTimer();
  }

/* ------------------------------------------- record previous states */
prevMode = mode;
//Serial.print("Cycle Time: ");
//Serial.println(millis()-startMillis);
}

/*--------------------------------------------------------------------
  ############################# FUNCTIONS ############################
  --------------------------------------------------------------------*/
void changeMode(void) {
  mode = (rand() % numberModes)+1;
}
/*--------------------------------------------------------------------
  ############################ SCRIPT END ############################
  --------------------------------------------------------------------*/
