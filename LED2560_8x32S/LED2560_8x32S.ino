#include <FastLED.h>
#include <Wire.h>


#define ADDR           2
uint8_t brightness = 64;

#include "XYmap.h"
#include "global.h"
#include "font.h"
#include "messages.h"
#include "macros.h"
#include "paints.h"
#include "utils.h"
#include "ledFX.h"
#include "shapes.h"
#include "pulseFX.h"
#include "matFX.h"

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
  slantBars,
  simpleStrobe,
  fillNoise8,
  fire,
  BouncingBalls,
  txtA,
  txtB,
  txtC
};
const byte numFX = (sizeof(fxList)/sizeof(fxList[0]));

// Pulse Mode Function List
functionList pulseFX[] = {
  flash,//0
  flashArray,
  mFlash,
  zoneFlash,
  riderS,
  confet,//5
  fader,
  iterator,
  fun
};

void setup() {
  DBEGIN(9600);
  DPRINT("Setup");
  Wire.begin(ADDR);
  Wire.onReceive(eHandler);
  if (cFX > (numFX - 1)) cFX = 0;
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER> (leds, NUM_LEDS);
  FastLED.addLeds<CHIPSET, LED_PIN2, COLOR_ORDER> (leds, NUM_LEDS);
  FastLED.setBrightness(scale8(cBright, MAXBRIGHT) );
  xX = random16();
  yY = random16();
  zZ = random16();
}

void loop() {
  cMil = millis();
  if (!Mode) { // if autoPilot is on...
    if (cMil - cycMil > cTime) {
      cycMil = cMil;
      //if (++cFX >= numFX) cFX = 0; //upgrade, add current runtime
      fxInit = false; // trigger effect initialization when new effect is selected *****
    }
  }
  if (cMil - hMil > hTime) {
    hMil = cMil;
    hCycle(1+hueSpeed); // increment the global hue value
  }
  if (Mode) { // when pulse on..
    pulseFX[cpFX](); // cpFX
  }
  else { // when autoPilot ...
    if (cMil - fxMil > fxDelay) {
      fxMil = cMil;
      fxList[cFX]();
    }
  }
  if (Mode) {
    fadeAll(1+fadeTime); // fade out the leds after pulse
  }
  else {
    if (fxList[cFX] == confetti) fadeAll(1+fadeTime);
    //if(fxList[cFX] == theLights) fadeAll(2);
    //if(fxList[cFX] == sinelon) fadeAll(2);
    if (fxList[cFX] == bpm) fadeAll(1+fadeTime);
    if (fxList[cFX] == bouncingTrails) fadeAll(1+fadeTime);
  }  
  FastLED.show(); // send the contents of the led memory to the LEDs
}

void parseIIC() {
  int comma = received.indexOf(',');
  String typeN = received.substring(0, comma);
  String valN = received.substring(comma + 1, 5);
  int t = typeN.toInt();
  int v = valN.toInt();
  switch (t) {
    case 1: {        cur_Step = v;      }    break;
    case 2: {       if (v)Mode = 0; if (v == 2) Mode = 1;       }   break;
    case 5: {        cPalVal = v;  selPal();      }   break;
    case 6: {        cFX = v;      } break;
    case 7: {        cpFX = v;      }    break;
    case 8: {        byte Go = v; get_bits(8, Go);      } break;
    case 9: {        byte Go = v; get_bits(9, Go);      } break;
    case 10:      pFlag[0] = 1;      break;
    case 11:      pFlag[1] = 1;      break;
    case 12:      pFlag[2] = 1;      break;
    case 13:      pFlag[3] = 1;      break;
    case 14:      pFlag[4] = 1;      break;
    case 15:      pFlag[5] = 1;      break;
    case 16:      pFlag[6] = 1;      break;
    case 17:      pFlag[7] = 1;      break;
    case 20:      { hueSpeed = v; DPRINT("hue = "); DPRINTLN(v); }     break;
    case 21:      { runTime = v; DPRINT("autoRunTime = "); DPRINTLN(v); }     break;
    case 23:      { fadeTime = v; DPRINT("fadeTime = "); DPRINTLN(v); }     break;    
  }
  //DPRINT("t = ");DPRINTLN(t);DPRINT("v = ");DPRINTLN(v);
}

void eHandler(int aa) {
  while (Wire.available()) {
    char c = Wire.read();             // receive a byte as character
    received.concat(c);          //Add the character to the received string
  }
  parseIIC();
  //DPRINTLN(received);
  received = "";
}
