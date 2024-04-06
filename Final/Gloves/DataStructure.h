//Communication Data Structure
// Max size of this struct is 32 bytes - NRF24L01 buffer limit

struct PayloadData {
  int kt_GyroX=0;
  int kt_GyroY=0;
  int kt_GyroZ=0;
  
  int adc_Thumb = 0;
  int adc_Index = 0;
  int adc_Middle = 0;
  int adc_Ring = 0;
  int adc_Pinky = 0;

  uint8_t byteThumb=0xff;
  uint8_t byteIndex=0xff;
  uint8_t byteMiddle=0xff;
  uint8_t byteRing=0xff;
  uint8_t bytePinky=0xff;

};

PayloadData payload;
