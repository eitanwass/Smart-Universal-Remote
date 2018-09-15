/* Universal Smart Remote
 * 
 * USR built with Arduino 1.8.5.
 * 
 * Ethan Wass
 */

#include <IRremote.h>


const int RECV_PIN = 4;
const int BTN_PIN = 5;

IRrecv irrecv(RECV_PIN);
IRsend irsend;
decode_results results;

bool BTN_pressed = false;


void setup()
{
  Serial.begin(9600);
  
  pinMode(BTN_PIN, INPUT);
  
  irrecv.enableIRIn();    //Enable recieving signals.
}

void loop()
{
  if (irrecv.decode(&results))
  {
      //If recieved a signal decode it
      
      Serial.println(results.value, HEX);
      irrecv.resume();    //Resume recieving signals.
  }

  if(digitalRead(BTN_PIN))
  {
    //If button pressed
    
    if(!BTN_pressed)
      {
        irsend.sendNEC(results.value, results.bits);
        
        Serial.print("Sent: ");
        Serial.println(results.value, HEX);
        
        BTN_pressed = true;
      }
    irrecv.enableIRIn();    //re-enable recieveing signals
  }
  else
    BTN_pressed = false;
}

