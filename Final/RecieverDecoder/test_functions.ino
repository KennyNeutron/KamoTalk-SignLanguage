
bool TestGesture(int ThisThumb, int ThisIndex, int ThisMiddle, int ThisRing, int ThisPinky, int ThisTolerance) {
  if (TestRange(Val_Thumb, ThisThumb, ThisTolerance) && TestRange(Val_Index, ThisIndex, ThisTolerance) && TestRange(Val_Middle, ThisMiddle, ThisTolerance) && TestRange(Val_Ring, ThisRing, ThisTolerance) && TestRange(Val_Pinky, ThisPinky, ThisTolerance)) {
    return true;
  } else {
    return false;
  }
  return false;
}

bool TestRange(int Value, int EqualTo, int Tolerance) {
  if (Value <= (EqualTo + Tolerance) && Value >= (EqualTo - Tolerance)) {
    return true;
  } else {
    return false;
  }
  return false;
}




void TestSensorValues() {
  //  if (abs(prev_ValThumb - Val_Thumb) > 15) {
  //    Serial.println("Thumb:" + String(Val_Thumb));
  //  }
  //
  //  if (abs(prev_ValIndex - Val_Index) > 15) {
  //    Serial.println("Index:" + String(Val_Index));
  //  }
  //
  //  if (abs(prev_ValMiddle - Val_Middle) > 15) {
  //    Serial.println("Middle:" + String(Val_Middle));
  //  }
  //
  //  if (abs(prev_ValRing - Val_Ring) > 15) {
  //    Serial.println("Ring:" + String(Val_Ring));
  //  }
  //
  //  if (abs(prev_ValPinky - Val_Pinky) > 15) {
  //    Serial.println("Pinky:" + String(Val_Pinky));
  //  }
  //
  //  Serial.println("Thumb Byte: " + String(ThumbByte()));
  //
  //
  //  Serial.print("angleX : ");
  //  Serial.print(KamoTalk_GyroX);
  //  Serial.print("\tangleY : ");
  //  Serial.print(KamoTalk_GyroY);
  //  Serial.print("\tangleZ : ");
  //  Serial.println(KamoTalk_GyroZ);


}

bool TestGyroYZ(int EqualToX, int EqualToY, int Tolerance) {
  if (TestGyroRange(KamoTalk_GyroX, EqualToX, Tolerance) && TestGyroRange(KamoTalk_GyroY, EqualToY, Tolerance)) {
    return true;
  } else {
    return false;
  }
  return false;
}


bool TestGyroRange(int Value, int EqualTo, int Tolerance) {
  if (Value <= (EqualTo + Tolerance) && Value >= (EqualTo - Tolerance)) {
    return true;
  } else {
    return false;
  }
  return false;
}
