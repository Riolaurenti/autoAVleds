#include <FastLED.h>
#include <Wire.h>
#include <LEDMatrix.h>
#include <LEDText.h>
#include <FontMatrise.h>
/*
 * DO NOT FORGET TO UPDATE YOUR XY MAPPINGS!
 * 
 * Current Setup is for 6 8x8 Matrices, 3 in each row (see XY)
 */

#define LED_PIN        5
#define LED_PIN2       7


#include "global.h"
#include "XYmap.h"
#include "macros.h"
#include "paints.h"
#include "utils.h"
#include "ledFX.h"

//autoMode Function List
functionList fxList[] = {
  glitter,
  sideRain,
  confetti,
  theLights,
  rainbow,
  sinelon,
  bpm,
  bouncingTrails,
  threeSine,
  plasma,
  rider,
  colourFill,
  slantBars
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
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER> (leds, NUM_LEDS/2);
  FastLED.addLeds<CHIPSET, LED_PIN2, COLOR_ORDER> (leds, (NUM_LEDS/2)+1, LAST_VISIBLE_LED+1);
  FastLED.setBrightness(scale8(cBright, MAXBRIGHT) );
}

void loop() { 
 cMil = millis(); 
  
  //make analog updates here
 
  if(Mode==0){ // if autoPilot is on...
    // switch to a new effect every cycleTime milliseconds
    if (cMil - cycMil > cTime) {
      cycMil = cMil;
      if (++cFX >= numFX) cFX = 0; // loop to start of effect list
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
      fxList[cFX](); // run the selected effect function
      }
  }
  if(Mode==1){ // when pulse on..
      pulseFX[1](); //
  }
  // run a fade effects too.. 
  if (Mode==0){
    if(fxList[cFX] == confetti) fadeAll(1);
    if(fxList[cFX] == theLights) fadeAll(5);
    if(fxList[cFX] == sinelon) fadeAll(1);
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
  DPRINT(iicTable[i]);
  }
  DPRINTLN();
  switch (iicTable[0]) {
    case 1:       Mode = 0;      break;
    case 2:      Mode = 1;      break;
    case 3:    {
      cFlag=1;
      cur_Step=iicTable[1]; // receive current step integer from clock
      break;
    }
    case 4: {
      // Won't recive array's - use Push Pull on Pulse...
      }
    
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
