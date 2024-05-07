void Correspond() {
  //  if ( TestGesture(250, 320, 285, 130, 350, UnitTolerance)) {
  //    Serial.println("");
  //    delay(2000);
  //  }


  //  if (TestGesture(290,  200,  475,  135, 220, UnitTolerance)) {
  //    Serial.println("");
  //    delay(2000);
  //  }

  byte LetterScore = 0;
  byte prev_LetterScore = 0;

  LetterScore = gesture('A', 82, 64, 74, 66, 72, 149, 278, 118, 0, 14, 14, 14, 14);

  if (LetterScore >= 66) {
    NowSigning = 'A';
    prev_LetterScore = LetterScore;
  }


  LetterScore = gesture('B', 84, 68, 78, 342, 129, 202, 372, 271, 0, 14, 14, 14, 14);
  if (LetterScore >= 66) {
    if (LetterScore >= prev_LetterScore) {
      NowSigning = 'B';
      prev_LetterScore = LetterScore;
    }
  }


  LetterScore = gesture('C', 53, 18, 75, 87, 94, 142, 316, 159, 0, 14, 14, 14, 14);
  if (LetterScore >= 65) {
    if (LetterScore >= prev_LetterScore) {
      NowSigning = 'C';
      prev_LetterScore = LetterScore;
    }
  }

  LetterScore = gesture('D', 71, 25, 80, 85, 170, 140, 297, 125, 14, 0, 13, 13, 13);
  if (LetterScore >= 65) {
    if (LetterScore >= prev_LetterScore) {
      NowSigning = 'D';
      prev_LetterScore = LetterScore;
    }
  }

  LetterScore = gesture('E', 83, 46, 67, 79, 75, 124, 270, 117, 15, 15, 15, 15, 15);
  if (LetterScore >= 65) {
    if (LetterScore >= prev_LetterScore) {
      NowSigning = 'E';
      prev_LetterScore = LetterScore;
    }
  }

  LetterScore = gesture('F', 86, 71, 80, 58, 80, 200, 403, 219, 1, 1, 12, 12, 12);
  if (LetterScore >= 65) {
    if (LetterScore >= prev_LetterScore) {
      NowSigning = 'F';
      prev_LetterScore = LetterScore;
    }
  }

  LetterScore = gesture('G', 77, 309, 105, 67, 86, 135, 254, 111, 1, 1, 12, 12, 12);
  if (LetterScore >= 65) {
    if (LetterScore >= prev_LetterScore) {
      NowSigning = 'G';
      prev_LetterScore = LetterScore;
    }
  }

  LetterScore = gesture('H', 137, 255, 166, 61, 112, 188, 277, 116, 0, 2, 2, 8, 8);
  if (LetterScore >= 65) {
    if (LetterScore >= prev_LetterScore) {
      NowSigning = 'H';
      prev_LetterScore = LetterScore;
    }
  }

  LetterScore = gesture('I', 87, 85, 57, 63, 70, 67, 133, 236, 7, 7, 7, 7, 0);
  if (LetterScore >= 63) {
    if (LetterScore >= prev_LetterScore) {
      NowSigning = 'I';
      prev_LetterScore = LetterScore;
    }
  }

  LetterScore = gesture('J', 115, 237, 126, 110, 75, 130, 259, 197, 7, 7, 7, 7, 0);
  if (LetterScore >= 65) {
    if (LetterScore >= prev_LetterScore) {
      NowSigning = 'J';
      prev_LetterScore = LetterScore;
    }
  }

  LetterScore = gesture('K', 75, 314, 105, 107, 146, 199, 276, 128, 0, 0, 0, 8, 8);
  if (LetterScore >= 65) {
    if (LetterScore >= prev_LetterScore) {
      NowSigning = 'K';
      prev_LetterScore = LetterScore;
    }
  }

  LetterScore = gesture('L', 83, 70, 71, 89, 107, 135, 256, 112, 0, 0, 12, 12, 12);
  if (LetterScore >= 64) {
    if (LetterScore >= prev_LetterScore) {
      NowSigning = 'L';
      prev_LetterScore = LetterScore;
    }
  }

  LetterScore = gesture('M', 55, 359, 90, 296, 55, 119, 240, 105, 7, 7, 7, 7, 0);
  if (LetterScore >= 67) {
    if (LetterScore >= prev_LetterScore) {
      NowSigning = 'M';
      prev_LetterScore = LetterScore;
    }
  }

  LetterScore = gesture('N', 80, 38, 82, 355, 69, 144, 274, 129, 3, 3, 3, 8, 8 );
  if (LetterScore >= 65) {
    if (LetterScore >= prev_LetterScore) {
      NowSigning = 'N';
      prev_LetterScore = LetterScore;
    }
  }

  LetterScore = gesture('O', 78, 38, 80, 67, 84, 130, 264, 133, 15, 15, 15, 15, 15);
  if (LetterScore >= 65) {
    if (LetterScore >= prev_LetterScore) {
      NowSigning = 'O';
      prev_LetterScore = LetterScore;
    }
  }

  LetterScore = gesture('P', 10, 345, 150, 130, 125, 180, 105, 130, 0, 0, 0, 8, 8);
  if (LetterScore >= 65) {
    if (LetterScore >= prev_LetterScore) {
      NowSigning = 'P';
      prev_LetterScore = LetterScore;
    }
  }

  LetterScore = gesture('Q', 352, 325, 190, 417, 68, 128, 273, 138, 0, 0, 12, 12, 12);
  if (LetterScore >= 65) {
    if (LetterScore >= prev_LetterScore) {
      NowSigning = 'Q';
      prev_LetterScore = LetterScore;
    }
  }

  LetterScore = gesture('R', 94, 114, 80, 333, 112, 196, 264, 117, 0, 2, 2, 8, 8 );
  if (LetterScore >= 65) {
    if (LetterScore >= prev_LetterScore) {
      NowSigning = 'R';
      prev_LetterScore = LetterScore;
    }
  }

  LetterScore = gesture('S', 107, 143, 77, 322, 65, 137, 231, 106, 15, 15, 15, 15, 15 );
  if (LetterScore >= 58) {
    if (LetterScore >= prev_LetterScore) {
      NowSigning = 'S';
      prev_LetterScore = LetterScore;
    }
  }

  LetterScore = gesture('T', 72, 23, 82, 1, 80, 125, 249, 109, 0, 0, 12, 12, 12);
  if (LetterScore >= 54) {
    if (LetterScore >= prev_LetterScore) {
      NowSigning = 'T';
      prev_LetterScore = LetterScore;
    }
  }

  LetterScore = gesture('U', 66, 17, 82, 62, 174, 218, 254, 125, 12, 2, 2, 9, 9);
  if (LetterScore >= 65) {
    if (LetterScore >= prev_LetterScore) {
      NowSigning = 'U';
      prev_LetterScore = LetterScore;
    }
  }

  LetterScore = gesture('V', 77, 30, 83, 120, 156, 210, 304, 145, 0, 0, 0, 8, 8);
  if (LetterScore >= 65) {
    if (LetterScore >= prev_LetterScore) {
      NowSigning = 'V';
      prev_LetterScore = LetterScore;
    }
  }

  LetterScore = gesture('W', 80, 30, 80, 160, 260, 365, 130, 150, 8, 0, 0, 0, 1);
  if (LetterScore >= 65) {
    if (LetterScore >= prev_LetterScore) {
      NowSigning = 'W';
      prev_LetterScore = LetterScore;
    }
  }
  LetterScore = gesture('X', 66, 329, 104, 88, 76, 123, 270, 138, 14, 0, 13, 13, 13);
  if (LetterScore >= 65) {
    if (LetterScore >= prev_LetterScore) {
      NowSigning = 'X';
      prev_LetterScore = LetterScore;
    }
  }

  LetterScore = gesture('Y', 87, 81, 74, 75, 67, 114, 262, 244, 0, 6, 6, 6, 0);
  if (LetterScore >= 65) {
    if (LetterScore >= prev_LetterScore) {
      NowSigning = 'Y';
      prev_LetterScore = LetterScore;
    }
  }

  LetterScore = gesture('Z', 46, 306, 141, 135, 126, 136, 289, 121, 0, 0, 12, 12, 12);
  if (LetterScore >= 65) {
    if (LetterScore >= prev_LetterScore) {
      NowSigning = 'Z';
      prev_LetterScore = LetterScore;
    }
  }


  LetterScore = gesture('#', 150, 200, 130, 170, 230, 180, 100, 350, 6, 0, 5, 5, 0);
  if (LetterScore >= 65) {
    if (LetterScore >= prev_LetterScore) {
      NowSigning = '#';
      prev_LetterScore = LetterScore;
    }
  }

  LetterScore = gesture('&', 140, 200, 125, 180, 10, 150, 0, 130, 15, 15, 15, 15, 15);
  if (LetterScore >= 65) {
    if (LetterScore >= prev_LetterScore) {
      NowSigning = '&';
      prev_LetterScore = LetterScore;
    }
  }

  LetterScore = gesture('$', 132, 212, 119, 42, 139, 163, 348, 133, 14, 0, 13, 13, 13);
  if (LetterScore >= 65) {
    if (LetterScore >= prev_LetterScore) {
      NowSigning = '$';
      prev_LetterScore = LetterScore;
    }
  }

  LetterScore = gesture('0', 38, 351, 100, 77, 77, 132, 269, 139, 15, 15, 15, 15, 15);
  if (LetterScore >= 65) {
    if (LetterScore >= prev_LetterScore) {
      NowSigning = '0';
      prev_LetterScore = LetterScore;
    }
  }

  LetterScore = gesture('1', 81, 335, 94, 71, 114, 145, 251, 109, 0, 0, 12, 12, 12);
  if (LetterScore >= 60) {
    if (LetterScore >= prev_LetterScore) {
      NowSigning = '1';
      prev_LetterScore = LetterScore;
    }
  }

  LetterScore = gesture('2', 80, 280, 120, 130, 165, 290, 100, 140, 12, 0, 0, 9, 9);
  if (LetterScore >= 65) {
    if (LetterScore >= prev_LetterScore) {
      NowSigning = '2';
      prev_LetterScore = LetterScore;
    }
  }

  LetterScore = gesture('3', 76, 349, 92, 109, 152, 204, 290, 136, 0, 0, 0, 8, 8);
  if (LetterScore >= 65) {
    if (LetterScore >= prev_LetterScore) {
      NowSigning = '3';
      prev_LetterScore = LetterScore;
    }
  }

  LetterScore = gesture('4', 87, 21, 88, 54, 125, 190, 375, 226, 0, 0, 0, 0, 0);
  if (LetterScore >= 65) {
    if (LetterScore >= prev_LetterScore) {
      NowSigning = '4';
      prev_LetterScore = LetterScore;
    }
  }


  LetterScore = gesture('5', 80, 330, 95, 105, 139, 204, 409, 264, 0, 0, 0, 0, 0);
  if (LetterScore >= 65) {
    if (LetterScore >= prev_LetterScore) {
      NowSigning = '5';
      prev_LetterScore = LetterScore;
    }
  }

  LetterScore = gesture('6', 70, 315, 110, 145, 165, 310, 130, 155, 8, 0, 0, 0, 1);
  if (LetterScore >= 56) {
    if (LetterScore >= prev_LetterScore) {
      NowSigning = '6';
      prev_LetterScore = LetterScore;
    }
  }

  LetterScore = gesture('7', 80, 336, 94, 58, 157, 214, 254, 221, 4, 0, 0, 1, 0);
  if (LetterScore >= 65) {
    if (LetterScore >= prev_LetterScore) {
      NowSigning = '7';
      prev_LetterScore = LetterScore;
    }
  }

  LetterScore = gesture('8', 77, 321, 99, 68, 153, 135, 395, 238, 2, 0, 1, 0, 0);
  if (LetterScore >= 65) {
    if (LetterScore >= prev_LetterScore) {
      NowSigning = '8';
      prev_LetterScore = LetterScore;
    }
  }

  LetterScore = gesture('9', 84, 18, 88, 66, 83, 193, 406, 237, 1, 1, 0, 0, 0);
  if (LetterScore >= 65) {
    if (LetterScore >= prev_LetterScore) {
      NowSigning = '9';
      prev_LetterScore = LetterScore;
    }
  }


  LetterScore = gesture('}', 130, 200, 100, 45, 85, 190, 310, 120, 13, 13, 0, 11, 11);
  if (LetterScore >= 65) {
    if (LetterScore >= prev_LetterScore) {
      NowSigning = '}';
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
