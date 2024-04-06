uint8_t gesture(char Letter,int gX, int gY, int gZ, int vThumb, int vIndex, int vMiddle, int vRing, int vPinky, int vThumbByte, int vMiddleByte) {
  byte GestureVal = 0;
  //check GyroX
  if (VerifyValue(KamoTalk_GyroX, gX, GyroTolerance)) {
    GestureVal++;
  }

  //check GyroY
  if (VerifyValue(KamoTalk_GyroY, gY, GyroTolerance)) {
    GestureVal++;
  }

  //check Thumb Flex Value
  if (VerifyValue(Val_Thumb, vThumb, UnitTolerance)) {
    GestureVal++;
  }

  //check Index Flex Value
  if (VerifyValue(Val_Index, vIndex, UnitTolerance)) {
    GestureVal+=5;
  }

  //check Middle Flex Value
  if (VerifyValue(Val_Middle, vMiddle, UnitTolerance)) {
    GestureVal+=5;
  }

  //check Ring Flex Value
  if (VerifyValue(Val_Ring, vRing, UnitTolerance)) {
    GestureVal++;
  }

  //check Pinky Flex Value
  if (VerifyValue(Val_Pinky, vPinky, UnitTolerance)) {
    GestureVal++;
  }

  if (ThumbByte == vThumbByte) {
    GestureVal+=10;
  }

  if (MiddleByte == vMiddleByte) {
    GestureVal+=10;
  }

  NowSigning = Letter;


  return GestureVal;

}


bool VerifyValue(int val, int equalto, int tolerance) {
  if (equalto >= (val - tolerance) && equalto <= (val + tolerance)) {
    return true;
  } else {
    return false;
  }
}
