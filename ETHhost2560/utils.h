void randPal() {
  cPal = random(26); // make no# palettes available
  iicInt(2, 5 , cPal);
}

void randCfx() {
  cFX = random(13); // make no# patterns in auto mode
  iicInt(2, 6 , cFX);
  cpFX = random(3); // make no# patterns in pulse mode (temp holder, to be merged)
  iicInt(2, 7 , cpFX);
}

void randCpfx() {
  cpFX = random(3); // make no# patterns in pulse mode
  iicInt(2, 7 , cpFX);
}
