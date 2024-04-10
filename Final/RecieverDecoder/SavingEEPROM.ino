

void saveEEPROM(uint8_t toSave, uint8_t command, float gyroX, float gyroY, float gyroZ, uint16_t fThumb, uint16_t fIndex, uint16_t fMiddle, uint16_t fRing, uint16_t fPinky, uint8_t pThumb, uint8_t pIndex, uint8_t pMiddle, uint8_t pRing, uint8_t pPinky) {
  int addressStart = 1;
  addressStart = 1 + (28 * (toSave - 1));
  EEPROM.write(addressStart, command);
  EEPROM.put(addressStart + 1, gyroX);
  EEPROM.put(addressStart + 5, gyroY);
  EEPROM.put(addressStart + 9, gyroZ);

  EEPROM.put(addressStart + 13, fThumb);
  EEPROM.put(addressStart + 15, fIndex);
  EEPROM.put(addressStart + 17, fMiddle);
  EEPROM.put(addressStart + 19, fRing);
  EEPROM.put(addressStart + 21, fPinky);

  EEPROM.write(addressStart + 23, pThumb);
  EEPROM.write(addressStart + 24, pIndex);
  EEPROM.write(addressStart + 25, pMiddle);
  EEPROM.write(addressStart + 26, pRing);
  EEPROM.write(addressStart + 27, pPinky);

  delay(100);

}

void getEEPROM(uint8_t slot) {
  int addressStart = 1;
  addressStart = 1 + (28 * (slot - 1));
  saved_command = EEPROM.read(addressStart);
  EEPROM.get(addressStart + 1, saved_Gx);
  EEPROM.get(addressStart + 5, saved_Gy);
  EEPROM.get(addressStart + 9, saved_Gz);

  EEPROM.get(addressStart + 13, saved_fThumb);
  EEPROM.get(addressStart + 15, saved_fIndex);
  EEPROM.get(addressStart + 17, saved_fMiddle);
  EEPROM.get(addressStart + 19, saved_fRing);
  EEPROM.get(addressStart + 21, saved_fPinky);

  saved_pThumb = EEPROM.read(addressStart + 23 );
  saved_pIndex = EEPROM.read(addressStart + 24);
  saved_pMiddle = EEPROM.read(addressStart + 25);
  saved_pRing = EEPROM.read(addressStart + 26);
  saved_pPinky = EEPROM.read(addressStart + 27);
  //
  //  Serial.println("EEPROM cmd:" + String(saved_command));
  //  Serial.println("EEPROM Gyro:" + String(saved_Gx) + "," + String(saved_Gy) + "," + String(saved_Gz));
  //  Serial.println("EEPROM Flex:" + String(saved_fThumb) + "," + String(saved_fIndex) + "," + String(saved_fMiddle) + "," + String(saved_fRing) + "," + String(saved_fPinky));
  //  Serial.println("EEPROM Pads::" + String(saved_pThumb) + "," + String(saved_pIndex) + "," + String(saved_pMiddle) + "," + String(saved_pRing) + "," + String(saved_pPinky));
}
