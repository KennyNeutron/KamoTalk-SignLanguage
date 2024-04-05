uint8_t ThumbByte() {
  pinMode(pad_thumb, OUTPUT);
  pinMode(pad_index, INPUT_PULLUP);
  pinMode(pad_middle, INPUT_PULLUP);
  pinMode(pad_ring, INPUT_PULLUP);
  pinMode(pad_pinky, INPUT_PULLUP);
  digitalWrite(pad_thumb, 0);
  delayMicroseconds(10);

  uint8_t Thumb_byte=0xFF;

  bitWrite(Thumb_byte,0,digitalRead(pad_index));
  bitWrite(Thumb_byte,1,digitalRead(pad_middle));
  bitWrite(Thumb_byte,2,digitalRead(pad_ring));
  bitWrite(Thumb_byte,3,digitalRead(pad_pinky));

  return Thumb_byte;
}
