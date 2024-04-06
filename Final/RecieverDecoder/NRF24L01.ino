void DecryptData() {
  Val_Thumb = payload.adc_Thumb;
  Val_Index = payload.adc_Index;
  Val_Middle = payload.adc_Middle;
  Val_Ring = payload.adc_Ring;
  Val_Pinky = payload.adc_Pinky;

  KamoTalk_GyroX = payload.kt_GyroX;
  KamoTalk_GyroY = payload.kt_GyroY;
  KamoTalk_GyroZ = payload.kt_GyroZ;

  ThumbByte=payload.byteThumb;
  MiddleByte=payload.byteMiddle;
}
