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
int MiddleByte = 0;

#define pad_thumb 7
#define pad_index 5
#define pad_middle 4
#define pad_ring 3
#define pad_pinky 2


bool thumb_to_index = false;
bool thumb_to_middle = false;
bool thumb_to_ring = false;
bool thumb_to_pinky = false;

int UnitTolerance = 80;
float GyroTolerance = 20.00;

float KamoTalk_GyroX = 0.00;
float KamoTalk_GyroY = 0.00;
float KamoTalk_GyroZ = 0.00;

char NowSigning = ' ';
char Prev_NowSigning = ' ';

uint8_t GestureCount = 0;
bool GestureAccepted = false;

bool SignPrinted = false;



String WordToSay = "";
bool HasSpoken = true;
