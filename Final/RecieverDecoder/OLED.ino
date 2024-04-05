void DrawData() {
  char ch_GyroX[60] = { ' ' };
  int int_GyroX = (int)KamoTalk_GyroX;
  float f_GyroX = (abs(KamoTalk_GyroX) - abs(int_GyroX)) * 100000;
  int fra_GyroX = (int)f_GyroX;
  sprintf(ch_GyroX, "%d.%d", int_GyroX, fra_GyroX);

  char ch_GyroY[60] = { ' ' };
  int int_GyroY = (int)KamoTalk_GyroY;
  float f_GyroY = (abs(KamoTalk_GyroY) - abs(int_GyroY)) * 100000;
  int fra_GyroY = (int)f_GyroY;
  sprintf(ch_GyroY, "%d.%d", int_GyroY, fra_GyroY);

  char ch_GyroZ[60] = { ' ' };
  int int_GyroZ = (int)KamoTalk_GyroZ;
  float f_GyroZ = (abs(KamoTalk_GyroZ) - abs(int_GyroZ)) * 100000;
  int fra_GyroZ = (int)f_GyroZ;
  sprintf(ch_GyroZ, "%d.%d", int_GyroZ, fra_GyroZ);

  char  ch_SensorVal[30] = "";
  sprintf(ch_SensorVal, "%d,%d,%d,%d,%d|%d", Val_Thumb, Val_Index, Val_Middle, Val_Ring, Val_Pinky, ThumbByte);


  u8g.setFont(u8g_font_helvR08);
  u8g.drawStr(0, 10, "gX:");
  u8g.drawStr(20, 10, ch_GyroX);

  u8g.drawStr(0, 23, "gY:");
  u8g.drawStr(20, 23, ch_GyroY);

  u8g.drawStr(0, 36, "gZ:");
  u8g.drawStr(20, 36, ch_GyroZ);

  u8g.drawStr(0, 49, ch_SensorVal);

  char ch_NowSigning[2] = { ' ' };
  if (SignPrinted) {
    sprintf(ch_NowSigning, "|%c|", NowSigning);
  } else {
    sprintf(ch_NowSigning, "%c", NowSigning);
  }
  
  u8g.drawStr(100, 10, ch_NowSigning);
}

void DrawLetter() {
  char ch_NowSigning[2] = { ' ' };
  if (SignPrinted) {
    sprintf(ch_NowSigning, "|%c|", NowSigning);
  } else {
    sprintf(ch_NowSigning, "%c", NowSigning);
  }


  u8g.setFont(u8g_font_osb18);
  u8g.drawStr(50, 32, ch_NowSigning);
}
