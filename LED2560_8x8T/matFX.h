#include <LEDMatrix.h>

void autoShapes(){
  runCheck(10);
  int xA,yA,xB,yB;
  xA = random8(0,kMatrixWidth); xB = random8(xA,kMatrixWidth);
  yA = random8(0,kMatrixHeight); yB = random8(yA,kMatrixHeight);
  switch(shape){
    case 0: { drawRectangle(xA,xB,xB,yB,cPal); } break;
  }
  
  //leds[pos] = ColorFromPalette( cPal, cycHue, brightness, currentBlending);
}


/*
 * TEXT Code - Set messages in messages.h
 * ToDo: Receive String (Next iteration with pJon)
 */

#define NORMAL 0
#define RAINBOW 1
#define charSpacing 2
void scrollText(byte message, byte style, CRGB fgColor, CRGB bgColor) {
  static byte currentMessageChar = 0;
  static byte currentCharColumn = 0;
  static byte paletteCycle = 0;
  static CRGB currentColor;
  static byte bitBuffer[16] = {0};
  static byte bitBufferPointer = 0;
  if (fxInit == false) {
    fxInit = true;
    fxDelay = 35;
    currentMessageChar = 0;
    currentCharColumn = 0;
    selectFlashString(message);
    loadCharBuffer(loadStringChar(message, currentMessageChar));
    cPal = RainbowColors_p; //  Debug
    for (byte i = 0; i < kMatrixWidth; i++) bitBuffer[i] = 0;
  }

  paletteCycle += 15;
  if (currentCharColumn < 8) { // characters are 8 pixels wide
    bitBuffer[(bitBufferPointer + kMatrixWidth - 1) % kMatrixWidth] = charBuffer[currentCharColumn]; // character
  } else {
    bitBuffer[(bitBufferPointer + kMatrixWidth - 1) % kMatrixWidth] = 0; // space
  }
  CRGB pixelColor;
  for (byte x = 0; x < kMatrixWidth; x++) {
    for (byte y = 0; y < 8; y++) { // characters are 8 pixels tall
      if (bitRead(bitBuffer[(bitBufferPointer + x) % kMatrixWidth], y) == 1) {
        if (style == RAINBOW) {
          pixelColor = ColorFromPalette(cPal, paletteCycle+y*16, 255);
        } else {
          pixelColor = fgColor;
        }
      } else {
        pixelColor = bgColor;
      }
      leds[XY(x, y)] = pixelColor;
    }
  }
  currentCharColumn++;
  if (currentCharColumn > (4 + charSpacing)) {
    currentCharColumn = 0;
    currentMessageChar++;
    char nextChar = loadStringChar(message, currentMessageChar);
    if (nextChar == 0) { // null character at end of strong
      currentMessageChar = 0;
      nextChar = loadStringChar(message, currentMessageChar);
    }
    loadCharBuffer(nextChar);
  }
  bitBufferPointer++;
  if (bitBufferPointer > 15) bitBufferPointer = 0;
}

void txtA() {
  scrollText(0, NORMAL, CRGB::Red, CRGB::Black);
}
void txtB() {
  scrollText(1, RAINBOW, 0, CRGB::Black);
}
void txtC() {
  scrollText(2, NORMAL, CRGB::Green, CRGB(0,0,8));
}

/*
 * Test me!
 */

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

void fire()
{
  static byte heat[NUM_LEDS];
    for( int i = 0; i < NUM_LEDS; i++) {
      heat[i] = qsub8( heat[i],  random8(0, ((COOLING * 10) / NUM_LEDS) + 2));
    }
    for( int k= NUM_LEDS - 1; k >= 2; k--) {
      heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
    }
    if( random8() < SPARKING ) {
      int y = random8(7);
      heat[y] = qadd8( heat[y], random8(160,255) );
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
