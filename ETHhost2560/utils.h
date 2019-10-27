
void iicPulse(int dest, int type) {
  Wire.beginTransmission(dest);
  Wire.write(type);
  Wire.endTransmission();
}
void iicInt(int dest, int type, int val) {
  Wire.beginTransmission(dest);
  Wire.write(type);
  Wire.write(val);
  Wire.endTransmission();
}
void iicArray(int dest, int data[8]) {
  Wire.beginTransmission(dest);
  Wire.write(4);
  for (int i = 0 ; i < 8; i++) {
    Wire.write(data[i]);
  }
  Wire.endTransmission();
}
void iicClk(int dest, int curStep) { // unnecessary, use iicInt
  Wire.beginTransmission(dest);
  Wire.write(3);
  Wire.write(curStep);
  Wire.endTransmission();
}

void randPal() {
  cPal = random(26); // make no# palettes available
  DPRINT(cPal);
  iicInt(2, 5 , cPal);
}

void randCfx() {
  cFX = random(20); // make no# patterns in auto mode
  iicInt(2, 6 , cFX);
  cpFX = random(3); // make no# patterns in pulse mode (temp holder, to be merged)
  iicInt(2, 7 , cpFX);
}

void randCpfx() {
  cpFX = random(3); // make no# patterns in pulse mode
  iicInt(2, 7 , cpFX);
}


void countBars() {
  if (clk == 64 | clk == 32) tClk = tClk + 1;
  if (tClk >= 64) tClk = 0;
  DPRINTLN(tClk);
  for (int i = 0; i < 16 ; i++) {
    if (clk == 8 * i) {
      randCfx();
      DPRINT("  cFX = ");
      DPRINTLN(cFX);
    }
  }
  for (int i = 0; i < 16 ; i++) {
    if (clk == 4 * i) {
      randPal();
      DPRINT("  cPal = ");
      DPRINTLN(cPal);
    }
  }
}
