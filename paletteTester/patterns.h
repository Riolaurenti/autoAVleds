static int colorIndex;
int paletteIndex;
uint8_t brightness = 255;
CRGBPalette16 usePalette = primaryPalette;
TBlendType currentBlending;

void sinelon() {
  // a colored dot sweeping back and forth, with fading trails
  //First argument for posX is the speed that t moves across x, would be great-
  //linked to a bpm input.
  int myDelay = 1;
  int myFadeOut =10;
  fadeToBlackBy(&(leds(0)), NUM_LEDS, myFadeOut);
  int posX = beatsin16( 200, 0, MATRIX_HEIGHT - 1 ) ;
  int posY = beatsin16( 12, 0, MATRIX_WIDTH - 1 ) ;
  EVERY_N_MILLIS(50){
  colorIndex++;
  }
  if (colorIndex > 765) {
    colorIndex = 0;
  }
  if (colorIndex < 255){
	  usePalette = primaryPalette;
	  paletteIndex = colorIndex;
  }
  if (colorIndex > 255 && colorIndex < 510){
	  usePalette = secondaryPalette;
	  paletteIndex = colorIndex - 255;
  }
  if (colorIndex > 510){
	  usePalette = tertiaryPalette;
	  paletteIndex = colorIndex - 510;
  }
  leds(posY,posX) = ColorFromPalette( usePalette, paletteIndex, brightness, currentBlending);
  FastLED.delay(1);
}
