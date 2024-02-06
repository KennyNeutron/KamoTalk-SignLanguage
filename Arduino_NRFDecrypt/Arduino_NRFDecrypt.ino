#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>



RF24 radio(9, 10);
const uint64_t address = 0xF0F0F0F0E1LL;



void setup()
{
  Serial.begin(115200);
  radio.begin();



  Serial.println("System Started");

  radio.openReadingPipe(0, address);   //Setting the address at which we will receive the data
  radio.setPALevel(RF24_PA_MAX);       //You can set this as minimum or maximum depending on the distance between the transmitter and receiver.
  radio.startListening();              //This sets the module as receiver
}



void loop() {
  if (radio.available()) {
    char text[32] = "";
    radio.read(&text, sizeof(text));
    Serial.write('<');
    Serial.write(text);
    Serial.write('>');
  }
}
