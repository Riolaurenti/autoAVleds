#define PJON_INCLUDE_SWBB
#include <PJON.h>  
uint8_t bus_id[] = {0, 0, 1, 53}; // Ancs unique ID
PJON<SoftwareBitBang> bus(bus_id,100); // Master = 100
int packet; // Holder for our packet
bool acquired = false; // did we get an address? 
bool debugMode = false; // Are we debugging
uint32_t t_millis; // tick tock

unsigned long DELAY_TIME = 15000; // 1.5 sec
unsigned long delayStart = 0; // the time the delay started
bool delayRunning = false; // true if still waiting for delay to finish

// Reads an incoming control message - not used much yet..
void parser(){
  while(string.length() >= 1){ // While there message left to read. 
    String subs = string.substring(0);
    if (subs.startsWith("Rst"))resetFunc(); // Reboot yourself. messge is destryed at this point
    else {
    DPRINTLN(string);
    DPRINTLN(string.length());
    }// prints the length of the command each iteration
  }
  DPRINT("STR = "); // prints after length < 1
  DPRINTLN(string);
  string = ""; // empty it
};

void error_handler(uint8_t code, uint16_t data, void *custom_pointer) {
  if(code == PJON_CONNECTION_LOST) {
      resetFunc(); // Reset
  }
};

// PJON RECEIVER CODE
void receiver_handler(uint8_t *payload, uint16_t length, const PJON_Packet_Info &packet_info) {
   const char * arr = payload; // Not a pointer now.... !
  string.concat(arr); // addd it to our string
  if( string.startsWith("ack")){ // master got our registation message!
    ack = true; // nice
    string = ""; // thats all it says!
    DPRINT("Heard from server"); 
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

/*
// PJON Reciver 
void receiver_function(uint8_t *payload, uint16_t length, const PJON_Packet_Info &packet_info) {
 
  int id = int(packet_info.sender_id);
  String toParse = payload; // conver to String
  parseMsg(id, toParse); // Shunt off to the PArser
  //DPRINTLN("MESSAGE!!");
} // Thats it!
*/

void tellMasterAboutSelf(){ 
  const char pkt[regString.length()+1]; // Create array
  regString.toCharArray(pkt,regString.length()); // Convert string to Char[]
  bus.send(254,pkt,regString.length()+1); // Send the packet to master. 
};
