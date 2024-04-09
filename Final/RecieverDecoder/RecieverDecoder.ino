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

  byte LetterScore = 0;
  byte prev_LetterScore = 0;

  LetterScore = gesture('A', 90, 90, 80, 155, 80, 180, 100, 120, 0, 14, 14, 14, 14);

  if ( LetterScore >= 59 ) {
    NowSigning = 'A';
    prev_LetterScore = LetterScore;
  }


  LetterScore = gesture('B', 80, 50, 80, 150, 250, 440, 230, 300 , 0, 0, 0, 0, 0);
  if (LetterScore >= 59) {
    if (LetterScore >= prev_LetterScore) {
      NowSigning = 'B';
      prev_LetterScore = LetterScore;
    }
  }


  LetterScore = gesture('C', 70, 350, 100, 250, 140, 300, 120, 180, 0, 14, 14, 14, 14);
  if (LetterScore >= 59) {
    if (LetterScore >= prev_LetterScore) {
      NowSigning = 'C';
      prev_LetterScore = LetterScore;
    }
  }

  LetterScore = gesture('D', 60, 350, 100, 150, 230, 260, 115, 160, 14, 0, 13, 13, 13);
  if (LetterScore >= 59) {
    if (LetterScore >= prev_LetterScore) {
      NowSigning = 'D';
      prev_LetterScore = LetterScore;
    }
  }

  LetterScore = gesture('E',  80, 30, 80, 165, 112, 230, 100, 150, 15, 15, 15, 15, 15);
  if (LetterScore >= 59) {
    if (LetterScore >= prev_LetterScore) {
      NowSigning = 'E';
      prev_LetterScore = LetterScore;
    }
  }

  LetterScore = gesture('F', 70, 350, 90, 145, 100, 450, 150, 300,  1, 1, 0, 0, 0);
  if (LetterScore >= 59) {
    if (LetterScore >= prev_LetterScore) {
      NowSigning = 'F';
      prev_LetterScore = LetterScore;
    }
  }

  LetterScore = gesture('G', 150, 260, 180, 160, 115, 220, 100, 140, 1, 1, 12, 12, 12);
  if (LetterScore >= 59) {
    if (LetterScore >= prev_LetterScore) {
      NowSigning = 'G';
      prev_LetterScore = LetterScore;
    }
  }

  LetterScore = gesture('H', 70, 270, 170, 170, 230, 430, 125, 150,  0, 2, 2, 8, 8);
  if (LetterScore >= 59) {
    if (LetterScore >= prev_LetterScore) {
      NowSigning = 'H';
      prev_LetterScore = LetterScore;
    }
  }

  LetterScore = gesture('I', 90, 100, 75, 140, 100, 220, 105, 300, 7, 7, 7, 7, 0);
  if (LetterScore >= 59) {
    if (LetterScore >= prev_LetterScore) {
      NowSigning = 'I';
      prev_LetterScore = LetterScore;
    }
  }

  LetterScore = gesture('J',  130, 250, 160, 140, 100, 220, 105, 300, 7, 7, 7, 7, 0);
  if (LetterScore >= 59) {
    if (LetterScore >= prev_LetterScore) {
      NowSigning = 'J';
      prev_LetterScore = LetterScore;
    }
  }

  LetterScore = gesture('K', 90, 270, 150, 170, 225, 340, 120, 140, 0, 0, 0, 8, 8);
  if (LetterScore >= 59) {
    if (LetterScore >= prev_LetterScore) {
      NowSigning = 'K';
      prev_LetterScore = LetterScore;
    }
  }

  LetterScore = gesture('L', 80, 50, 80, 215, 160, 200, 105, 142, 0, 0, 12, 12, 12);
  if (LetterScore >= 59) {
    if (LetterScore >= prev_LetterScore) {
      NowSigning = 'L';
      prev_LetterScore = LetterScore;
    }
  }

  LetterScore = gesture('M', 340, 25, 315, 140, 110, 210, 115, 160, 0, 6, 6, 6, 0);
  if (LetterScore >= 59) {
    if (LetterScore >= prev_LetterScore) {
      NowSigning = 'M';
      prev_LetterScore = LetterScore;
    }
  }

  LetterScore = gesture('N', 350, 10, 300, 170, 110, 235, 120, 165, 0, 2, 2, 8, 8);
  if (LetterScore >= 59) {
    if (LetterScore >= prev_LetterScore) {
      NowSigning = 'N';
      prev_LetterScore = LetterScore;
    }
  }

  LetterScore = gesture('O', 5, 350, 170, 150, 110, 200, 100, 155, 15, 15, 15, 15, 15 );
  if (LetterScore >= 59) {
    if (LetterScore >= prev_LetterScore) {
      NowSigning = 'O';
      prev_LetterScore = LetterScore;
    }
  }

  LetterScore = gesture('P', 350, 350, 250, 230, 290, 450, 130, 240, 0, 2, 2, 0, 0 );
  if (LetterScore >= 59) {
    if (LetterScore >= prev_LetterScore) {
      NowSigning = 'P';
      prev_LetterScore = LetterScore;
    }
  }

  LetterScore = gesture('Q', 350, 350, 250, 155, 130, 215, 100, 135, 1, 1, 12, 12, 12 );
  if (LetterScore >= 59) {
    if (LetterScore >= prev_LetterScore) {
      NowSigning = 'Q';
      prev_LetterScore = LetterScore;
    }
  }

  LetterScore = gesture('R', 80, 15, 90, 110, 220, 260, 100, 150, 0, 0, 0, 8, 8);
  if (LetterScore >= 59) {
    if (LetterScore >= prev_LetterScore) {
      NowSigning = 'R';
      prev_LetterScore = LetterScore;
    }
  }

  LetterScore = gesture('S', 350, 10, 300, 250, 110, 250, 110, 140, 0, 14, 14, 14, 14);
  if (LetterScore >= 59) {
    if (LetterScore >= prev_LetterScore) {
      NowSigning = 'S';
      prev_LetterScore = LetterScore;
    }
  }

  LetterScore = gesture('T', 80, 15, 90, 175, 1200, 200, 100, 130, 0, 2, 2, 8, 8);
  if (LetterScore >= 59) {
    if (LetterScore >= prev_LetterScore) {
      NowSigning = 'T';
      prev_LetterScore = LetterScore;
    }
  }

  LetterScore = gesture('U', 70, 350, 100, 120, 270, 340, 110, 150, 12, 2, 2, 9, 9);
  if (LetterScore >= 59) {
    if (LetterScore >= prev_LetterScore) {
      NowSigning = 'U';
      prev_LetterScore = LetterScore;
    }
  }

  LetterScore = gesture('V', 80, 15, 90, 110, 220, 260, 100, 150, 12, 0, 0, 9, 9);
  if (LetterScore >= 59) {
    if (LetterScore >= prev_LetterScore) {
      NowSigning = 'V';
      prev_LetterScore = LetterScore;
    }
  }

  LetterScore = gesture('W', 80, 30, 80, 160, 260, 365, 130, 150, 8, 0, 0, 0, 1);
  if (LetterScore >= 59) {
    if (LetterScore >= prev_LetterScore) {
      NowSigning = 'W';
      prev_LetterScore = LetterScore;
    }
  }

  LetterScore = gesture('X', 80, 50, 80, 215, 160, 200, 105, 142, 1, 1, 12, 12, 12);
  if (LetterScore >= 59) {
    if (LetterScore >= prev_LetterScore) {
      NowSigning = 'X';
      prev_LetterScore = LetterScore;
    }
  }

  LetterScore = gesture('Y', 100, 100, 70, 155, 100, 210, 105, 170, 0, 6, 6, 6, 0);
  if (LetterScore >= 59) {
    if (LetterScore >= prev_LetterScore) {
      NowSigning = 'Y';
      prev_LetterScore = LetterScore;
    }
  }

  LetterScore = gesture('Z', 20, 300, 180, 123, 200, 180, 100, 145, 0, 0, 12, 12, 12);
  if (LetterScore >= 59) {
    if (LetterScore >= prev_LetterScore) {
      NowSigning = 'Z';
      prev_LetterScore = LetterScore;
    }
  }
  
  signing();
  if (prev_LetterScore == 0) {
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
