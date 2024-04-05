#include <SPI.h>
#include <Wire.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "DataStructure.h"
#include "variables.h"

//======================================= OLED ==================================================
#include "U8glib.h"
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_DEV_0 | U8G_I2C_OPT_NO_ACK | U8G_I2C_OPT_FAST);  // Fast I2C / TWI
//===============================================================================================

RF24 radio(8, 9); // CE, CSN

const byte address[6] = "PT001";

#define LEDgreen 3
#define LEDred 2

void setup() {
  pinMode(LEDgreen, OUTPUT);
  pinMode(LEDred, OUTPUT);
  digitalWrite(LEDred, 1);
  LEDgreenOFF();
  Serial.begin(9600);
  if (!radio.begin()) {
    Serial.println("NRF24L01 Hardware Didn't Respond");
  }

  Serial.println("NRF24L01 Reciever Mode");
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);
  radio.openReadingPipe(0, address);
  radio.startListening();


  //============================ OLED =============================
  if (u8g.getMode() == U8G_MODE_R3G3B2) {
    u8g.setColorIndex(255);  // white
  } else if (u8g.getMode() == U8G_MODE_GRAY2BIT) {
    u8g.setColorIndex(3);  // max intensity
  } else if (u8g.getMode() == U8G_MODE_BW) {
    u8g.setColorIndex(1);  // pixel on
  } else if (u8g.getMode() == U8G_MODE_HICOLOR) {
    u8g.setHiColorByRGB(255, 255, 255);
  }
  //===============================================================
}

void loop() {
  if (radio.available()) {
    //Serial.println("recieve and decode data");
    radio.read(&payload, sizeof(PayloadData));
    LEDgreenON();
    char text[32] = "";
    radio.read(&text, sizeof(text));

    //Serial.println("decrypt data");
    DecryptData();
    //ShowData();
    //Serial.println("respond to data");
    Correspond();
  } else {
    LEDgreenOFF();
  }







  //============================ OLED =============================
  u8g.firstPage();
  do {
    //DrawData();
    DrawLetter();
  } while (u8g.nextPage());
  //===============================================================


  if (GestureAccepted == true && !SignPrinted && NowSigning != ' ') {
    Serial.print(NowSigning);
    //GestureAccepted = true;
    //GestureCount = 0;
    SignPrinted = true;
  } else if (GestureAccepted == false) {
    SignPrinted = false;
  }
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

  if (TestGesture(280,  160,  280,  150, 330, UnitTolerance) && TestGyroGesture(85.00, -7.00, -177.00 , GyroTolerance) ) {
    NowSigning = 'A';
    signing();
  } else if (TestGesture(210,  295,  485,  205, 420, UnitTolerance) && TestGyroGesture(103.61, -8.94, 60.00 , GyroTolerance) ) {
    NowSigning = 'B';
    signing();
  } else if (TestGesture(220,  180,  350,  175, 320, UnitTolerance) && TestGyroGesture(63.00, 2.00, 71.00 , GyroTolerance) ) {
    NowSigning = 'C';
    signing();
  }  else if (TestGesture(250,  310,  350,  170, 240, UnitTolerance) && TestGyroGesture(70.00, -5.00, 90.00 , GyroTolerance) && ThumbByte == 240 ) {
    NowSigning = 'D';
    signing();
  }  else if (TestGesture(200, 155, 270, 111, 175, UnitTolerance) && TestGyroGesture(67.00, -6.00, 129.00, GyroTolerance) ) {
    NowSigning = 'E';
    signing();
  }   else if (TestGesture(225, 180, 465, 190, 340, UnitTolerance) && TestGyroGesture(66.00, -11.00, 800.00, GyroTolerance) ) {
    NowSigning = 'F';
    signing();
  }  else if (TestGesture(240, 200, 305, 130, 250, UnitTolerance) && TestGyroGesture(90.00, 17.00, -520.00, GyroTolerance) && ThumbByte == 240 ) {
    NowSigning = 'G';
    signing();
  }  else if (TestGesture(200, 305, 480, 145, 170, UnitTolerance) && TestGyroGesture(63.00, 28.00, -485.00, GyroTolerance) && ThumbByte == 240 ) {
    NowSigning = 'H';
    signing();
  }  else if (TestGesture(185, 145, 280, 120, 345, UnitTolerance) && TestGyroGesture(89.00, -6.00, -600.00, GyroTolerance) && ThumbByte == 240 ) {
    NowSigning = 'I';
    signing();
  } else if (TestGesture(195, 150, 305, 125, 370, UnitTolerance) && TestGyroGesture(28.00, 88.00, -900.00, GyroTolerance) && ThumbByte == 240 ) {
    NowSigning = 'J';
    signing();
  }  else if (TestGesture(255,260,395,170,270, UnitTolerance) && TestGyroGesture(72.00, 17.00, -61.00, GyroTolerance) && ThumbByte == 253 ) {
    NowSigning = 'K';
    signing();
  } else {
    NowSigning = ' ';
    SignPrinted = false;
  }

}

void signing() {
  if (NowSigning == Prev_NowSigning) {
    GestureCount++;
    if (GestureCount >= 20) {
      GestureAccepted = true;
    }
  } else {
    GestureCount = 0;
    GestureAccepted = false;
    SignPrinted = false;
  }
  Prev_NowSigning = NowSigning;
}







void ShowData() {
  Serial.println("=============== NRF24L01 DATA Recieved! ===============");
  Serial.println("GYRO");
  Serial.println("Gyro X:" + String(payload.kt_GyroX));
  Serial.println("Gyro Y:" + String(payload.kt_GyroY));
  Serial.println("Gyro Z:" + String(payload.kt_GyroZ));
  Serial.println("\n\nADC");
  Serial.println("Thumb:" + String(payload.adc_Thumb));
  Serial.println("Index:" + String(payload.adc_Index));
  Serial.println("Middle:" + String(payload.adc_Middle));
  Serial.println("Ring:" + String(payload.adc_Ring));
  Serial.println("Pinky:" + String(payload.adc_Pinky));
  Serial.println("=======================================================\n\n\n");
}

void LEDgreenON() {
  digitalWrite(LEDgreen, 0);
}

void LEDgreenOFF() {
  digitalWrite(LEDgreen, 1);
}
