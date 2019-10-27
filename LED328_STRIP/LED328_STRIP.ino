#include <FastLED.h>
#include <Wire.h>
/*
 * DO NOT FORGET TO UPDATE YOUR XY MAPPINGS!
 */

#define LED_PIN        3
#define LED_PIN2       4
#define LED_PIN3       5
#define LED_PIN4       6

#include "XYmap.h"
#include "global.h"
#include "macros.h"
#include "paints.h"
#include "utils.h"
#include "ledFX.h"

//autoMode Function List
functionList fxList[] = {
  glitter, //0
  sideRain, //1
  confetti,//2
  theLights,//3
  rainbow, //4
  sinelon, //5
  bpm, //6
  bouncingTrails, //7
  threeSine, //8
  plasma, //9
  rider, //10
  colourFill, //11
  slantBars, //12
  simpleStrobe, //13
  theLights, // fillNoise8, 14
  theLights, // fire not working (15)
  theLights ,  //palLoop, //16
  theLights,//  BouncingBalls, //17
  theLights, // for txt1 18
  theLights, // for txt2 19
  theLights // for txt3 //20
};
const byte numFX = (sizeof(fxList)/sizeof(fxList[0]));

// Pulse Mode Function List
functionList pulseFX[] = {
  flash,
  flashArray,
};

void setup() {
  DBEGIN(9600);
  DPRINT("Setup");
  Wire.begin(ADDR);
  Wire.onReceive(eHandler);
  if (cFX > (numFX - 1)) cFX = 0;
  if(kMatrixHeight==1){
    FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER> (leds, LAST_VISIBLE_LED + 1);
    DPRINT("1 strip");
  }
  else if(kMatrixHeight==4){
    FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER> (leds, kMatrixWidth);
    FastLED.addLeds<CHIPSET, LED_PIN2, COLOR_ORDER> (leds, kMatrixWidth, kMatrixWidth);
    FastLED.addLeds<CHIPSET, LED_PIN3, COLOR_ORDER> (leds, 2*kMatrixWidth, kMatrixWidth);
    FastLED.addLeds<CHIPSET, LED_PIN4, COLOR_ORDER> (leds, 3*kMatrixWidth ,kMatrixWidth + 1);
    DPRINT("4 strips");
  }
  FastLED.setBrightness(scale8(cBright, MAXBRIGHT) );
}

void loop() { 
 cMil = millis(); 
  
  //make analog updates here
 
  if(Mode==0){ // if autoPilot is on...
    // switch to a new effect every cycleTime milliseconds
    if (cMil - cycMil > cTime) {
      cycMil = cMil;
      if(Solo==1)if (++cFX >= numFX) cFX = 0; // loop to start of effect list 
      fxInit = false; // trigger effect initialization when new effect is selected *****
    }
  }
  if (cMil - hMil > hTime) {
    hMil = cMil;
    hCycle(1); // increment the global hue value
  }
  if(Mode==0) { // when autoPilot ... 
    // run the currently selected effect every effectDelay milliseconds
    if (cMil - fxMil > fxDelay) {
      fxMil = cMil;
      fxList[11](); // run the selected effect function
      }
  }
  if(Mode==1){ // when pulse on..
      pulseFX[cpFX](); //
  }
  // run a fade effects too.. 
  if (Mode==0){
    if(fxList[cFX] == confetti) fadeAll(1);
    //if(fxList[cFX] == theLights) fadeAll(2);
    //if(fxList[cFX] == sinelon) fadeAll(2);
    if(fxList[cFX] == bpm) fadeAll(1);
    if(fxList[cFX] == bouncingTrails) fadeAll(1);
  }
  if (Mode==1){
    fadeAll(1); // fade out the leds after pulse
  }
  FastLED.show(); // send the contents of the led memory to the LEDs
}


void eHandler(int aa) {
  int i =0;
  while (Wire.available()) {
  iicTable[i] = Wire.read();    // receive byte as an integer
  i=i+1;
  //DPRINT("IC = ");
  //DPRINTLN(iicTable[i]);
  }
  //DPRINTLN();
  switch (iicTable[0]) {
    case 1:       Mode = 0;      break;
    case 2:      Mode = 1;      break;
    case 3:    { // receive current step integer from clock
      cFlag=1;
      cur_Step=iicTable[1]; 
      break;
    }
    case 4: {  // Is this Controller Primary or Secondary?
      for(int i=0;i<sizeof(ioRule);i++){
        ioRule[i]=iicTable[i+1];
        iAm=ioRule[0]; //(use to change Mode if non auto is on - dont be fooled by current clk control)
        Mode = iAm ; //Temporary placeholder, use if(auto mode = 0 and zone ctrl = 1)
        //DPRINT(ioRule[i]);
      }
      break;
    }
    case 5:      {
      cPalVal = iicTable[1];
      selPal();
      //DPRINT("OK");
    } break; //get cPal
    
    case 6:       cFX = iicTable[1]; break; //get cFX
    case 7:       cpFX = iicTable[1]; break; //get cpFX (merge into message case #6)
    
    case 10:      pFlag[0] = 1;      break;
    case 11:      pFlag[1] = 1;      break;
    case 12:      pFlag[2] = 1;      break;
    case 13:      pFlag[3] = 1;      break;
    case 14:      pFlag[4] = 1;      break;
    case 15:      pFlag[5] = 1;      break;
    case 16:      pFlag[6] = 1;      break;
    case 17:      pFlag[7] = 1;      break;
    
  }
}
