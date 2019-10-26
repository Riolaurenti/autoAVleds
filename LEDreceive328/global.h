#define ADDR           2
#define COLOR_ORDER    GRB
#define CHIPSET        WS2812B
#define MAXBRIGHT 95
#define STARTBRIGHT 120
#define cTime 15000
#define hTime 30

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
int ioRule[] = {0,0,0,0,0}; // Rule Holder for Primary/Secondary MCU
int iAm = 0; //Change to cur MCU#


int arrA[64] = {};
int arrB[64] = {};
int arrC[64] = {};
int arrD[64] = {};
