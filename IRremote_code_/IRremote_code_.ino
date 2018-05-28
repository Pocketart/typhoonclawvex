#include <boarddefs.h>
#include <ir_Lego_PF_BitStreamEncoder.h>
#include <IRremote.h>
#include <IRremoteInt.h>


IRsend mySender;
void sendNEC(unsigned long data, int nbits);




const int RECV_PIN = 2;
const int buttonPinON = 4;
int buttonStateOn = 0;
IRrecv irrecv(RECV_PIN);
decode_results results;
IRsend irsend;
void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();
  irrecv.blink13(true);

}

void loop() {
  buttonStateOn = digitalRead(buttonPinON);
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    delay(200);
            switch (results.decode_type){
                case NEC: Serial.println("NEC"); break ;
                case SONY: Serial.println("SONY"); break ;
                case RC5: Serial.println("RC5"); break ;
                case RC6: Serial.println("RC6"); break ;
                case DISH: Serial.println("DISH"); break ;
                case SHARP: Serial.println("SHARP"); break ;
                case JVC: Serial.println("JVC"); break ;
                case SANYO: Serial.println("SANYO"); break ;
                case MITSUBISHI: Serial.println("MITSUBISHI"); break ;
                case SAMSUNG: Serial.println("SAMSUNG"); break ;
                case LG: Serial.println("LG"); break ;
                case WHYNTER: Serial.println("WHYNTER"); break ;
                case AIWA_RC_T501: Serial.println("AIWA_RC_T501"); break ;
                case PANASONIC: Serial.println("PANASONIC"); break ;
                case DENON: Serial.println("DENON"); break ;
              default:
                case UNKNOWN: Serial.println("UNKNOWN"); break ;
              }
              

  } 

    if (buttonStateOn == HIGH)
    {
      Serial.println("ON");
      Serial.println(results.value, HEX);

      irsend.sendNEC(0x1FE40BF, 32);
 //     irsend.sendRaw(rawCodes, codeLen, 38);

    }
    irrecv.resume();
    delay(100);
}
  
