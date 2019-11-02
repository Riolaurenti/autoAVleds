static int colorIndex;
uint8_t brightness = 255;
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
  colorIndex++;
  if (colorIndex > 254) {
    colorIndex = 0;
  }
  leds(posY,posX) = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
  FastLED.delay(1);
}
