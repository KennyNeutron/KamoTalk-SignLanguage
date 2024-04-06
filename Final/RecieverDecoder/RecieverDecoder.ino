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

RF24 radio(9, 10); // CE, CSN

const byte address[6] = "PT001";

#define LEDgreen 3
#define LEDred 2

uint32_t last_millis = 0;

void setup() {
  pinMode(LEDgreen, OUTPUT);
  pinMode(LEDred, OUTPUT);
  digitalWrite(LEDred, 0);
  LEDgreenOFF();
  Serial.begin(9600);
  if (!radio.begin()) {
    Serial.println("NRF24L01 Hardware Didn't Respond");
  }

  //Serial.println("NRF24L01 Reciever Mode");
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
  //  String str_sample="Hello";
  //  Serial.write('<');
  //  Serial.print(str_sample);
  //  Serial.write('>');
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
    DrawData();
    //DrawLetter();
  } while (u8g.nextPage());
  //===============================================================


  //Serial.print("\nSPEAK:");
  //  if (!HasSpoken && GestureAccepted == true && !SignPrinted && NowSigning != '@') {
  //    HasSpoken = true;
  //    Serial.write('<');
  //    Serial.print(WordToSay);
  //    Serial.write('>');
  //    delay(3000);
  //  }



  Serial.print(NowSigning);



  if (GestureAccepted == true && !SignPrinted && NowSigning != ' ' && NowSigning != '@') {
    Serial.print(NowSigning);
    WordToSay = WordToSay + NowSigning;
    last_millis = millis();
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

  if (gesture('A', 65, -20,  -50, 230, 100, 260, 100, 140, 255, 240) >= 35 ) {
    signing();
  } else  if (gesture('B', 65, -25, -40, 175, 255, 450, 230, 320, 255, 240) >= 35) {
    signing();
  }  else  if (gesture('C', 53, -25, -40, 180, 180, 295, 120, 200, 255, 242) >= 35) {
    signing();
  } else  if (gesture('D', 60, -20, -25, 175, 200, 390, 130, 195, 240, 242) >= 35) {
    signing();
  } else  if (gesture('E', 55, -30, -50, 160, 120, 225, 105, 165, 240, 240) >= 35) {
    signing();
  }  else  if (gesture('F', 60, -15, -25, 175, 130, 420, 150, 260, 240, 255) >= 35 ) {
    signing();
  } else  if (gesture('G', 15, 75, -25, 170, 140, 225, 115, 160, 240, 240) >= 35) {
    signing();
  } else  if (gesture('H', 30, 55, -40, 150, 280, 430, 120, 160, 240, 240) >= 35) {
    signing();
  }  else  if (gesture('I', 30, -75, -25, 160, 110, 235, 115, 330, 240, 240) >= 35) {
    signing();
  } else  if (gesture('J', 10, 0, -25 , 160, 100, 250, 120, 300,  240, 240) >= 35) {
    signing();
  } else  if (gesture('K', 15, -20, -25, 200, 230, 380, 130, 180, 255, 255) >= 35) {
    signing();
  } else  if (gesture('L', 30, -70, -25, 250, 200, 250, 120, 175, 255, 240) >= 35) {
    signing();
  } else  if (gesture('M', 0, -40, -25, 230, 120, 300, 115, 210, 240, 240) >= 35) {
    signing();
  } else  if (gesture('N', 20, -10, -50, 220, 120, 300, 140, 200, 243, 244 ) >= 35) {
    signing();
  } else  if (gesture('N', 20, -10, -50, 220, 120, 300, 140, 200, 243, 244 ) >= 35) {
    signing();
  } else  if (gesture('O', 50, -15, -25, 190, 125, 255, 125, 230, 255, 240 ) >= 35) {
    signing();
  } else  if (gesture('P', 5, -20, -25, 260, 260, 450, 150, 300, 255, 255) >= 35) {
    signing();
  } else  if (gesture( 'Q', -20, -15, -25, 170, 130, 225, 115, 200, 255, 242) >= 35) {
    signing();
  } else  if (gesture('R', 60, -30, -25, 140, 260, 300, 120, 220, 240, 240) >= 35) {
    signing();
  } else  if (gesture('S', 70, -20, -50, 180, 115, 245, 110, 150, 255, 240) >= 35) {
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
  Serial.println("Gyro X:" + String(KamoTalk_GyroX));
  Serial.println("Gyro Y:" + String(KamoTalk_GyroY));
  Serial.println("Gyro Z:" + String(KamoTalk_GyroZ));
  Serial.println("\n\nADC");
  Serial.println("Thumb:" + String(payload.adc_Thumb));
  Serial.println("Index:" + String(payload.adc_Index));
  Serial.println("Middle:" + String(payload.adc_Middle));
  Serial.println("Ring:" + String(payload.adc_Ring));
  Serial.println("Pinky:" + String(payload.adc_Pinky));
  Serial.println("=======================================================\n\n\n");
}

void LEDgreenON() {
  digitalWrite(LEDgreen, 1);
}

void LEDgreenOFF() {
  digitalWrite(LEDgreen, 0);
}
