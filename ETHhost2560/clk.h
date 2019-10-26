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
    ioRule[0]=0;
    ioRule[1]=0;
    ioRule[2]=1;
    ioRule[3]=1;
    ioRule[4]=1;
  }
  if(ioRule!=ioRuleMem)    iicArray(2, ioRule);
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
