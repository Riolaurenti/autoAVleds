#define ADDR           2
#define COLOR_ORDER    GRB
#define CHIPSET        WS2812B
#define MAXBRIGHT 95
#define STARTBRIGHT 120
#define cTime 15000
#define hTime 30

#define MAX_DIMENSION ((kMatrixWidth>kMatrixHeight) ? kMatrixWidth : kMatrixHeight) // Noise 
static uint16_t xX;
static uint16_t yY;
static uint16_t zZ;
uint16_t speed = 20;
uint16_t scale = 30;
uint8_t       colorLoop = 1; // Maybe unnecessary...
uint8_t noise[MAX_DIMENSION][MAX_DIMENSION];

#define COOLING  55 // fire (20-100)
#define SPARKING 120 //(50-200)
bool gReverseDirection = false;

bool cycleFlag[] = {};
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
byte cpFX = 0; // index to the currently running effect
byte cBright = STARTBRIGHT; // 0-255 will be scaled to 0-MAXBRIGHTNESS

CRGBPalette16 cPal(RainbowColors_p); // global palette storage

typedef void (*functionList)(); // definition for list of effect function pointers
extern const byte numFX;

#define STROBE_BEATS_PER_MINUTE 97.5
uint8_t gHue = 0;
int myDelay = 30;
int colorIndex = 0;
int patternNumber = 2;
uint8_t brightness = 255;
TBlendType currentBlending;


int sStatic = 0; //setup placeholder 
int cur_Step = 0;
int iicTable[68] = {};
volatile int clkVal;
bool cFlag = 0; //clock Flag
bool pFlag[8] = {0,0,0,0, 0,0,0,0}; //pulse Flag
int itX = 0;
int Mode = 0; //Menu pulse/auto
int Solo = 0; // host auto / solo auto
int ioRule[] = {0,0,0,0,0}; // Rule Holder for Primary/Secondary MCU
int iAm = 0; //Change to cur MCU#
int cPalVal = 0;


int arrA[64] = {};
int arrB[64] = {};
int arrC[64] = {};
int arrD[64] = {};
