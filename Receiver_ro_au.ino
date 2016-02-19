
#include <VirtualWire.h>

const int led_pin = 13;
const int receive_pin = 11;
const int vcc = 10;

#define FALSE 0
#define TRUE 1

boolean output[4] = {false,false,false,false};
float output_pin[] = {7,6,5,4};
void setup()
{
 
   delay(1000);
   Serial.begin(9600); 
   Serial.println("setup");
   
   vw_set_rx_pin(receive_pin);
   vw_setup(2000); // Transmission rate
   // Start the receiver PLL
   vw_rx_start();
   // Set LED pin
   pinMode(led_pin, OUTPUT);
   pinMode(output_pin[0], OUTPUT);
   pinMode(output_pin[1], OUTPUT);
   pinMode(output_pin[2], OUTPUT);
   pinMode(output_pin[3], OUTPUT);
   pinMode(vcc, OUTPUT);
   digitalWrite(output_pin[0], LOW);
   digitalWrite(output_pin[1], LOW);
   digitalWrite(output_pin[2], LOW);
   digitalWrite(output_pin[3], LOW);
   digitalWrite(vcc, HIGH);
}
void loop()
{
   uint8_t buf[VW_MAX_MESSAGE_LEN];
   uint8_t buflen = VW_MAX_MESSAGE_LEN;
   
   if (vw_get_message(buf, &buflen))
   {
   
   digitalWrite(led_pin, HIGH);
   Serial.print("Got: ");
   // Print message
   for (int i = 0; i < buflen; i++)
   {
     Serial.print(char(buf[i]));
     Serial.print(' ');
     
   }
   
   for (int j = 0; j < 4; j++){
       if( buf[j] == 0x31 ){
         output[j] = !output[j];
       }
   }
   for (int k = 0; k < 4; k++){
     if(output[k] == 1 ){
       digitalWrite(output_pin[k], HIGH);}
       else {
         digitalWrite(output_pin[k], LOW);}
   
   Serial.println();
   digitalWrite(led_pin, LOW);
   }
}
delay(1000);
}
