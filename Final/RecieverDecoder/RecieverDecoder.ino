#include <SPI.h>
#include <Wire.h>
#include <EEPROM.h>
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


#define LEDred 2
#define LEDgreen 3
#define LEDblue 4

uint32_t last_millis = 0;

uint8_t SerialVal = 0;
uint8_t SignToSave = 0;
uint32_t Serial_LastMillis = 0;


void setup() {
  pinMode(LEDred, OUTPUT);
  pinMode(LEDgreen, OUTPUT);
  pinMode(LEDblue, OUTPUT);
  LEDredOFF();
  LEDgreenOFF();
  LEDblueOFF();
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

  //  Serial.println("EEPROM 1:" + String(EEPROM.read(1)));
  //  Serial.println("EEPROM 2:" + String(EEPROM.get(2, saved_Gx)));
  //  Serial.println("EEPROM 6:" + String(EEPROM.get(6, saved_Gy)));
  //  Serial.println("EEPROM 10:" + String(EEPROM.get(10, saved_Gz)));
  //  Serial.println("EEPROM 14:" + String(EEPROM.read(14)));
  //  Serial.println("EEPROM 16:" + String(EEPROM.read(16)));
  //  Serial.println("EEPROM 18:" + String(EEPROM.read(18)));
  //  Serial.println("EEPROM 20:" + String(EEPROM.read(20)));
  //  Serial.println("EEPROM 22:" + String(EEPROM.read(22)));
  //
  //  Serial.println("EEPROM 24:" + String(EEPROM.read(24)));
  //  Serial.println("EEPROM 25:" + String(EEPROM.read(25)));
  //  Serial.println("EEPROM 26:" + String(EEPROM.read(26)));
  //  Serial.println("EEPROM 27:" + String(EEPROM.read(27)));
  //  Serial.println("EEPROM 28:" + String(EEPROM.read(28)));


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


  if (NowSigning != ' ') {
    Serial.print(NowSigning);
  }




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

  if (Serial.available() > 0) {
    Serial_LastMillis = millis();
    SerialVal = Serial.read();
    if (SerialVal == '<') {
      LEDblueON();
      while (Serial.available() == 0) {
        if (millis() - Serial_LastMillis >= 3000) {
          goto SerialExit;
        }
      }
      SignToSave   = Serial.read() - 48;
      //      Serial.print("sign to save:");
      //      Serial.println(SignToSave);
      while (Serial.available() == 0) {
        if (millis() - Serial_LastMillis >= 3000) {
          goto SerialExit;
        }
      }
      SerialVal = Serial.read();
      if (SerialVal == '>') {
        saveEEPROM(SignToSave, 1, KamoTalk_GyroX, KamoTalk_GyroY, KamoTalk_GyroZ, Val_Thumb, Val_Index, Val_Middle, Val_Ring, Val_Pinky, ThumbByte, IndexByte, MiddleByte, RingByte, PinkyByte);
      }
      LEDblueOFF();
    } else if (SerialVal == '{') {
      LEDredON();
      while (Serial.available() == 0) {
        if (millis() - Serial_LastMillis >= 3000) {
          goto SerialExit;
        }
      }
      SignToSave   = Serial.read() - 48;
      //      Serial.print("sign to save:");
      //      Serial.println(SignToSave);
      while (Serial.available() == 0) {
        if (millis() - Serial_LastMillis >= 3000) {
          goto SerialExit;
        }
      }
      SerialVal = Serial.read();
      if (SerialVal == '}') {
        saveEEPROM(SignToSave, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
      }
      LEDredOFF();
    }
  }
SerialExit:
  delayMicroseconds(10);


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

void LEDredON() {
  digitalWrite(LEDred, 1);
}

void LEDredOFF() {
  digitalWrite(LEDred, 0);
}

void LEDblueON() {
  digitalWrite(LEDblue, 1);
}

void LEDblueOFF() {
  digitalWrite(LEDblue, 0);
}
