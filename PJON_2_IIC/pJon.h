
 /*
  * Parser - Receives PJON and converts to I2C
  */
void parser() { 
  while(string.length() >= 1){
    String type = string.substring(0); // get value at pos #1 - Message Type
    int msg = type.toInt(); 
    String value = string.substring(1); // get value at pos #2 - Value of Message
    int val = value.toInt(); // change to Int
    DPRINT(msg);
    DPRINT(val); 
    DFLUSH();
    for(int i=0;i<4;i++){ // add how to address MCU's here (Flags)
        Wire.beginTransmission(i); // choose destination
        Wire.write(msg); // add message type
        Wire.write(val); // add value
        Wire.endTransmission(); // send on next iteration
      }
    }
  string = ""; // empty the string!
};

// PJON error handling 
void error_handler(uint8_t code, uint16_t data, void *custom_pointer) {
  if(code == PJON_CONNECTION_LOST) { // Master is gone !!
    DPRINT("Connection lost with device ");
    DPRINTLN((uint8_t)bus.packets[data].content[0], DEC);
    delay(1000); // wait a second
    resetFunc(); // Reset
  }
  if(code == PJON_ID_ACQUISITION_FAIL) { // Didnt get an addres... !
    if(data == PJON_ID_ACQUIRE) {
      DPRINTLN("PJONSlave error: multi-master addressing failed.");
      // Didnt get id in Multi-Master environment
      delay(1000);
      resetFunc(); // bye!
    }
    if(data == PJON_ID_CONFIRM) // failed to confirm id with master... This shouldnt happen
      DPRINTLN("PJONSlave error: master-slave id confirmation failed.");
    if(data == PJON_ID_NEGATE)
      // We wont encounter this as we dont intend to give up out ID
      DPRINTLN("PJONSlave error: master-slave id release failed.");
    if(data == PJON_ID_REQUEST)
      // We couldnt find a Master on the network.... 
      DPRINTLN("PJONSlave error: master-slave id request failed.");
      delay(40); // wait 400ms
      if (millis() > 15000){ // if 15s has passed
        DPRINTLN("Resetting due to no ID");
        delay(300); // we reset
        resetFunc();
        } // if not
      bus.acquire_id_master_slave(); // try and get an id again
      acquired = false; // make sure we resend our registration when we reconnect
      delay(160); // makes the delay about 500ms between retrys
     
 }
  DFLUSH(); // wait til serial is printed
};

void receiver_handler(uint8_t *payload, uint16_t length, const PJON_Packet_Info &packet_info) {
  const  char * arr = payload; // Not a pointer now.... !
  string.concat(arr); // addd it to our string
  if( string.startsWith("ack")){ // master got our registation message!
    ack = true; // nice
    string = ""; // thats all it says!
    DPRINT("Heard from server : "); 
  }
  else parser(); // whats it say then ?? 
  // prints it to the console letter by letter
  DPRINT("Received: ");
  for(uint16_t i = 0; i < length; i++) {
    DPRINT((char)payload[i]);
    DPRINT(" ");
  }
  DPRINTLN();
  DFLUSH();
};
void tellMasterAboutSelf(){ 
  const char pkt[regString.length()+1]; // Create array
  regString.toCharArray(pkt,regString.length()+1); // Convert string to Char[]
  bus.send(254,pkt,regString.length()+1); // Send the packet to master. 
};
