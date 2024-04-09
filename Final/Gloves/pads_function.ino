uint8_t ThumbByte() {
  pinMode(pad_thumb, OUTPUT);
  pinMode(pad_index, INPUT);
  pinMode(pad_middle, INPUT);
  pinMode(pad_ring, INPUT);
  pinMode(pad_pinky, INPUT);

  digitalWrite(pad_thumb, 1);
  delay(10);

  uint8_t Thumb_byte = 0;

  bitWrite(Thumb_byte, 0, digitalRead(pad_index));
  bitWrite(Thumb_byte, 1, digitalRead(pad_middle));
  bitWrite(Thumb_byte, 2, digitalRead(pad_ring));
  bitWrite(Thumb_byte, 3, digitalRead(pad_pinky));


  //  Serial.print("Thumb:");
  //  Serial.println(Thumb_byte, BIN);

  DDRD = B00000010;
  delay(10);
  return Thumb_byte;
}


uint8_t IndexByte() {
  pinMode(pad_thumb, INPUT);
  pinMode(pad_index, OUTPUT);
  pinMode(pad_middle, INPUT);
  pinMode(pad_ring, INPUT);
  pinMode(pad_pinky, INPUT);

  digitalWrite(pad_index, 1);
  delay(10);

  uint8_t Index_byte = 0;

  bitWrite(Index_byte, 0, digitalRead(pad_thumb));
  bitWrite(Index_byte, 1, digitalRead(pad_middle));
  bitWrite(Index_byte, 2, digitalRead(pad_ring));
  bitWrite(Index_byte, 3, digitalRead(pad_pinky));

  DDRD = B00000010;
  delay(10);
  return Index_byte;
}

uint8_t MiddleByte() {
  pinMode(pad_thumb, INPUT);
  pinMode(pad_index, INPUT);
  pinMode(pad_middle, OUTPUT);
  pinMode(pad_ring, INPUT);
  pinMode(pad_pinky, INPUT);

  digitalWrite(pad_middle, 1);
  delay(10);

  uint8_t Middle_byte = 0;

  bitWrite(Middle_byte, 0, digitalRead(pad_thumb));
  bitWrite(Middle_byte, 1, digitalRead(pad_index));
  bitWrite(Middle_byte, 2, digitalRead(pad_ring));
  bitWrite(Middle_byte, 3, digitalRead(pad_pinky));

  DDRD = B00000010;
  delay(10);
  return Middle_byte;
}

uint8_t RingByte() {
  pinMode(pad_thumb, INPUT);
  pinMode(pad_index, INPUT);
  pinMode(pad_middle, INPUT);
  pinMode(pad_ring, OUTPUT);
  pinMode(pad_pinky, INPUT);

  digitalWrite(pad_ring, 1);
  delay(10);

  uint8_t Ring_byte = 0;

  bitWrite(Ring_byte, 0, digitalRead(pad_thumb));
  bitWrite(Ring_byte, 1, digitalRead(pad_index));
  bitWrite(Ring_byte, 2, digitalRead(pad_middle));
  bitWrite(Ring_byte, 3, digitalRead(pad_pinky));

  DDRD = B00000010;
  delay(10);
  return Ring_byte;
}

uint8_t PinkyByte() {
  pinMode(pad_thumb, INPUT);
  pinMode(pad_index, INPUT);
  pinMode(pad_middle, INPUT);
  pinMode(pad_ring, INPUT);
  pinMode(pad_pinky, OUTPUT);

  digitalWrite(pad_pinky, 1);
  delay(10);

  uint8_t Pinky_byte = 0;

  bitWrite(Pinky_byte, 0, digitalRead(pad_thumb));
  bitWrite(Pinky_byte, 1, digitalRead(pad_index));
  bitWrite(Pinky_byte, 2, digitalRead(pad_middle));
  bitWrite(Pinky_byte, 3, digitalRead(pad_ring));

  DDRD = B00000010;
  delay(10);
  return Pinky_byte;
}
