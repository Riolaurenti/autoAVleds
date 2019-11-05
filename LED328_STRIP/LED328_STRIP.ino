#include <FastLED.h>
#include <Wire.h>
/*
   DO NOT FORGET TO UPDATE YOUR XY MAPPINGS!
*/

#define ADDR           2

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
const byte numFX = (sizeof(fxList) / sizeof(fxList[0]));

// Pulse Mode Function List
functionList pulseFX[] = {
  flash,
  flashArray,
  mFlash,
  //zoneFlash,
  riderS,
  confet
};

void setup() {
  DBEGIN(9600);
  DPRINT("Setup");
  Wire.begin(ADDR);
  Wire.onReceive(eHandler);
  if (cFX > (numFX - 1)) cFX = 0;
    FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER> (leds, kMatrixWidth);
    FastLED.addLeds<CHIPSET, LED_PIN2, COLOR_ORDER> (leds, kMatrixWidth, kMatrixWidth);
    FastLED.addLeds<CHIPSET, LED_PIN3, COLOR_ORDER> (leds, 2 * kMatrixWidth, kMatrixWidth);
    FastLED.addLeds<CHIPSET, LED_PIN4, COLOR_ORDER> (leds, 3 * kMatrixWidth , kMatrixWidth + 1);
  FastLED.setBrightness(scale8(cBright, MAXBRIGHT) );
  setStripMode();
  DPRINTLN("..........Setup Complete");
}

void loop() {
  cMil = millis();

  //make analog updates here

  // switch to a new effect every cycleTime milliseconds
  if (cMil - cycMil > cTime) {
      cycMil = cMil;
      if (Solo == 1) if (++cFX >= numFX) cFX = 0; // loop to start of effect list
      fxInit = false; // trigger effect initialization when new effect is selected *****
    }
  if (cMil - hMil > hTime) {
      hMil = cMil;
      hCycle(1); // increment the global hue value
  }
  
  // run the currently selected effect every effectDelay milliseconds
  if (cMil - fxMil > fxDelay) {
      fxMil = cMil;
      if(stripMode) {
        for(int k = 0; k < 4; k++) {
          curStrip=k;
          if(subZone[k]){
            setStripMode();
            if(Mode) pulseFX[5]();
            else fxList[cFX];
          }
        }
      }
      else {
        if(Mode) pulseFX[5];
        else fxList[cFX]();
      }
    }
/*
  // run a fade effects too..
  if (Mode == 0) {
    //if (fxList[cFX] == confetti) fadeAll(1);
    //if(fxList[cFX] == theLights) fadeAll(2);
    //if(fxList[cFX] == sinelon) fadeAll(2);
    //if (fxList[cFX] == bpm) fadeAll(1);
    //if (fxList[cFX] == bouncingTrails) fadeAll(1);
  }
  if (Mode == 1) {
    //fadeAll(1); // fade out the leds after pulse
  }
  */
  //FastLED.show(); // send the contents of the led memory to the LEDs
}

void parseIIC() {
  int comma = received.indexOf(',');
  String typeN = received.substring(0, comma);
  String valN = received.substring(comma + 1, 5);
  int t = typeN.toInt();
  int v = valN.toInt();
  switch (t) {
    case 1: {
        cur_Step = v;
      }    break;
    case 2: {
        DPRINT("MODE");
        if (v == 1) Mode = 0; // autoPilot
        if (v == 2) Mode = 1; // Pulse Mode
      }   break;

    case 5: {
        cPalVal = v;
        selPal();
      }   break;
    case 6: {
        DPRINT(v);
        cFX = v;
      } break;
    case 7: {
        DPRINT(v);
        cpFX = v;
      }    break;
    case 8: {
        byte Go = v;
        get_bits(8, Go); // 8  = set Zones
      } break;
    case 9: {
        byte Go = v; 
        DPRINT(v);
        get_bits(9, Go); // 9 =  set subzones
        /*
        for (int i = 0; i < 4; i++) {
          if (subZone[i] == 1) {
            patternStore[i] = cFX; // my problem is probably here...
            }
        }
        */
      } break;

    case 10:      pFlag[0] = 1;      break;
    case 11:      pFlag[1] = 1;      break;
    case 12:      pFlag[2] = 1;      break;
    case 13:      pFlag[3] = 1;      break;
    case 14:      pFlag[4] = 1;      break;
    case 15:      pFlag[5] = 1;      break;
    case 16:      pFlag[6] = 1;      break;
    case 17:      pFlag[7] = 1;      break;

    case 20:      {
        for (int i = 0; i < 4; i++) {
          if (subZone[i] == 1) {
            patternStore[i] = cFX;
          }
        }
      }   break;
    case 21: {
        if (v == 0) {
          stripMode = 0;  // All Strip Mode
          setStripMode();
          DPRINTLN("LEDS INDIVIDUAL MODE");
        }
        if (v == 1) {
          stripMode = 1;  // Individual Strip Mode
          setStripMode();
          DPRINTLN("LEDS STRIP MODE");
        }
      }
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
