#include <VirtualWire.h>


const int led_pin = 13;
const int transmit_pin = 12;
const int input1_pin = 7;
const int input2_pin = 6;
const int input3_pin = 5;
const int input4_pin = 4;
int input1_value;
int input2_value;
int input3_value;
int input4_value;
const int vcc = A0;
void setup()
{
   // Init
   vw_set_tx_pin(transmit_pin);
   vw_setup(2000); 
   Serial.begin(9600); 
   Serial.println("setup");
   pinMode(led_pin, OUTPUT);
   pinMode(input1_pin,INPUT);
   pinMode(input2_pin,INPUT);
   pinMode(input3_pin,INPUT);
   pinMode(input4_pin,INPUT);
   pinMode(vcc,OUTPUT);
   digitalWrite(vcc, HIGH);
   
}
void loop()
{
   
   input1_value = digitalRead(input1_pin);
   input2_value = digitalRead(input2_pin);
   input3_value = digitalRead(input3_pin);
   input4_value = digitalRead(input4_pin);
   
 char msg[4] = {'0','0','0','0'};
   if (input1_value == 0){
      msg[0] = '1';
   }
   if (input2_value == 0){
      msg[1] = '1';
   }
   if (input3_value == 0){
      msg[2] = '1';
   }
   if (input4_value == 0){
      msg[3] = '1';
   }
   for (int i = 0; i < 4; i++)
   {
     Serial.print(char(msg[i]));
     Serial.print(' ');
     
   }
   Serial.println(' ');
   Serial.println(digitalRead(input1_pin));
   digitalWrite(led_pin, HIGH); 
   vw_send((uint8_t *)msg, 4);
   vw_wait_tx(); // Wait until the whole message is gone
   digitalWrite(led_pin, LOW);
   delay(1000);
}
