#include <FastLED.h>
#include <Wire.h>

#define ADDR           2
#include "XYmap.h"
#include "global.h"
#include "macros.h"
#include "paints.h"
#include "controls.h"
#include "utils.h"
#include "ledFX.h"
#include "Pulse.h"

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
    FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER> (leds, kMatrixWidth);
    FastLED.addLeds<CHIPSET, LED_PIN2, COLOR_ORDER> (leds, kMatrixWidth, kMatrixWidth);
    FastLED.addLeds<CHIPSET, LED_PIN3, COLOR_ORDER> (leds, 2*kMatrixWidth, kMatrixWidth);
    FastLED.addLeds<CHIPSET, LED_PIN4, COLOR_ORDER> (leds, 3*kMatrixWidth ,kMatrixWidth + 1);
  //FastLED.setBrightness(scale8(cBright, MAXBRIGHT) );
  setStripMode();
  DPRINTLN("..........Setup Complete");
}

void loop() {
  EVERY_N_SECONDS(1) {
    hCycle(1); // increment the global hue value
  }
  EVERY_N_SECONDS(5) {
   // randPat();
  }
  if(Mode==1)pulseFX[0]();
  else selPat();
  
FastLED.show();
//FastLED.delay(1000 / FRAMES_PER_SECOND);
  /*
  FastLED[0].showLeds(64);
  FastLED[1].showLeds(64);
  FastLED[2].showLeds(64);
  FastLED[3].showLeds(64);
*/
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
        if(stripMode){
          for(int i = 0 ; i < 4 ; i++) {
            if(subZone[i]){
              pArr[i]=v;
            }      
          DPRINT(pArr[i]);
          DPRINT("-");
          } 
          DPRINTLN();          
        }
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
        get_bits(9, Go); // 9 =  set subzones
      } break;

    case 10:      pFlag[0] = 1;      break;
    case 11:      pFlag[1] = 1;      break;
    case 12:      pFlag[2] = 1;      break;
    case 13:      pFlag[3] = 1;      break;
    case 14:      pFlag[4] = 1;      break;
    case 15:      pFlag[5] = 1;      break;
    case 16:      pFlag[6] = 1;      break;
    case 17:      pFlag[7] = 1;      break;

    case 20:      {       }   break;
    case 21: {
        if (v) {
          stripMode = 1;  
          setStripMode();
          DPRINTLN("LEDS Strip MODE");
        }
        if (v == 0) {
          stripMode = 0;  
          setStripMode();
          DPRINTLN("LEDS Normal MODE");
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
