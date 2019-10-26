void iicPulse(int dest, int type) {
  Wire.beginTransmission(dest);
  Wire.write(type);
  Wire.endTransmission();
}
void iicArray(int dest, int data[8]) {
  Wire.beginTransmission(dest);
  Wire.write(4);
  for(int i = 0 ; i < 8; i++){
  Wire.write(data[i]);
  }
  Wire.endTransmission();
}
void iicClk(int dest, int curStep) {
  Wire.beginTransmission(dest);
  Wire.write(3);
  Wire.write(curStep);
  Wire.endTransmission();
}
void printMon() {
  /*
  DPRINT("CLK = : ");
  DPRINT("\t");
  DPRINT(clk);
  */
 /*
  DPRINT("   Volume = : " );
  DPRINT(vol);
  DPRINTLN();
  */
 
  for (int i = 0; i<64; i++){ 
    DPRINT(arrA[i]);
    //DPRINT( "\t" ); 
  }
  DPRINTLN();
 /*
  for (int j = 0; j<64; j++){ 
    DPRINT(arrB[j]);
    //DPRINT( "\t" ); 
  }
  DPRINTLN();
  for (int k = 0; k<64; k++){ 
    DPRINT(arrC[k]);
    //DPRINT( "\t" ); 
  }
  DPRINTLN();
  for (int l = 0; l<64; l++){ 
    DPRINT(arrD[l]);
    //DPRINT( "\t" ); 
  }
  DPRINTLN();
  */
  
}


void CLK(OSCMessage &msg, int addrOffset ){ // get float from clock #1 - Receive int/pulse
  int a = msg.getFloat(0);
  clk = a;
  //printMon();
  iicClk(2,clk);
}

void VOL(OSCMessage &msg, int addrOffset ){ // get float from clock #1 - Receive int/pulse
  int c = msg.getFloat(0);
  vol = c;
}
void MODE(OSCMessage &msg, int addrOffset ){ // get float from clock #1 - Receive int/pulse
  int d = msg.getFloat(0);
  mode = d;
  iicPulse(2,d);
  DPRINT("Sent iic with value : ");
  DPRINTLN(d);
}

void onPulse(OSCMessage &msg, int addrOffset ){ // get float from clock #1 - Receive int/pulse
  //
   int aA = msg.getFloat(0);
   if (aA==1){ iicPulse(2,10); } 
   int aB = msg.getFloat(1);
   if(aB==1){ iicPulse(2,11); }
   int aC = msg.getFloat(2);
   if(aC==1){  iicPulse(2,12);}
   int aD = msg.getFloat(3);
   if(aD==1){ iicPulse(2,13); }
   int aE = msg.getFloat(4);
   if (aE==1){ iicPulse(2,14);}
   int aF = msg.getFloat(5);
   if(aF==1){ iicPulse(2,15); }
   int aG = msg.getFloat(6);
   if(aG==1){ iicPulse(2,16); }
   int aH = msg.getFloat(7);
   if(aH==1){ iicPulse(2,17);   }
}


void ARRA(OSCMessage &msg, int addrOffset ){
  for(int i=0;i<64;i++) {
    if (msg.isFloat(i)) {
      int arA = msg.getFloat(i);
      arrA[i] = arA;
    }
   iicArray(2,arrA);
   printMon();
  }
}
void ARRB(OSCMessage &msg, int addrOffset ){
  for(int i=0;i<64;i++) {
    if (msg.isFloat(i)) {
      int arB = msg.getFloat(i);
      arrB[i] = arB;
    }
  }
}
void ARRC(OSCMessage &msg, int addrOffset  ){
  for(int k=0;k<64;k++) {
    if (msg.isFloat(k)) {
      int arC = msg.getFloat(k);
      arrC[k] = arC;
    }
  }
}
void ARRD(OSCMessage &msg, int addrOffset ){
  for(int i=0;i<64;i++) {
    if (msg.isFloat(i)) {
      int arD = msg.getFloat(i);
      arrD[i] = arD;
    }
  }
}
