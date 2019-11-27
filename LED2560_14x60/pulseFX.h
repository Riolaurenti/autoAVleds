/*
    Simple Momentary Tricks
*/
void flash() { // Single Channel Pulse Example
  runCheck(30);
  if (pFlag[0] == 1) {
    for (int x = 0; x < MATRIX_WIDTH; x++) {
      for (int y = 0; y < MATRIX_Height; y++) {
        leds(x, y) = ColorFromPalette( cPal, cycHue, brightness, currentBlending);
      }
    }
  }
  pFlag[0] = 0;
}

void flashArray() { // Multi-Channel Pulse Example single Strip. (BadCode - UPDATE)
  runCheck(30);
  for (int i = 0; i < 8; i++) {
    if (pFlag[i] == 1) {
      for (int x = 0; x < MATRIX_WIDTH / 8; x++) {
        for (int y = 0; y < MATRIX_Height; y++) {
          leds(x + (i * (MATRIX_WIDTH / 8)), y) = ColorFromPalette( cPal, cycHue + (10 * i), brightness, currentBlending);
        }
      }
    }
    pFlag[i] = 0;
  }
  if (cFlag == 1) { // Clock is added single blue LED
    if (cur_Step <= NUM_LEDS - 1) {
      leds[cur_Step] = CRGB::White;
    }
  }
  cFlag = 0;
}

void mFlash() { // Multi Channel Pulse Example
  runCheck(30);
  for ( int i = 0 ; i < MATRIX_Height; i++) {
    if (pFlag[i] == 1) {
      for (int x = 0; x < MATRIX_WIDTH; x++) {
        leds(x, i) = ColorFromPalette( cPal, cycHue, brightness, currentBlending);
      }
    }
    pFlag[i] = 0;
  }
}
void zoneFlash() { // Bad example of hard colour choices - use cpal Hue + val.
  runCheck(30);
  for ( int i = 0 ; i < MATRIX_Height; i++) {
    if (pFlag[i] == 1) {
      for (int x = 0; x < MATRIX_WIDTH; x++) {
        if (i == 0)leds(x, 0)] = CRGB::White;
        if (i == 1)leds(x, 1)] = CRGB::Blue;
        if (i == 2)leds(x, 2)] = CRGB::Red;
        if (i == 3)leds(x, 3)] = CRGB::Green;
      }
    }
    pFlag[i] = 0;
  }
}

void riderS() { //Single Dash on Pulse
  static byte riderPos = 0;
  if (fxInit == false) {
    fxInit = true;
    fxDelay = 2;
    riderPos = 0;
  }
  for (int k = 0; k < 4; k++) {
    if (pFlag[k] == 1) {
      for (byte x = 0; x < MATRIX_WIDTH; x++) {
        int brightness = abs(x * (256 / MATRIX_WIDTH) - triwave8(riderPos) * 4 + 127) * 2;
        if (brightness > 255) brightness = 255;
        brightness = 255 - brightness;
        CRGB riderColor = CHSV(cycHue, 255, brightness);
        for (byte y = 0; y < MATRIX_Height; y++) {
          leds(x, k) = riderColor;
        }
      }
      riderPos++; // byte wraps to 0 at 255, triwave8 is also 0-255 periodic
      if (riderPos >= 64)riderPos = 0;
    }
    pFlag[k] = 0;
  }
}

void confet() {
  runCheck(30);
  for (int k = 0; k < 4; k++) {
    if (pFlag[k]) {
      for (int x = 0; x < MATRIX_WIDTH; x++) {
        leds(random16(MATRIX_WIDTH), k) = ColorFromPalette(cPal, random16(255), 255); //CHSV(random16(255), 255, 255);
      }
    }
    pFlag[k] = 0;
  }
}

void fader() {
  runCheck(1);
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = ColorFromPalette( cPal, cycHue);
  }
  for (int k = 0; k < 4; k++) {
    if (pFlag[k]) {
      for (int x = 0; x < MATRIX_WIDTH; x++) {
        if (k)leds(x, k) = CRGB::White;
      }
    }
    pFlag[k] = 0;
  }
}


void iterator() { // realy bad example of on frame actions
  runCheck(30);
  for (int k = 0; k < 4; k++) {
    if (pFlag[k]) {
      itXmem[k]++;
      if(itXmem[k]>=MATRIX_WIDTH){
        itXmem[k]=0;
      }
      for(int a=0;a<3;a++){
        leds(itXmem[k]+a, k) = ColorFromPalette( cPal, cycHue);  
      }
      if (itXmem[k] == 0)leds(MATRIX_WIDTH, k)] = CRGB::Black;
      else leds(itXmem[k] - 1, k) = CRGB::Black;
    }
    pFlag[k] = 0;
  }
}

void fun(){
  runCheck(30);
  int mov[] = {0,0,0,0};
  int rVal = random8(MATRIX_WIDTH);
  for (int k = 0; k < 4; k++) {
    if (pFlag[k]) {
      mov[k]++;
      if(mov[k]>=MATRIX_WIDTH/2)mov[k]=0;;
      CRGB col = CRGB(random8(),random8(),random8());
      for (int x = 0; x <rVal ; x++) {
        leds(x, k) = col;
      }
    }
    pFlag[k] = 0;
    
  }
}
