#include <SPI.h>
#include <Wire.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "DataStructure.h"
#include "variables.h"

//======================================= OLED ==================================================
#include "U8glib.h"
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE | U8G_I2C_OPT_DEV_0); // I2C / TWI
//U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_DEV_0 | U8G_I2C_OPT_NO_ACK | U8G_I2C_OPT_FAST);  // Fast I2C / TWI
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

  if (gesture('A', 90, 70, 80, 250, 110, 250, 110, 140, 255, 240) >= 33 && IndexByte == 240) {
    signing();
  } else  if (gesture('B', 80, 50, 80, 150, 250, 440, 230, 300 , 255, 251) >= 33  && IndexByte == 255) {
    signing();
  } else  if (gesture('C', 70, 350, 100, 250, 140, 300, 120, 180, 255, 255) >= 33 && IndexByte == 255) {
    signing();
  }   else  if (gesture('D', 60, 350, 100, 150, 230, 260, 115, 160, 240, 240 ) >= 33 && IndexByte == 255) {
    signing();
  }   else  if (gesture('E', 80, 30, 80, 165, 112, 230, 100, 150, 240, 240 ) >= 33 && IndexByte == 240) {
    signing();
  }   else  if (gesture('F', 70, 350, 90, 145, 100, 450, 150, 300, 248, 255 ) >= 33) {
    signing();
  } else  if (gesture('G', 150, 260, 180, 160, 115, 220, 100, 140, 240, 240 ) >= 33) {
    signing();
  } else  if (gesture('H', 70, 270, 170, 170, 230, 430, 125, 150, 255, 241 ) >= 23 && IndexByte == 253) {
    signing();
  } else  if (gesture('I', 90, 100, 75, 140, 100, 220, 105, 300, 248, 248 ) >= 33) {
    signing();
  } else  if (gesture('J', 130, 250, 160, 140, 100, 220, 105, 300, 248, 248 ) >= 33) {
    signing();
  } else  if (gesture('K', 90, 270, 150, 170, 225, 340, 120, 140, 255, 255) >= 23 && IndexByte == 255 && RingByte == 241) {
    signing();
  } else   if (gesture('L', 80, 50, 80, 150, 250, 440, 230, 300 , 255, 240) >= 33 && IndexByte == 255) {
    signing();
  }  else   if (gesture('M', 330, 15, 290, 170, 110, 270, 110, 150, 240, 240) >= 33 ) {
    signing();
  }  else   if (gesture('N',  330, 15, 290, 170, 110, 270, 110, 150, 242, 255) >= 23 && IndexByte == 255 ) {
    signing();
  } else  if (gesture('O', 70, 350, 100, 250, 140, 300, 120, 180, 248, 248) >= 33) {
    signing();
  }  else  if (gesture('P', 350, 350, 250, 230, 290, 450, 130, 240, 255, 249) >= 33) {
    signing();
  }   else  if (gesture('Q', 350, 350, 250, 155, 130, 215, 100, 135, 255, 240) >= 33 && RingByte == 240 ) {
    signing();
  }   else  if (gesture('R', 80, 20, 80, 120, 280, 350, 100, 160, 255, 255) >= 23  && RingByte == 240) {
    signing();
  }    else  if (gesture('T', 90, 250, 120, 180, 130, 290, 130, 150, 255, 243) >= 23) {
    signing();
  } else  if (gesture('&', 160, 190, 110, 140, 110, 255, 105, 160, 240, 240) >= 33) {
    signing();
  }  else  if (gesture('@', 160, 205, 135, 140, 210, 245, 110, 225, 249, 250 ) >= 33) {
    signing();
  } else if (gesture('S', 350, 10, 300, 250, 110, 250, 110, 140, 255, 240) >= 33 && IndexByte == 240  ) {
    signing();
  }    else {
    NowSigning = ' ';
    SignPrinted = false;
  }

}

void signing() {
  if (NowSigning == Prev_NowSigning) {
    GestureCount++;
    if (GestureCount >= 5) {
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
