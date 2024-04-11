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
  if (LetterScore >= 67) {
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

  LetterScore = gesture('Q', 350, 350, 250, 155, 130, 215, 100, 135, 0, 0, 12, 12, 12 );
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

  LetterScore = gesture('Z', 30, 330, 140, 130, 145, 160, 10, 140, 0, 0, 12, 12, 12);
  if (LetterScore >= 59) {
    if (LetterScore >= prev_LetterScore) {
      NowSigning = 'Z';
      prev_LetterScore = LetterScore;
    }
  }


  LetterScore = gesture('#', 150, 200, 130, 170, 230, 180, 100, 350, 6, 0, 5, 5, 0);
  if (LetterScore >= 59) {
    if (LetterScore >= prev_LetterScore) {
      NowSigning = '#';
      prev_LetterScore = LetterScore;
    }
  }

  LetterScore = gesture('&', 140, 200, 125, 180, 10, 150, 0, 130, 15, 15, 15, 15, 15);
  if (LetterScore >= 59) {
    if (LetterScore >= prev_LetterScore) {
      NowSigning = '&';
      prev_LetterScore = LetterScore;
    }
  }

  LetterScore = gesture('$', 190, 250, 180, 155, 90, 150, 95, 130, 0, 14, 14, 14, 14);
  if (LetterScore >= 59) {
    if (LetterScore >= prev_LetterScore) {
      NowSigning = '$';
      prev_LetterScore = LetterScore;
    }
  }

  LetterScore = gesture('0', 85, 300, 100, 175, 85, 165, 100, 140, 15, 15, 15, 15, 15);
  if (LetterScore >= 59) {
    if (LetterScore >= prev_LetterScore) {
      NowSigning = '0';
      prev_LetterScore = LetterScore;
    }
  }

  LetterScore = gesture('1', 90, 270, 120, 130, 136, 160, 100, 155, 14, 0, 13, 13, 13);
  if (LetterScore >= 59) {
    if (LetterScore >= prev_LetterScore) {
      NowSigning = '1';
      prev_LetterScore = LetterScore;
    }
  }

  LetterScore = gesture('2', 80, 280, 120, 130, 165, 290, 100, 140, 12, 0, 0, 9, 9);
  if (LetterScore >= 59) {
    if (LetterScore >= prev_LetterScore) {
      NowSigning = '2';
      prev_LetterScore = LetterScore;
    }
  }

  LetterScore = gesture('3', 100, 250, 110, 170, 160, 330, 120, 165, 0, 0, 0, 8, 8);
  if (LetterScore >= 59) {
    if (LetterScore >= prev_LetterScore) {
      NowSigning = '3';
      prev_LetterScore = LetterScore;
    }
  }

  LetterScore = gesture('4', 80, 320, 100, 115, 170, 300, 145, 256, 0, 0, 0, 0, 0);
  if (LetterScore >= 62) {
    if (LetterScore >= prev_LetterScore) {
      NowSigning = '4';
      prev_LetterScore = LetterScore;
    }
  }


  LetterScore = gesture('5', 80, 320, 100, 230, 170, 300, 145, 256, 0, 0, 0, 0, 0);
  if (LetterScore >= 59) {
    if (LetterScore >= prev_LetterScore) {
      NowSigning = '5';
      prev_LetterScore = LetterScore;
    }
  }

  LetterScore = gesture('6', 70, 315, 110, 145, 165, 310, 130, 155, 8, 0, 0, 0, 1);
  if (LetterScore >= 59) {
    if (LetterScore >= prev_LetterScore) {
      NowSigning = '6';
      prev_LetterScore = LetterScore;
    }
  }

  LetterScore = gesture('7', 90, 70, 80, 140, 150, 290, 130, 250, 4, 0, 0, 1, 0);
  if (LetterScore >= 59) {
    if (LetterScore >= prev_LetterScore) {
      NowSigning = '7';
      prev_LetterScore = LetterScore;
    }
  }

  LetterScore = gesture('8', 90, 70, 80, 140, 150, 290, 130, 250, 2, 0, 1, 0, 0);
  if (LetterScore >= 59) {
    if (LetterScore >= prev_LetterScore) {
      NowSigning = '8';
      prev_LetterScore = LetterScore;
    }
  }

  LetterScore = gesture('9', 90, 70, 80, 140, 150, 290, 130, 250, 1, 1, 0, 0, 0);
  if (LetterScore >= 59) {
    if (LetterScore >= prev_LetterScore) {
      NowSigning = '9';
      prev_LetterScore = LetterScore;
    }
  }
  char eepromToSign = '[';
  for (int a = 1; a <= 30; a++) {
    getEEPROM(a);
    if (saved_command == 1) {
      LetterScore = gesture(eepromToSign, saved_Gx, saved_Gy, saved_Gz, saved_fThumb, saved_fIndex, saved_fMiddle, saved_fRing, saved_fPinky, saved_pThumb, saved_pIndex, saved_pMiddle, saved_pRing, saved_pPinky);
      if (LetterScore >= 65) {
        if (LetterScore >= prev_LetterScore) {
          NowSigning = eepromToSign;
          prev_LetterScore = LetterScore;
        }
      }
    }
    eepromToSign++;
  }

  SignScore = prev_LetterScore;

  signing();

  if (prev_LetterScore == 0) {
    NowSigning = ' ';
    SignPrinted = false;
  }


}
