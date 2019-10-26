#include <Wire.h>
#include "global.h"
#include "macros.h"
#include "pJon.h"

void setup() {
  DBEGIN(115200);
    bus.set_error(error_handler); // link PJON to error handler
    bus.set_receiver(receiver_handler); // link PJON to receiver
    bus.strategy.set_pin(12); // Set PJON pin
    bus.begin(); // 
    Wire.begin();
}

void loop() {
   if (delayRunning && ((millis() - delayStart) >= DELAY_TIME)) {
      if(bus.device_id() == PJON_NOT_ASSIGNED){
       resetFunc(); // reset
    }
    if(!acquired | !ack){
      bus.send(254,"Chk,",5); // send to master quick check
      acquired = true;
      ack = true;
    }
    delayStart += DELAY_TIME; // No id has been assigned and 15s have elapsed
  }
  if((bus.device_id() != PJON_NOT_ASSIGNED) && !acquired) { // we have an id, but havent regisrtered
    DPRINT("Acquired device id: ");
    DPRINTLN(bus.device_id()); 
    DFLUSH();
    delay(100);
    acquired = true; // track that
    //tellMasterAboutSelf(); // and register
  }
  bus.update(); // update the PJON
  bus.receive(5000); // receive for a while
}
