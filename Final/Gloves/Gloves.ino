#include <MPU6050_tockn.h>
#include <Wire.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "variables.h"
#include "DataStructure.h"

RF24 radio(9, 10); // CE, CSN
const byte address[6] = "PT001";

MPU6050 mpu6050(Wire);

#define LEDblue 8

uint32_t ihap = 0;

void setup() {
  pinMode(LEDblue, OUTPUT);
  LEDon();
  Serial.begin(115200);
  Serial.println("Sign Language Gloves on ESP32");
  Serial.println("SYSTEM STARTING...\n\n\n");

  pinMode(Sensor_Thumb, INPUT);
  pinMode(Sensor_Index, INPUT);
  pinMode(Sensor_Middle, INPUT);
  pinMode(Sensor_Ring, INPUT);
  pinMode(Sensor_Pinky, INPUT);

  if (!radio.begin()) {
    Serial.println("NRF24L01 Hardware Didn't Respond");
  }
  Serial.println("NRF24L01 Transmitter Mode");
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);
  radio.openWritingPipe(address);
  radio.stopListening();

  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
  LEDoff();
  Serial.println("\n\n\nStarting in 2 seconds");
  delay(2000);

  //  Serial.println("\n\n\nPOSITION...");
  //  delay(3000);
  //  Serial.println("\n\n\nSTART READING....");
  //  delay(2000);
  //  Val_Thumb = analogRead(Sensor_Thumb);
  //  Val_Index = analogRead(Sensor_Index);
  //  Val_Middle = analogRead(Sensor_Middle);
  //  Val_Ring = analogRead(Sensor_Ring);
  //  Val_Pinky = analogRead(Sensor_Pinky);
  //
  //  mpu6050.update();
  //  KamoTalk_GyroX = mpu6050.getAngleX();
  //  KamoTalk_GyroY = mpu6050.getAngleY();
  //  KamoTalk_GyroZ = mpu6050.getAngleZ();
  //  delay(100);
  //  TestSensorValues();
}




void loop() {
  Val_Thumb = analogRead(Sensor_Thumb);
  Val_Index = analogRead(Sensor_Index);
  Val_Middle = analogRead(Sensor_Middle);
  Val_Ring = analogRead(Sensor_Ring);
  Val_Pinky = analogRead(Sensor_Pinky);

  mpu6050.update();
  KamoTalk_GyroX = mpu6050.getAngleX();
  KamoTalk_GyroY = mpu6050.getAngleY();
  KamoTalk_GyroZ = mpu6050.getAngleZ();

  //Correspond();
  //TestSensorValues();
  NRF_SendData();


}

void NRF_SendData() {
  payload.kt_GyroX = KamoTalk_GyroX;
  payload.kt_GyroY = KamoTalk_GyroY;
  payload.kt_GyroZ = KamoTalk_GyroZ;

  payload.adc_Thumb = Val_Thumb;
  payload.adc_Index = Val_Index;
  payload.adc_Middle = Val_Middle;
  payload.adc_Ring = Val_Ring;
  payload.adc_Pinky = Val_Pinky;

  payload.byteThumb = ThumbByte();
  LEDon();
  radio.write(&payload, sizeof(PayloadData));
  LEDoff();
}

void Correspond() {
  //  if ( TestGesture(250, 320, 285, 130, 350, UnitTolerance)) {
  //    Serial.println("Rock and Roll");
  //    delay(2000);
  //  }


  //  if (TestGesture(290,  200,  475,  135, 220, UnitTolerance)) {
  //    Serial.println("Pakyu Bitch");
  //    delay(2000);
  //  }

  if (TestGesture(270,  160,  320,  140, 210, UnitTolerance) && TestGyroGesture(103.61, -8.94, 60.75 , GyroTolerance) && ThumbByte() == 255) {
    Serial.println("A");
    delay(100);
  }

  if (TestGesture(210,  295,  485,  205, 420, UnitTolerance) && TestGyroGesture(103.61, -8.94, 60.75 , GyroTolerance) && ThumbByte() == 255) {
    Serial.println("B");
    delay(100);
  }

  if (TestGesture(244,  200,  343,  135 , 290, UnitTolerance) && TestGyroGesture(103.61, -8.94, 60.75 , GyroTolerance) && ThumbByte() == 255) {
    Serial.println("C");
    delay(100);
  }

}


void LEDon() {
  digitalWrite(LEDblue, 1);
}

void LEDoff() {
  digitalWrite(LEDblue, 0);
}
