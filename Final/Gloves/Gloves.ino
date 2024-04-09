#include <Wire.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "variables.h"
#include "DataStructure.h"

RF24 radio(9, 10); // CE, CSN
const byte address[6] = "PT001";



#define LEDblue 8

uint32_t ihap = 0;

const int MPU_addr = 0x68;
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;

int minVal = 265;
int maxVal = 402;

float x;
float y;
float z;


void setup() {
  pinMode(LEDblue, OUTPUT);
  LEDon();
  //Serial.begin(115200);
  //Serial.println("Sign Language Gloves on ESP32");
  //Serial.println("SYSTEM STARTING...\n\n\n");

  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);


  pinMode(Sensor_Thumb, INPUT);
  pinMode(Sensor_Index, INPUT);
  pinMode(Sensor_Middle, INPUT);
  pinMode(Sensor_Ring, INPUT);
  pinMode(Sensor_Pinky, INPUT);

  if (!radio.begin()) {
    //Serial.println("NRF24L01 Hardware Didn't Respond");
  }
  //Serial.println("NRF24L01 Transmitter Mode");
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);
  radio.openWritingPipe(address);
  radio.stopListening();

  //Serial.println("Done!\n");

  LEDoff();
  //Serial.println("\n\n\nStarting in 2 seconds");
  delay(2000);


}




void loop() {
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr, 14, true);
  AcX = Wire.read() << 8 | Wire.read();
  AcY = Wire.read() << 8 | Wire.read();
  AcZ = Wire.read() << 8 | Wire.read();
  int xAng = map(AcX, minVal, maxVal, -90, 90);
  int yAng = map(AcY, minVal, maxVal, -90, 90);
  int zAng = map(AcZ, minVal, maxVal, -90, 90);

  x = RAD_TO_DEG * (atan2(-yAng, -zAng) + PI);
  y = RAD_TO_DEG * (atan2(-xAng, -zAng) + PI);
  z = RAD_TO_DEG * (atan2(-yAng, -xAng) + PI);


  Val_Thumb = analogRead(Sensor_Thumb);
  Val_Index = analogRead(Sensor_Index);
  Val_Middle = analogRead(Sensor_Middle);
  Val_Ring = analogRead(Sensor_Ring);
  Val_Pinky = analogRead(Sensor_Pinky);



  //Correspond();
  //TestSensorValues();
  NRF_SendData();


}

void NRF_SendData() {
  payload.kt_GyroX = x;
  payload.kt_GyroY = y;
  payload.kt_GyroZ = z;

  payload.adc_Thumb = Val_Thumb;
  payload.adc_Index = Val_Index;
  payload.adc_Middle = Val_Middle;
  payload.adc_Ring = Val_Ring;
  payload.adc_Pinky = Val_Pinky;

  payload.byteThumb = ThumbByte();
  payload.byteIndex = IndexByte();
  payload.byteMiddle = MiddleByte();
  payload.byteRing = RingByte();
  payload.bytePinky = PinkyByte();

  LEDon();
  radio.write(&payload, sizeof(PayloadData));
  LEDoff();
}

//void Correspond() {
//
//  if (TestGesture(270,  160,  320,  140, 210, UnitTolerance) && TestGyroGesture(103.61, -8.94, 60.75 , GyroTolerance) && ThumbByte() == 255) {
//    Serial.println("A");
//    delay(100);
//  }
//
//  if (TestGesture(210,  295,  485,  205, 420, UnitTolerance) && TestGyroGesture(103.61, -8.94, 60.75 , GyroTolerance) && ThumbByte() == 255) {
//    Serial.println("B");
//    delay(100);
//  }
//
//  if (TestGesture(244,  200,  343,  135 , 290, UnitTolerance) && TestGyroGesture(103.61, -8.94, 60.75 , GyroTolerance) && ThumbByte() == 255) {
//    Serial.println("C");
//    delay(100);
//  }
//
//}


void LEDon() {
  digitalWrite(LEDblue, 1);
}

void LEDoff() {
  digitalWrite(LEDblue, 0);
}
