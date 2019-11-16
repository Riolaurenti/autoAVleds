#include <FastLED.h> // FastLED init
#include <LEDMatrix.h>
#include <LEDText.h>

#define DATA_PIN 5
#define DATA2_PIN 7
#define COLOR_ORDER GRB

#define MATRIX_TILE_WIDTH 8
#define MATRIX_TILE_HEIGHT 8
#define MATRIX_TILE_H 3
#define MATRIX_TILE_V 2
#define MATRIX_SIZE (MATRIX_WIDTH*MATRIX_HEIGHT)
#define MATRIX_PANEL (MATRIX_WIDTH*MATRIX_HEIGHT)

#define MATRIX_WIDTH (MATRIX_TILE_WIDTH*MATRIX_TILE_H)
#define MATRIX_HEIGHT (MATRIX_TILE_HEIGHT*MATRIX_TILE_V)

#define NUM_LEDS (MATRIX_WIDTH*MATRIX_HEIGHT)

cLEDMatrix< -MATRIX_TILE_WIDTH, MATRIX_TILE_HEIGHT, HORIZONTAL_ZIGZAG_MATRIX, MATRIX_TILE_H, MATRIX_TILE_V, HORIZONTAL_ZIGZAG_BLOCKS> leds;

#include "palettes.h"
#include "patterns.h"

void setup() {
  Serial.begin(115200);
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds[0], 0, 192);
  FastLED.addLeds<WS2812B, DATA2_PIN, GRB>(leds[0], 192, 192);
  FastLED.setBrightness(64);
  currentBlending = LINEARBLEND;
  primaryPalette = Red_blueD1;
  secondryPalette =	Red_blueL1;
  tertiaryPalette = Blue_greenD1;
  FastLED.clear();
}

void loop(){
	sinelon();
}
