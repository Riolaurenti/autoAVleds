// Global variables
boolean fxInit = false; // indicates if a pattern has been recently switched
uint16_t fxDelay = 0; // time between automatic effect changes
uint16_t FXdel = 0;
unsigned long fxMil = 0; // store the time of last effect function run
unsigned long cycMil = 0; // store the time of last effect change
unsigned long cMil; // store current loop's millis value
unsigned long hMil; // store time of last hue change
unsigned long cFXmil; // store current loop's millis value
unsigned long FXmil; // store time of last hue change
byte cFX = 0; // index to the currently running effect
byte cBright = STARTBRIGHT; // 0-255 will be scaled to 0-MAXBRIGHTNESS

CRGBPalette16 cPal(RainbowColors_p); // global palette storage

typedef void (*functionList)(); // definition for list of effect function pointers
extern const byte numFX;

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

// Fade every LED in the array by a specified amount
void fadeAll(byte fadeIncr) {
  for (byte i = 0; i < NUM_LEDS; i++) {
    leds[i] = leds[i].fadeToBlackBy(fadeIncr);
  }
}
void fadeCustom(byte fadeIncr) {
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


// Pick a random palette from a list
void selectRandomPalette() {
  switch(random8(8)) {
    case 0:    cPal = CloudColors_p;
    break;
    case 1:     cPal = LavaColors_p;
    break;
    case 2:    cPal = OceanColors_p;
    break;
    case 4:    cPal = ForestColors_p;
    break;
    case 5:    cPal = RainbowColors_p;
    break;    
    case 6:    cPal = PartyColors_p;
    break;    
    case 7:    cPal = HeatColors_p;
    break;
    case 8:    cPal = Pastel1_08_gp;
    break;
    case 9:    cPal = Paired_08_gp;
    break;
    case 10:    cPal = Dark2_08_gp;
    break;
    case 11:    cPal = RdYlGn_08_gp;
    break;
    case 12:    cPal = RdYlBu_08_gp;
    break;
    case 13:    cPal = RdBu_08_gp;
    break;
    case 14 :    cPal = PuOr_08_gp;
    break;
    case 15:    cPal = PRGn_08_gp;
    break;
    case 16:    cPal = Fuschia_8_gp;
      break;
    case 17:      cPal = saga_07_gp;
      break;
    case 18:      cPal = saga_08_gp;
      break;
    case 19:      cPal = saga_09_gp;
      break;
    case 20:      cPal = saga_10_gp;
      break;
    case 21:      cPal = saga_11_gp;
      break;
    case 22:      cPal = saga_12_gp;
      break;
    case 23:      cPal = saga_13_gp;
      break;
    case 24:      cPal = saga_14_gp;
      break;
    case 25:      cPal = saga_15_gp;
      break;
    case 26:      cPal = saga_17_gp;
      break;
    
    }
}

/*
 * // Determine flash address of text string
unsigned int currentStringAddress = 0;
void selectFlashString(byte string) {
  currentStringAddress = pgm_read_word(&stringArray[string]);
}

// Fetch font character bitmap from flash
byte charBuffer[5] = {0};
void loadCharBuffer(byte character) {
  byte mappedCharacter = character;
  if (mappedCharacter >= 32 && mappedCharacter <= 95) {
    mappedCharacter -= 32; // subtract font array offset
  } else if (mappedCharacter >= 97 && mappedCharacter <= 122) {
    mappedCharacter -= 64; // subtract font array offset and convert lowercase to uppercase
  } else {
    mappedCharacter = 96; // unknown character block
  }
  
  for (byte i = 0; i < 5; i++) {
    charBuffer[i] = pgm_read_byte(Font[mappedCharacter]+i);
  }
  
}

// Fetch a character value from a text string in flash
char loadStringChar(byte string, byte character) {
  return (char) pgm_read_byte(currentStringAddress + character);
}
 */
