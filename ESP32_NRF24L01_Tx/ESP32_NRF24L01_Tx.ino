#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>



RF24 radio(4, 5);
const uint64_t address = 0xF0F0F0F0E1LL;

uint16_t counter=0;


void setup()
{
  Serial.begin(115200);
  radio.begin();



  Serial.println("System Started");

  radio.openWritingPipe(address); //Setting the address where we will send the data
  radio.setPALevel(RF24_PA_MAX);  //You can set it as minimum or maximum depending on the distance between the transmitter and receiver.
  radio.stopListening();          //This sets the module as transmitter
}



void loop() {
  String msg = "Hello World ";
  msg=msg+String(counter);
  radio.write(&msg, sizeof(msg));
  Serial.println(String(msg));
  delay(5000);
  counter++;
}
