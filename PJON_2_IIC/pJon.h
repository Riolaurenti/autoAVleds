
 /*
  * Parser - Receives PJON and converts to I2C
  */
void parser() { 
  int comma = string.indexOf(",");
  while(string.length() >= 1){
    //Bypass all below and just forward string to iic

    
    String type = string.substring(0, comma); // get value at pos #1 - Message Type
    DPRINT("type = "); DPRINTLN(type);
    String value = string.substring(comma+1,3); // get value at pos #2 - Value of Message
    DPRINT("Value = ");    DPRINTLN(value); 
    DFLUSH();
    //iic(); 
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
  }
  DFLUSH(); // wait til serial is printed
};

void receiver_handler(uint8_t *payload, uint16_t length, const PJON_Packet_Info &packet_info) {
  const  char * arr = payload; // Not a pointer now.... !
  string.concat(arr); // addd it to our string
  iic(string);
  /*
 // parser(); 
  DPRINT("Received: ");
  for(uint16_t i = 0; i < length; i++) {
    DPRINT((char)payload[i]);
    DPRINT(" ");
  }
  DPRINTLN();
  */
  string = "";
 };
