void DrawData() {


  char  ch_SensorVal[100] = "";
  sprintf(ch_SensorVal, "F: %d,%d,%d,%d,%d", Val_Thumb, Val_Index, Val_Middle, Val_Ring, Val_Pinky);

  char ch_PadByte[30] = "";
  sprintf(ch_PadByte, "P: %d,%d,%d,%d,%d", ThumbByte, IndexByte, MiddleByte, RingByte, PinkyByte);

  u8g.setFont(u8g_font_helvR08);


  u8g.setPrintPos(0, 9);
  u8g.print("G: " + String(KamoTalk_GyroX) + "," + String(KamoTalk_GyroY) + "," + String(KamoTalk_GyroZ));


  u8g.drawStr(0, 21, ch_SensorVal);

  u8g.drawStr(0, 33, ch_PadByte);

  u8g.setPrintPos(0, 45);
  u8g.print("TS: " + String(SignToSave));

  // u8g.setFont(u8g_font_helvB14);

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
