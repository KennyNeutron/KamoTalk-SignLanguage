void DrawData() {
  char ch_Gyro[30] = "";
  sprintf(ch_Gyro, "G: %d,%d,%d", KamoTalk_GyroX, KamoTalk_GyroY, KamoTalk_GyroZ);


  char  ch_SensorVal[30] = "";
  sprintf(ch_SensorVal, "F: %d,%d,%d,%d,%d", Val_Thumb, Val_Index, Val_Middle, Val_Ring, Val_Pinky);

  char ch_PadByte[30] = "";
  sprintf(ch_PadByte, "P: %d,%d", ThumbByte, MiddleByte);

  u8g.setFont(u8g_font_helvR08);
  u8g.drawStr(0, 9, ch_Gyro);

  //  u8g.drawStr(0, 21, "gY:");
  //  u8g.drawStr(20, 21, ch_GyroY);
  //
  //  u8g.drawStr(0, 33, "gZ:");
  //  u8g.drawStr(20, 33, ch_GyroZ);

  u8g.drawStr(0, 21, ch_SensorVal);

  u8g.drawStr(0, 33, ch_PadByte);

  u8g.setFont(u8g_font_ncenB18);
  
  char ch_NowSigning[2] = { ' ' };
  if (SignPrinted) {
    sprintf(ch_NowSigning, "|%c|", NowSigning);
  } else {
    sprintf(ch_NowSigning, "%c", NowSigning);
  }

  u8g.drawStr(64, 55, ch_NowSigning);
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
