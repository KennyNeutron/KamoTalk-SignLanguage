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

int ThumbByte = 0;
int IndexByte = 0;
int MiddleByte = 0;
int RingByte = 0;
int PinkyByte = 0;

#define pad_thumb 7
#define pad_index 5
#define pad_middle 4
#define pad_ring 3
#define pad_pinky 2


bool thumb_to_index = false;
bool thumb_to_middle = false;
bool thumb_to_ring = false;
bool thumb_to_pinky = false;

int UnitTolerance = 40;
float GyroTolerance = 30.00;

float KamoTalk_GyroX = 0.00;
float KamoTalk_GyroY = 0.00;
float KamoTalk_GyroZ = 0.00;

char NowSigning = ' ';
char Prev_NowSigning = ' ';

uint8_t GestureCount = 0;
bool GestureAccepted = false;

bool SignPrinted = false;

byte SignScore=0;

String WordToSay = "";
bool HasSpoken = true;


//EEPROM
uint8_t saved_command=-0;
float saved_Gx = 0.00;
float saved_Gy=0.00;
float saved_Gz=0.00;

uint16_t saved_fThumb=0;
uint16_t saved_fIndex=0;
uint16_t saved_fMiddle=0;
uint16_t saved_fRing=0;
uint16_t saved_fPinky=0;

uint8_t saved_pThumb=0;
uint8_t saved_pIndex=0;
uint8_t saved_pMiddle=0;
uint8_t saved_pRing=0;
uint8_t saved_pPinky=0;

String defaultPassword="6789";
