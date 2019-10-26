#include <Ethernet.h>
#include <EthernetUdp.h>
#include <SPI.h>    
#include <OSCBundle.h>
#include <OSCBoards.h>
#include <Wire.h>

#include"global.h"
#include "macros.h"
#include"cOSC.h"

EthernetUDP Udp;

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; 
IPAddress ip(192, 168, 0, 150);
const unsigned int inPort = 8888;

void setup() { 
  DBEGIN(115200);
  DPRINT("Setup");
  Wire.begin();
  //Wire.onReceive(eHandler);
  Ethernet.begin(mac,ip);
  Udp.begin(inPort);
  DPRINTLN(Ethernet.localIP());
}

void loop() {
  routeOSC();
  //printMon();
}


void routeOSC() {
  OSCBundle bundleIN;
  int size;
   if((size = Udp.parsePacket())>0) {
     while(size--) bundleIN.fill(Udp.read());
     if(!bundleIN.hasError()) {
      bundleIN.route("/m", MODE);
      bundleIN.route("/CLK", CLK);
      bundleIN.route("/p", onPulse);
//      bundleIN.route("/q", onPulse1);
      bundleIN.route("/v", VOL);

      bundleIN.route("/aA", ARRA);
      bundleIN.route("/aB", ARRB);
      bundleIN.route("/aC", ARRC);
      bundleIN.route("/aD", ARRD);
      //bundleIN.route("/aE", ARRA);
      //bundleIN.route("/aF", ARRB);
      //bundleIN.route("/aG", ARRC);
      //bundleIN.route("/aH", ARRD);
     }
   }
}



 /*
void eHandler(int aa) {
  while (1 < Wire.available()) { // loop through all but the last
    char c = Wire.read(); // receive byte as a character
    DPRINT(c);         // print the character
  }
  int x = Wire.read();    // receive byte as an integer
  DPRINTLN(x);         // print the integer
}
*/
