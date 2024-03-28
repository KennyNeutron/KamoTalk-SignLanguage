#define Sensor_Thumb A0
#define Sensor_Index A1
#define Sensor_Middle A2
#define Sensor_Ring A3
#define Sensor_Pinky A6

int Val_Thumb = 0;
int Val_Index = 0;
int Val_Middle = 0;
int Val_Ring = 0;
int Val_Pinky = 0;

int prev_ValThumb = 0;
int prev_ValIndex = 0;
int prev_ValMiddle = 0;
int prev_ValRing = 0;
int prev_ValPinky = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("Sign Language Gloves on ESP32");
  Serial.println("SYSTEM STARTING...\n\n\n");

  pinMode(Sensor_Thumb, INPUT);
  pinMode(Sensor_Index, INPUT);
  pinMode(Sensor_Middle, INPUT);
  pinMode(Sensor_Ring, INPUT);
  pinMode(Sensor_Pinky, INPUT);

}

int ThisTolerance = 20;
void loop() {
  Val_Thumb = analogRead(Sensor_Thumb);
  Val_Index = analogRead(Sensor_Index);
  Val_Middle = analogRead(Sensor_Middle);
  Val_Ring = analogRead(Sensor_Ring);
  Val_Pinky = analogRead(Sensor_Pinky);


//  TestSensorValues();

  if (TestRange(Val_Thumb, 250, ThisTolerance) && TestRange(Val_Index, 320, ThisTolerance) && TestRange(Val_Middle, 285, ThisTolerance) && TestRange(Val_Ring, 130, ThisTolerance) && TestRange(Val_Pinky, 350, ThisTolerance)) {
    Serial.println("Rock and Roll");
    //Serial.println("Thumb:" + String(Val_Thumb));
  }

  if (TestRange(Val_Thumb, 260, ThisTolerance) && TestRange(Val_Index, 150, ThisTolerance) && TestRange(Val_Middle, 475, ThisTolerance) && TestRange(Val_Ring, 135, ThisTolerance) && TestRange(Val_Pinky, 220, ThisTolerance)) {
    Serial.println("Pakyu Bitch");
    //Serial.println("Thumb:" + String(Val_Thumb));
  }


  delay(1000);



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
  if (abs(prev_ValThumb - Val_Thumb) > 15) {
    Serial.println("Thumb:" + String(Val_Thumb));
    prev_ValThumb = Val_Thumb;
  }

  if (abs(prev_ValIndex - Val_Index) > 15) {
    Serial.println("Index:" + String(Val_Index));
    prev_ValIndex = Val_Index;
  }

  if (abs(prev_ValMiddle - Val_Middle) > 15) {
    Serial.println("Middle:" + String(Val_Middle));
    prev_ValMiddle = Val_Middle;
  }

  if (abs(prev_ValRing - Val_Ring) > 15) {
    Serial.println("Ring:" + String(Val_Ring));
    prev_ValRing = Val_Ring;
  }

  if (abs(prev_ValPinky - Val_Pinky) > 15) {
    Serial.println("Pinky:" + String(Val_Pinky));
    prev_ValPinky = Val_Pinky;
  }
}
