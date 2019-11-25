//#include <LEDMatrix.h>

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
