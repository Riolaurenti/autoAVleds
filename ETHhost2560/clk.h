void onBar() {
  for(i=1;i<runT;i++){
    for(int i = 0 ; i < sizeof(ioRule); i++) {
      ioRuleMem[i]=ioRule[i];
    }
    if(tClk==((i*ratio))){ // if the tClk is divisable by the ratio...
      DPRINTLN(" Division 1"); //do something send something whatever
       if(howManyBars==0){
          randPal(); //randomize at this rate
          randCfx();
       }
    }
    if(tClk==((ratio*i)+(ratio/4))){
      DPRINTLN(" !!!  L2 O1");
      if(howManyBars==1){
          randPal();
          randCfx();
       }
    }
    if(tClk==((ratio*i)+((ratio/4)*2))){
      DPRINTLN(" !!!  L3 O1");
      if(howManyBars==2){
          randPal();
          randCfx();
       }
    }
    if(tClk==((ratio*i)+((ratio/4)*3))){
      DPRINTLN(" !!!  L4 O1");
      if(howManyBars==3){
          randPal();
          randCfx();
       }
    }
    if(ioRule!=ioRuleMem)    iicArray(2, ioRule); // if the ioRule has changed, send it via I2C
  }
}

void countBars(){
  if(clk==0) tClk++;
  if(tClk >= 64) tClk=0;
  DPRINT(" CLK = ");
  DPRINT(clk);
  DPRINT(" Bar = ");
  DPRINT(tClk);
  onBar();
}
/*
//old method for safe keeping
void onBar(){
  for(int i = 0 ; i < sizeof(ioRule); i++) {
    ioRuleMem[i]=ioRule[i];
  }
  if(tClk < 15) {
    for(int i = 0 ; i < sizeof(ioRule); i++) { // change to no# MCU's connected
      ioRule[i]=0;
    }
  }
  if(tClk >=15 && tClk < 31) {  
    for(int i = 0 ; i < sizeof(ioRule); i++) { // change to no# MCU's connected
      ioRule[i]=1;
    }
  }
  if(tClk >=31 && tClk < 47) {
    ioRule[0]=0;
    ioRule[1]=0;
    ioRule[2]=1;
    ioRule[3]=1;
    ioRule[4]=1;
  }
  if(tClk >=47 && tClk < 63) {
    ioRule[0]=1;
    ioRule[1]=1;
    ioRule[2]=0;
    ioRule[3]=0;
    ioRule[4]=0;
  }
  if(ioRule!=ioRuleMem)    iicArray(2, ioRule);
}
*/
