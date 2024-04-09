uint8_t ThumbByte() {
  pinMode(pad_thumb, OUTPUT);
  pinMode(pad_index, INPUT_PULLUP);
  pinMode(pad_middle, INPUT_PULLUP);
  pinMode(pad_ring, INPUT_PULLUP);
  pinMode(pad_pinky, INPUT_PULLUP);

  digitalWrite(pad_thumb, 0);
  delayMicroseconds(100);

  uint8_t Thumb_byte = 0xff;

  bitWrite(Thumb_byte, 0, digitalRead(pad_index));
  bitWrite(Thumb_byte, 1, digitalRead(pad_middle));
  bitWrite(Thumb_byte, 2, digitalRead(pad_ring));
  bitWrite(Thumb_byte, 3, digitalRead(pad_pinky));


  //  Serial.print("Thumb:");
  //  Serial.println(Thumb_byte, BIN);

  DDRD = B00000010;
  return Thumb_byte;
}

uint8_t IndexByte() {
  pinMode(pad_thumb, INPUT_PULLUP);
  pinMode(pad_index, OUTPUT);
  pinMode(pad_middle, INPUT_PULLUP);
  pinMode(pad_ring, INPUT_PULLUP);
  pinMode(pad_pinky, INPUT_PULLUP);

  digitalWrite(pad_index, 0);
  delayMicroseconds(100);

  uint8_t Index_byte = 0xff;

  bitWrite(Index_byte, 0, digitalRead(pad_thumb));
  bitWrite(Index_byte, 1, digitalRead(pad_middle));
  bitWrite(Index_byte, 2, digitalRead(pad_ring));
  bitWrite(Index_byte, 3, digitalRead(pad_pinky));


  //  Serial.print("Index:");
  //  Serial.println(Index_byte, BIN);

  DDRD = B00000010;

  return Index_byte;
}

uint8_t MiddleByte() {
  pinMode(pad_thumb, INPUT_PULLUP);
  pinMode(pad_index, INPUT_PULLUP);
  pinMode(pad_middle, OUTPUT);
  pinMode(pad_ring, INPUT_PULLUP);
  pinMode(pad_pinky, INPUT_PULLUP);

  digitalWrite(pad_middle, 0);
  delayMicroseconds(100);

  uint8_t Middle_byte = 0xff;

  bitWrite(Middle_byte, 0, digitalRead(pad_thumb));
  bitWrite(Middle_byte, 1, digitalRead(pad_index));
  bitWrite(Middle_byte, 2, digitalRead(pad_ring));
  bitWrite(Middle_byte, 3, digitalRead(pad_pinky));


  //  Serial.print("Middle:");
  //  Serial.println(Middle_byte, BIN);

  DDRD = B00000010;

  return Middle_byte;
}

uint8_t RingByte() {
  pinMode(pad_thumb, INPUT_PULLUP);
  pinMode(pad_index, INPUT_PULLUP);
  pinMode(pad_middle, INPUT_PULLUP);
  pinMode(pad_ring, OUTPUT);
  pinMode(pad_pinky, INPUT_PULLUP);

  digitalWrite(pad_ring, 0);
  delayMicroseconds(100);

  uint8_t Ring_byte = 0xff;

  bitWrite(Ring_byte, 0, digitalRead(pad_thumb));
  bitWrite(Ring_byte, 1, digitalRead(pad_index));
  bitWrite(Ring_byte, 2, digitalRead(pad_middle));
  bitWrite(Ring_byte, 3, digitalRead(pad_pinky));


  //  Serial.print("Middle:");
  //  Serial.println(Middle_byte, BIN);

  DDRD = B00000010;

  return Ring_byte;
}
