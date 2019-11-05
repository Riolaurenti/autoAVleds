#define LED_PIN        2
#define LED_PIN2       3
#define LED_PIN3       4
#define LED_PIN4       5
#define NUM_STRIPS     4 
#define NUM_PER_STRIP 42 

#define COLOR_ORDER    GRB
#define CHIPSET        WS2812B
#define MAXBRIGHT 64
#define STARTBRIGHT 60
#define cTime 15000
#define hTime 30
uint8_t brightness = 64;
#define STROBE_BEATS_PER_MINUTE 97.5

int ourAddr = ADDR-2; // Our IIC address holder for logic work.

CRGBPalette16 cPal(RainbowColors_p); // global palette storage
//CRGB cPalGo[4] = {CRGB::White, CRGB::Blue, CRGB::Green,CRGB::Red}; // global palette storage
int Zone = 0; //Change to cur MCU#
byte zVals[5] = {}; // Zone Value (get bits) used for pattern store
byte subZone[4] = {}; // Change Strip
int iicTable[8] = {}; // holder for iic array message (reduce to 8)
byte stripMode = 0;
byte curStrip = 0;
int nLED;
int sLED;
int eLED;
int pArr[NUM_STRIPS] = {};
int cPalVal = 0;

int patternStore[NUM_STRIPS+1];//this array holds the pattern number for each strip.

volatile byte cFX = 0; // index to the currently running effect
volatile byte cpFX = 0; // index to the currently running effect
byte cBright = STARTBRIGHT; // 0-255 will be scaled to 0-MAXBRIGHTNESS

int cur_Step = 0;
volatile int clkVal;
bool cFlag = 0; //clock Flag
bool pFlag[8] = {0,0,0,0, 0,0,0,0}; //pulse Flag
int Mode = 0; //Menu pulse/auto
int Solo = 0; // host auto / solo auto
int ioRule[] = {0,0,0,0,0}; // Rule Holder for Primary/Secondary MCU

String received; 
boolean fxInit = false; // indicates if a pattern has been recently switched
uint16_t fxDelay = 0; // time between automatic effect changes

unsigned long fxMil = 0; // store the time of last effect function run
unsigned long cycMil = 0; // store the time of last effect change
unsigned long cMil; // store current loop's millis value
unsigned long hMil; // store time of last hue change
unsigned long cFXmil; // store current loop's millis value
unsigned long FXmil; // store time of last hue change

uint8_t gHue = 0;
int myDelay = 30;
int colorIndex = 0;
byte patternNumber = 0; // holder for pattern no individual
byte patternNoArray = 0; // holder for pattern in array
TBlendType currentBlending;

typedef void (*functionList)(); // definition for list of effect function pointers
extern const byte numFX;

int itX = 0; // used for iterator, debug only
int sStatic = 0; //setup placeholder debug
