void runCheck(int val){
  if (fxInit == false) {
    fxInit = true;
    fxDelay = val;
  }
}

void get_bits(int type, int val){
  for(int j=0;j<4;j++){
    byte i = bitRead(val,j);
    if(type==8 && j==ourAddr){      Zone = i;      }
    if(type==9 ){      subZone[j] = i;    }
    //if(type==20){      zVals[j]=i;      }
    DPRINT(i);  
  }  
  DPRINTLN();
  DPRINT(subZone[0]);DPRINT(subZone[1]);DPRINT(subZone[2]);DPRINT(subZone[3]); DPRINTLN();
}

void setStripMode(){
  if(stripMode){
    nLED=NUM_PER_STRIP;
    for(int i=0;i<NUM_STRIPS;i++){
      if(curStrip==i){
        sLED = (NUM_PER_STRIP*i);
        eLED = (NUM_PER_STRIP*(i+1));
       }
    }
  }
  else {
    nLED = NUM_LEDS;
    sLED = 0;
    eLED = LAST_VISIBLE_LED;
  }
}

/*
 * When stripNumber changes... / patternNumber 
 * patternStore[stripNumber]=patternNumber;
 */

 
// Increment the global hue value for functions that use it
byte cycHue = 0;
byte cycHueCount = 0;
void hCycle(byte incr) {
    cycHueCount = 0;
    cycHue+=incr;
}

// Set every LED in the array to a specified color
void fillAll(CRGB fillColor) {
  for (byte i = 0; i < NUM_LEDS; i++) {
    leds[i] = fillColor;
  }
}
void setAll(byte r, byte g, byte b) {
  for (byte i = 0; i < NUM_LEDS; i++) {
    leds[i].setRGB(r,g,b);
  }
}
void setPixel(int Pixel, byte red, byte green, byte blue){ 
   leds[Pixel].r = red;
   leds[Pixel].g = green;
   leds[Pixel].b = blue;
}
// Fade every LED in the array by a specified amount
void fadeAll(byte fadeIncr) {
  for (byte i = 0; i < NUM_LEDS; i++) {
    leds[i] = leds[i].fadeToBlackBy(fadeIncr);
  }
}

// Shift all pixels by one, right or left (0 or 1)
void scrollArray(byte scrollDir) {
    byte scrollX = 0;
    for (byte x = 1; x < kMatrixWidth; x++) {
      if (scrollDir == 0) {
        scrollX = kMatrixWidth - x;
      } else if (scrollDir == 1) {
        scrollX = x - 1;
      }
      
      for (byte y = 0; y < kMatrixHeight; y++) {
        leds[XY(scrollX,y)] = leds[XY(scrollX + scrollDir*2 - 1,y)];
      }
    }
}
// Pick a palette from Host Int
void selPal() {
  switch(cPalVal) {
    case 0:    cPal = CloudColors_p;    break;
    case 1:     cPal = LavaColors_p;    break;
    case 2:    cPal = OceanColors_p;    break;
    case 4:    cPal = ForestColors_p;    break;
    case 5:    cPal = RainbowColors_p;    break;    
    case 6:    cPal = PartyColors_p;    break;    
    case 7:    cPal = HeatColors_p;    break;
    case 8:    cPal = Pastel1_08_gp;    break;
    case 9:    cPal = Paired_08_gp;    break;
    case 10:    cPal = Dark2_08_gp;    break;
    case 11:    cPal = RdYlGn_08_gp;    break;
    case 12:    cPal = RdYlBu_08_gp;    break;
    case 13:    cPal = RdBu_08_gp;    break;
    case 14 :    cPal = PuOr_08_gp;    break;
    case 15:    cPal = PRGn_08_gp;    break;
    case 16:    cPal = Fuschia_8_gp;      break;
    case 17:      cPal = saga_07_gp;      break;
    case 18:      cPal = saga_08_gp;      break;
    case 19:      cPal = saga_09_gp;      break;
    case 20:      cPal = saga_10_gp;      break;
    case 21:      cPal = saga_11_gp;      break;
    case 22:      cPal = saga_12_gp;      break;
    case 23:      cPal = saga_13_gp;      break;
    case 24:      cPal = saga_14_gp;      break;
    case 25:      cPal = saga_15_gp;      break;
    case 26:      cPal = saga_17_gp;      break;    
    }
   // DPRINT("pallete = ");
   // DPRINTLN(cPalVal);
}
void randPat() {//choses a random pattern
  if (stripMode==0){
    cFX = random(2, 10);
    }
    if (stripMode!=0){
    byte lStrip=curStrip;
    for(int i=0;i<4;i++){
      if (i==curStrip){
        pArr[i]=random(2,10);
      }
    }
    curStrip=lStrip;
  }
}
