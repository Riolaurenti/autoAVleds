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

#define STROBE_BEATS_PER_MINUTE 97.5
uint8_t gHue = 0;
int myDelay = 30;
int colorIndex = 0;
int patternNumber = 2;
uint8_t brightness = 255;
TBlendType currentBlending;

bool cycleFlag[] = {};

int sStatic = 0; //setup placeholder 
int cur_Step = 0;
int iicTable[68] = {};
volatile int clkVal;
bool cFlag = 0; //clock Flag
bool pFlag[8] = {0,0,0,0, 0,0,0,0}; //pulse Flag
int itX = 0;
int Mode = 0; //Menu pulse/auto



int arrA[64] = {};
int arrB[64] = {};
int arrC[64] = {};
int arrD[64] = {};
