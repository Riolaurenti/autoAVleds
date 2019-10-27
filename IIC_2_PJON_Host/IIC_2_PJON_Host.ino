#include <Wire.h>
#define I2CADDR  8

#include "global.h"
#include "macros.h"
#include "pJon.h"

/*
 * I2C > Pjon converter code
 * Takes all I2c arguements, builds a string then sends over network
 * Here determines route to Network from the Master EthHost2560
 * 
 * ToDo - Ignore Master
 */

void receiveEvent(int howMany) {
  while (Wire.available()) { // loop through all but the last
    char c = Wire.read(); // receive byte as a characte   // print the character
    i2cStr.concat(c);
  }
  DPRINTLN();
  DPRINT("ASSEMBLED MESSAGE FROM I2C : ");
  DPRINTLN(i2cStr);
  sendPjon(i2cStr);
  i2cStr = "";
}

void sendPjon(String str){ 
  DPRINT("SENDING TO MASTER");
  const char pkt[str.length()+1]; // Create array
  str.toCharArray(pkt,str.length()+1); // Convert string to Char[]
  bus.send(PJON_BROADCAST,pkt,str.length()+1); // Send the packet to everyone 
  DPRINTLN(pkt);
};

void setup() {
  DBEGIN(115200);
  Wire.begin(8);              // join i2c bus with address #8
  Wire.onReceive(receiveEvent);
  bus.set_error(error_handler); // link PJON to error handler
  bus.set_receiver(receiver_handler); // link PJON to receiver
  bus.strategy.set_pin(12); // Set PJON pin
  bus.begin(); //
  delay(160); // possibly not needed if master is online
}

void loop() {
  bus.update(); // update the PJON
  bus.receive(5000); // receive for a while
}
