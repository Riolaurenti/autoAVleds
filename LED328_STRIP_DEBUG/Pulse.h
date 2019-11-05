/*
 * OnPulse Scripts
 */

 /*
  * Simple Momentary Tricks
  */
void flash(){ // Single Channel Pulse Example with hard colour choice
  runCheck(5);
  if (pFlag[0]==1){
   for (int x = sLED; x < nLED; x++) {
    for (int y = 0; y < kMatrixHeight; y++) {
      leds[x] = CRGB::Purple;
      } 
    }
  }
  pFlag[0]=0;
}

void flashArray(){ // Multi-Channel Pulse Example single Strip.
  runCheck(30);
  int numChan = sizeof(pFlag) ; // add controller here
  for (int i = 0; i < numChan; i++){
     if (pFlag[i]==1){
       for (int x = 0; x < nLED/numChan; x++) {
         for (int y = 0; y < kMatrixHeight; y++) {
            leds[x+(i*(nLED/numChan))] = CRGB::White;
          } 
        }
      }      
   pFlag[i]=0;
  }
  if(cFlag==1){ // Clock is added single blue LED -- COME BACK HERE LATER
        if(cur_Step<=nLED-1){
            leds[cur_Step] = CRGB::Blue;
        }
    }
   //cFlag=0;   
}

void mFlash(){ // Multi Channel Pulse Example with hard colour choice
  runCheck(30);
  for( int i = 0 ; i < kMatrixHeight;i++){
     if (pFlag[i]==1){
        for (int x = 0; x < kMatrixWidth; x++) {
          leds[XY(x,i)] = CRGB::White;
           } 
        }
      pFlag[i]=0;
  }
}
/*
void zoneFlash(){ // Call method works fine, attempt with full procedure..
  runCheck(30);
  for (int y = 0; y < kMatrixHeight; y++) {
    if (pFlag[y]==1){
       for (int x = 0; x < kMatrixWidth; x++) {
          leds[XY(x,y)] = cPalGo[y];
       } 
    }
  pFlag[y]=0;
  }
}
*/
void riderS() { //Single Dash on Pulse
  static byte riderPos = 0;
  if (fxInit == false) {
    fxInit = true;
    fxDelay = 2;
    riderPos = 0;
  }
  for(int k=0;k<4;k++){
  if(pFlag[k]==1){
    for (byte x = 0; x < kMatrixWidth; x++) {
      int brightness = abs(x * (256 / kMatrixWidth) - triwave8(riderPos) * 4 + 127) * 2;
      if (brightness > 255) brightness = 255;
        brightness = 255 - brightness;
        CRGB riderColor = CHSV(cycHue, 255, brightness);
        for (byte y = 0; y < kMatrixHeight; y++) {
          leds[XY(x, k)] = riderColor;
        }
    }
  riderPos++; // byte wraps to 0 at 255, triwave8 is also 0-255 periodic
  if(riderPos>=64)riderPos=0;
  }
  pFlag[k]=0;
}
}

void confet() {
  runCheck(40);
  for(int k=0;k<4;k++){
    if (pFlag[k]==1){
     for (int x = 0; x < kMatrixWidth; x++) {
      leds[XY(random16(kMatrixWidth), k)] = ColorFromPalette(cPal, random16(255), 255); //CHSV(random16(255), 255, 255);
     }
    }
  pFlag[k]=0;
  }
}
