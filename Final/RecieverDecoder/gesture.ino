uint8_t gesture(char Letter, float gX, float gY, float gZ, int vThumb, int vIndex, int vMiddle, int vRing, int vPinky, int vThumbByte, int vMiddleByte) {
  byte GestureVal = 0;
  //check GyroX
  if (VerifyValueFloat(KamoTalk_GyroX, gX, GyroTolerance)) {
    GestureVal += 5;
  }

  //check GyroY
  if (VerifyValueFloat(KamoTalk_GyroY, gY, GyroTolerance)) {
    GestureVal += 5;
  }

  //check GyroZ
  if (VerifyValueFloat(KamoTalk_GyroZ, gZ, GyroTolerance)) {
    GestureVal += 5;
  }


  //check Thumb Flex Value
  if (VerifyValueFloat(Val_Thumb, vThumb, UnitTolerance)) {
    GestureVal++;
  }

  //check Index Flex Value
  if (VerifyValue(Val_Index, vIndex, UnitTolerance)) {
    GestureVal++;
  }

  //check Middle Flex Value
  if (VerifyValue(Val_Middle, vMiddle, UnitTolerance)) {
    GestureVal++;
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
    GestureVal += 10;
  }

  if (MiddleByte == vMiddleByte) {
    GestureVal += 10;
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

bool VerifyValueFloat(float val, float equalto, float tolerance) {
  if (equalto >= (val - tolerance) && equalto <= (val + tolerance)) {
    return true;
  } else {
    return false;
  }
}
