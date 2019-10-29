void iic(String x){
  Wire.beginTransmission(2);
  char c[x.length()+1];
  x.toCharArray(c,x.length()+1);
  Wire.write(c);
  Wire.endTransmission();
}

void iicPulse(char type) {
  Wire.beginTransmission(2);
  Wire.write(type);
  Wire.endTransmission();
}


/* Learn about unions later
void iicSend ( int V1, int V2, int V3) {
  Wire.beginTransmission(2);
  union
    {
    int configs [3];
    byte buf [8];
    } configUnion;
   
  configUnion.configs [0] = V1;
  configUnion.configs [1] = V2;
  configUnion.configs [2] = V3;
 
  Wire.write((byte *) &configUnion, sizeof configUnion);
  Wire.endTransmission();
}
*/
 
void randPal() {
  cPal = random(26); // make no# palettes available
  String CPAL = String(cPal);
  String mOut = "5," + CPAL;
  char outA[mOut.length()+2]; 
  mOut.toCharArray(outA, mOut.length()+1);
  iic(outA);
 
  DPRINT(cPal);
}

void randCfx() {
  cFX = random(20); // make no# patterns in auto mode
  String CFX = String(cFX);
  String mOut = "6," + CFX;
  char outA[mOut.length()+2]; 
  mOut.toCharArray(outA, mOut.length()+1);
  iic(outA);
}

void randCpfx() {
  cpFX = random(2); // make no# patterns in pulse mode
  String CPFX = String(cpFX);
  String mOut = "7," + CPFX;
  char outA[mOut.length()+2]; 
  mOut.toCharArray(outA, mOut.length()+1);
  iic(outA);
}


void countBars() {
  if (clk == 64 | clk == 32) tClk = tClk + 1;
  if (tClk >= 64) tClk = 0;
  DPRINTLN(tClk);
  for (int i = 0; i < 16 ; i++) {
    if (clk == 8 * i) {
      randCfx();
      randCpfx();
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
