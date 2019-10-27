void runCheck(int val){
  if (fxInit == false) {
    fxInit = true;
    FXdel = val;
    fxDelay = val;
  }
}
/*
 * OnPulse Scripts
 */

 /*
  * Simple Momentary Tricks
  */
void flash(){ // Single Channel Pulse Example with hard colour choice
  runCheck(30);
  if (pFlag[0]==1){
   for (int x = 0; x < kMatrixWidth; x++) {
    for (int y = 0; y < kMatrixHeight; y++) {
      leds[XY(x,y)] = CRGB::White;
      } 
    }
  }
  pFlag[0]=0;
}
void mFlash(){ // Multi Channel Pulse Example with hard colour choice
  runCheck(30);
  for( int i = 0 ; i < kMatrixHeight;i++){
     if (pFlag[i]==1){
        for (int x = 0; x < kMatrixWidth; x++) {
          for (int y = 0; y < kMatrixHeight; y++) {
            leds[XY(x+(i*kMatrixWidth),i)] = CRGB::White;
           } 
        }
      }
   pFlag[i]=0;
   }
}

void cFlash(CRGB COL){ // Single Channel Pulse Example with hard colour choice
  runCheck(30);
  if (pFlag[0]==1){
   for (int x = 0; x < kMatrixWidth; x++) {
    for (int y = 0; y < kMatrixHeight; y++) {
      leds[XY(x,y)] = COL;
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
       for (int x = 0; x < kMatrixWidth/numChan; x++) {
         for (int y = 0; y < kMatrixHeight; y++) {
            leds[XY(x+(i*(kMatrixWidth/numChan)),y)] = CRGB::White;
          } 
        }
      }      
   pFlag[i]=0;
  }
  if(cFlag==1){ // Clock is added single blue LED
        if(cur_Step<=NUM_LEDS-1){
            leds[cur_Step] = CRGB::Blue;
        }
    }
   cFlag=0;   
}

void confet(){
  runCheck(30);
  if (pFlag[0]==1){
   for (int x = 0; x < kMatrixWidth; x++) {
    for (int y = 0; y < kMatrixHeight; y++) {
      leds[XY(random16(kMatrixWidth), random16(kMatrixHeight))] = ColorFromPalette(cPal, random16(255), 255); //CHSV(random16(255), 255, 255);
      } 
    }
  }
  pFlag[0]=0;
}
void iterator() { // realy bad example of on frame actions
  runCheck(30);
  if(itX>=kMatrixWidth) itX=0;
  if(pFlag[0]==1){
    leds[itX] = CRGB::White;
    if(itX==0)leds[kMatrixWidth] = CRGB::Black;
    else leds[itX-1] = CRGB::Black;
    }
  pFlag[0]=0;
  itX++;
}



/*
 * OnScene Scripts
 */
/*
 * Old Patterns from DV2
 */
void theLights() {
  runCheck(10);
  fadeToBlackBy(&(leds[0]), NUM_LEDS, 10);
  int pos = random16(0, NUM_LEDS);
  colorIndex = (colorIndex + 10);
  if (colorIndex > 254) {
    colorIndex = 0;
  }
  leds[pos] = ColorFromPalette( cPal, colorIndex, brightness, currentBlending);
}

void rainbow() {
  runCheck(1);
  static int pHue = 0;
  static int hueStore;
    for (int i = 0; i < NUM_LEDS; i++) {
      pHue = i + cycHue;
      if (pHue > 255) {
         hueStore = pHue - 255;
         pHue = hueStore;
      }
    leds[i] = ColorFromPalette(cPal, pHue, brightness, currentBlending);
  }
}
void sinelon() {
   runCheck(10);
  fadeToBlackBy(&(leds[0]), NUM_LEDS, 20);
  int pos = beatsin16( 13, 0, NUM_LEDS - 1 ) ;
  colorIndex++;
  if (colorIndex > 254) { // maybe further reduce by making colorIndex cycHue? Or a global timer
    colorIndex = 0;
  }
  leds[pos] = ColorFromPalette( cPal, colorIndex, brightness, currentBlending);
}

void bpm() {
  runCheck(10);
  uint8_t beat = beatsin8( 62, 64, 255);
  for (int i = 0; i < NUM_LEDS; i++) { 
    EVERY_N_MILLISECONDS(20){
     colorIndex++; //not necessary...
     if (colorIndex > 254) {//not necessary...
      colorIndex = 0;//not necessary...
     }
    }
    leds[i] = ColorFromPalette(cPal, colorIndex + (i * 2), beat - 0 + (i * 10));
    }
}


void bouncingTrails(){ // this is some messy code - will come back to it...
   runCheck(10);
  //sets a "spawn" in the middle half of a strip then sends a trail in either direction which bounces of the ends of the strip.
  static int counter=0;//used to set a start point at 1
  static int lastCount=0;//i use this to be able to tell when the counter has increased. (had problems with if(counter++))
  static int paletteRef=0;//the number of the color, in the palette, to set.
  static int posUp=0;//holds the light that goes up the strip
  static int posDown=0;//holds the light that goes down the strip
  static byte upReversed=0;//if up hits the top of the strip, sets this to 1 and and runs back down the strip
  static byte downReversed=0;//as above, in reverse
  static int pos=0;//holds the initial position from which the two trails emerge
  counter++;
  if (counter==(kMatrixWidth*4)){//used a multiple of 2 so that a new point s formed when the two trails are close to each other (looks better in my opinon)
    counter=0;
  }
  if (lastCount!=counter){//if the counter has progressed
    //Run a fadeAll flag
    paletteRef=(counter*5);//used a multiple here as we want to adress as broad a rang from 0 - 256 as possible, with more LEDs be worth lowering this value.
  }
  if ((counter==1)&&(lastCount!=counter)){   
    pos = random16((kMatrixWidth/4),((kMatrixWidth/4)*3));//if on count 1, set the spawn, and clear the reversed states.
    downReversed=0;    upReversed=0;    posUp=pos;    posDown=pos;
    for (int i = 0; i < kMatrixHeight; i++){
        leds[(pos+(i*kMatrixWidth))]=ColorFromPalette( cPal, paletteRef, brightness, currentBlending);
    }
  }  
    if ((counter!=1)&&(lastCount!=counter)){//this set of if statements increment the trailing dots, and tarcks if they are reversed
    switch (upReversed){
      case  0:
        if(posUp!=kMatrixWidth-1){          posUp++;
          break;
        }
        else{          upReversed=1;          posUp--;
          break;
        }
      case 1:
        if(posUp!=0){          posUp--;
          break;
        }
        else{          upReversed=0;      posUp++;
          break;
        }
    }
    switch (downReversed){
      case 0:
        if (posDown!=0){          posDown--;
          break;
        }
        else{          downReversed=1;          posDown++;
          break;
        }
      case 1:
        if (posDown!=kMatrixWidth-1){          posDown++;
          break;
        }
        else{          downReversed=0;          posDown--;
          break;
        }
    }
    for (int i = 0; i < kMatrixHeight; i++){
        leds[(posUp+(i*kMatrixWidth))]=ColorFromPalette( cPal, paletteRef,  brightness, currentBlending);
        leds[(posDown+(i*kMatrixWidth))]=ColorFromPalette( cPal, paletteRef, brightness, currentBlending);
    }
  }
  lastCount=counter;
}
/* NOT WORK!
void palLoop() {
  runCheck(30);
  for(int j=0;j<3;j++){
      for(int k=0;k<256;k++){
        switch(j){
          case 0: setAll(k,0,0); break;
          case 1: setAll(0,k,0); break;
          case 2: setAll(0,0,k); break;
        }
      }
    for(int k=255;k>=0;k--){
        switch(j){
          case 0: setAll(k,0,0); break;
          case 1: setAll(0,k,0); break;
          case 2: setAll(0,0,k); break;
        }
      }
  }
}
*/ 

///also not working!
void BouncingBalls(byte red, byte green, byte blue, int BallCount) {
  runCheck(50);
  float Gravity = -9.81;
  int StartHeight = 1;
  float Height[BallCount];
  float ImpactVelocityStart = sqrt( -2 * Gravity * StartHeight );
  float ImpactVelocity[BallCount];
  float TimeSinceLastBounce[BallCount];
  int   Position[BallCount];
  long  ClockTimeSinceLastBounce[BallCount];
  float Dampening[BallCount];
  
  for (int i = 0 ; i < BallCount ; i++) {  
    ClockTimeSinceLastBounce[i] = millis();
    Height[i] = StartHeight;
    Position[i] = 0;
    ImpactVelocity[i] = ImpactVelocityStart;
    TimeSinceLastBounce[i] = 0;
    Dampening[i] = 0.90 - float(i)/pow(BallCount,2);
  }

  while (true) {
    for (int i = 0 ; i < BallCount ; i++) {
      TimeSinceLastBounce[i] =  millis() - ClockTimeSinceLastBounce[i];
      Height[i] = 0.5 * Gravity * pow( TimeSinceLastBounce[i]/1000 , 2.0 ) + ImpactVelocity[i] * TimeSinceLastBounce[i]/1000;
 
      if ( Height[i] < 0 ) {                      
        Height[i] = 0;
        ImpactVelocity[i] = Dampening[i] * ImpactVelocity[i];
        ClockTimeSinceLastBounce[i] = millis();
 
        if ( ImpactVelocity[i] < 0.01 ) {
          ImpactVelocity[i] = ImpactVelocityStart;
        }
      }
      Position[i] = round( Height[i] * (NUM_LEDS - 1) / StartHeight);
    }
 
    for (int i = 0 ; i < BallCount ; i++) {
      setPixel(Position[i],red,green,blue);
    } 
    //setAll(0,0,0);
  }
}


/*
 * Frame By Frame +  Other Animations
 */
void threeSine() {
  static byte sineOffset = 0; // counter for current position of sine waves
  runCheck(20);
  for (byte x = 0; x < kMatrixWidth; x++) {
    for (int y = 0; y < kMatrixHeight; y++) {
      byte sinDistanceR = qmul8(abs(y * (255 / kMatrixHeight) - sin8(sineOffset * 9 + x * 16)), 2);
      byte sinDistanceG = qmul8(abs(y * (255 / kMatrixHeight) - sin8(sineOffset * 10 + x * 16)), 2);
      byte sinDistanceB = qmul8(abs(y * (255 / kMatrixHeight) - sin8(sineOffset * 11 + x * 16)), 2);
      leds[XY(x, y)] = CRGB(255 - sinDistanceR, 255 - sinDistanceG, 255 - sinDistanceB);
    }
  }
  sineOffset++; // byte will wrap from 255 to 0, matching sin8 0-255 cycle
}

void plasma() {
  static byte offset  = 0; // counter for radial color wave motion
  static int plasVector = 0; // counter for orbiting plasma center
  runCheck(10);
  int xOffset = cos8(plasVector / 256);
  int yOffset = sin8(plasVector / 256);
  for (int x = 0; x < kMatrixWidth; x++) {
    for (int y = 0; y < kMatrixHeight; y++) {
      byte color = sin8(sqrt(sq(((float)x - 7.5) * 10 + xOffset - 127) + sq(((float)y - 2) * 10 + yOffset - 127)) + offset);
      leds[XY(x, y)] = CHSV(color, 255, 255);
    }
  }
  offset++; // wraps at 255 for sin8
  plasVector += 16; // using an int for slower orbit (wraps at 65536)
}

void rider() {
  static byte riderPos = 0;
  if (fxInit == false) {
    fxInit = true;
    fxDelay = 5;
    riderPos = 0;
  }
  for (byte x = 0; x < kMatrixWidth; x++) {
    int brightness = abs(x * (256 / kMatrixWidth) - triwave8(riderPos) * 2 + 127) * 3;
    if (brightness > 255) brightness = 255;
    brightness = 255 - brightness;
    CRGB riderColor = CHSV(cycHue, 255, brightness);
    for (byte y = 0; y < kMatrixHeight; y++) {
      leds[XY(x, y)] = riderColor;
    }
  }
  riderPos++; // byte wraps to 0 at 255, triwave8 is also 0-255 periodic
}

void colourFill() {
   fadeToBlackBy(&(leds[0]), NUM_LEDS, 20); // keep or not?
  static byte currentColor = 0;
  static byte currentRow = 0;
  static byte currentDirection = 0;
  if (fxInit == false) {
    fxInit = true;
    fxDelay = 45;
    currentColor = 0;
    currentRow = 0;
    currentDirection = 0;
    cPal = RainbowColors_p;
  }
  // test a bitmask to fill up or down when currentDirection is 0 or 2 (0b00 or 0b10)
  if (!(currentDirection & 1)) {
    fxDelay = 45; // slower since vertical has fewer pixels
    for (byte x = 0; x < kMatrixWidth; x++) {
      byte y = currentRow;
      if (currentDirection == 2) y = kMatrixHeight - 1 - currentRow;
      leds[XY(x, y)] = cPal[currentColor];
    }
  }
  // test a bitmask to fill left or right when currentDirection is 1 or 3 (0b01 or 0b11)
  if (currentDirection & 1) {
    fxDelay = 20; // faster since horizontal has more pixels
    for (byte y = 0; y < kMatrixHeight; y++) {
      byte x = currentRow;
      if (currentDirection == 3) x = kMatrixWidth - 1 - currentRow;
      leds[XY(x, y)] = cPal[currentColor];
    }
  }
  currentRow++;
  // detect when a fill is complete, change color and direction
  if ((!(currentDirection & 1) && currentRow >= kMatrixHeight) || ((currentDirection & 1) && currentRow >= kMatrixWidth)) {
    currentRow = 0;
    currentColor += random8(3, 6);
    if (currentColor > 15) currentColor -= 16;
    currentDirection++;
    if (currentDirection > 3) currentDirection = 0;
    fxDelay = 300; // wait a little bit longer after completing a fill
  }
}

void slantBars() {
  static byte slantPos = 0;
  runCheck(5);
  for (byte x = 0; x < kMatrixWidth; x++) {
    for (byte y = 0; y < kMatrixHeight; y++) {
      leds[XY(x, y)] = CHSV(cycHue, 255, quadwave8(x * 32 + y + slantPos));
    }
  }
  slantPos -= 4;
}

void glitter() {
  runCheck(30);
  for (int x = 0; x < kMatrixWidth; x++) {
    for (int y = 0; y < kMatrixHeight; y++) {
      leds[XY(x, y)] = CHSV(cycHue, 255, random8(5) * 63);
    }
  }
}

#define rainDir 0
void sideRain() {
  runCheck(15);
  scrollArray(rainDir);
  byte randPixel = random8(kMatrixHeight);
  for (byte y = 0; y < kMatrixHeight; y++) leds[XY((kMatrixWidth - 1) * rainDir, y)] = CRGB::Black;
   leds[XY((kMatrixWidth - 1)*rainDir, randPixel)] = CHSV(cycHue, 255, 255);  
}

void confetti() {
  runCheck(30);
  //selectRandomPalette();
  // scatter random colored pixels at several random coordinates
  for (byte i = 0; i < 4; i++) {
    leds[XY(random16(kMatrixWidth), random16(kMatrixHeight))] = ColorFromPalette(cPal, random16(255), 255); //CHSV(random16(255), 255, 255);
    }
}

/*
 * Noise Code
 */

 /*
void mapNoiseToLEDsUsingPalette()
{
  static uint8_t ihue=0;
  for(int i = 0; i < kMatrixWidth; i++) {
    for(int j = 0; j < kMatrixHeight; j++) {
      // We use the value at the (i,j) coordinate in the noise
      // array for our brightness, and the flipped value from (j,i)
      // for our pixel's index into the color palette.
      uint8_t index = noise[j][i];
      uint8_t bri =   noise[i][j];
      // if this palette is a 'loop', add a slowly-changing base value
      if( colorLoop) { 
        index += ihue;
      }
      // brighten up, as the color palette itself often contains the 
      // light/dark dynamic range desired
      if( bri > 127 ) {
        bri = 255;
      } else {
        bri = dim8_raw( bri * 2);
      }
      CRGB color = ColorFromPalette( cPal, index, bri);
      leds[XY(i,j)] = color;
    }
  }
  ihue+=1;
}
void fillNoise8() {
  uint8_t dataSmoothing = 0;
  if( speed < 50) {
    dataSmoothing = 200 - (speed * 4);
  }  
  for(int i = 0; i < MAX_DIMENSION; i++) {
    int ioffset = scale * i;
    for(int j = 0; j < MAX_DIMENSION; j++) {
      int joffset = scale * j;
   
      uint8_t data = inoise8(xX + ioffset,yY + joffset,zZ);
      // The range of the inoise8 function is roughly 16-238.
      // These two operations expand those values out to roughly 0..255
      // You can comment them out if you want the raw noise data.
      data = qsub8(data,16);
      data = qadd8(data,scale8(data,39));

      if( dataSmoothing ) {
        uint8_t olddata = noise[i][j];
        uint8_t newdata = scale8( olddata, dataSmoothing) + scale8( data, 256 - dataSmoothing);
        data = newdata;
      }
      noise[i][j] = data;
    }
  }
  zZ += speed;
  // apply slow drift to X and Y, just for visual variation.
  xX += speed / 8;
  yY -= speed / 16;
  mapNoiseToLEDsUsingPalette();
}
*/
void fire()
{
  static byte heat[NUM_LEDS];
    for( int i = 0; i < NUM_LEDS; i++) {
      heat[i] = qsub8( heat[i],  random(0, ((COOLING * 10) / NUM_LEDS) + 2));
    }
    for( int k= NUM_LEDS - 1; k >= 2; k--) {
      heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
    }
    if( random() < SPARKING ) {
      int y = random(7);
      heat[y] = qadd8( heat[y], random(160,255) );
    }
    for( int j = 0; j < NUM_LEDS; j++) {
      byte colorindex = scale8( heat[j], 240);
      CRGB color = ColorFromPalette( cPal, colorindex);
      int pixelnumber;
      if( gReverseDirection ) {
        pixelnumber = (NUM_LEDS-1) - j;
      } else {
        pixelnumber = j;
      }
      leds[pixelnumber] = color;
    }
}

/*
 * Strobe Code!
 */
 
static void strobeDraw( uint8_t startpos, uint16_t lastpos, uint8_t period, uint8_t width, uint8_t huestart, uint8_t huedelta, uint8_t saturation, uint8_t value) {
  uint8_t hue = huestart;
  for ( uint16_t i = startpos; i <= lastpos; i += period) {
    CRGB color = CHSV( hue, saturation, value);
    //CRGB color = CRGB::Blue; // USE TO COMPLETELY BYPASS HSV Change Scheme
    uint16_t pos = i;
    for ( uint8_t w = 0; w < width; w++) {
      leds[pos] = ColorFromPalette( cPal, colorIndex, brightness, currentBlending);
      pos++;
      if ( pos >= NUM_LEDS) {
        break;
      }
    }
    hue += huedelta;
  }
}
void strobeCore(uint8_t dashperiod, uint8_t dashwidth, int8_t  dashmotionspeed, uint8_t stroberepeats, uint8_t huedelta) {
  static uint8_t sRepeatCounter = 0;
  static int8_t sStartPosition = 0;
  static uint8_t sStartHue = 0;
  sStartHue += 1; //Shift the Colour little by little
  sRepeatCounter = sRepeatCounter + 1;
  if ( sRepeatCounter >= stroberepeats) {
    sRepeatCounter = 0;
    sStartPosition = sStartPosition + dashmotionspeed;
    if ( sStartPosition >= dashperiod ) {
      while ( sStartPosition >= dashperiod) {
        sStartPosition -= dashperiod;
      }
      sStartHue  -= huedelta;
    }
    else if ( sStartPosition < 0) {
      while ( sStartPosition < 0) {
        sStartPosition += dashperiod;
      }
      sStartHue  += huedelta;
    }
  }
  const uint8_t kSaturation = 208; // WHITE >> CURRENT COLOUR control (def 208)
  const uint8_t kValue = 200; // Brightness??
  strobeDraw( sStartPosition, NUM_LEDS - 1, dashperiod, dashwidth, sStartHue, huedelta, kSaturation, kValue);
}
void simpleStrobe () {
  runCheck(20);
  fill_solid( leds, NUM_LEDS, CRGB::Black);
  const uint8_t kStrobeCycleLength = 4; // light every Nth frame
  static uint8_t sStrobePhase = 0;
  sStrobePhase = sStrobePhase + 1;
  colorIndex++;
  if (colorIndex > 256) {
    colorIndex = 1;
  }
  if ( sStrobePhase >= kStrobeCycleLength ) {
    sStrobePhase = 0;
  }
  if ( sStrobePhase == 0 ) {
    uint8_t dashperiod = beatsin8( 8, 4, 10);
    uint8_t dashwidth = (dashperiod / 4) + 1;
    uint8_t zoomBPM = STROBE_BEATS_PER_MINUTE;
    int8_t  dashmotionspeed = beatsin8( (zoomBPM / 2), 1, dashperiod);
    if ( dashmotionspeed >= (dashperiod / 2)) {
      dashmotionspeed = 0 - (dashperiod - dashmotionspeed );
    }
    uint8_t cycle = beat8(2); // two cycles per minute
    uint8_t easedcycle = ease8InOutCubic( ease8InOutCubic( cycle));
    uint8_t wavecycle = cubicwave8( easedcycle);
    //uint8_t hueShift = 0; // NO SHIFT OF HUE IN COLOUR (we should rebuild in RGB...)
    uint8_t hueShift = scale8( wavecycle, 130); // METHOD HOW HUE VALUE SHIFTS
    uint8_t strobesPerPosition = 2; // try 1..4
    strobeCore( dashperiod, dashwidth, dashmotionspeed, strobesPerPosition, hueShift);
  }
 // FastLED.delay(myDelay/4);
}
