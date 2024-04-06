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

#define pad_thumb 7
#define pad_index 5
#define pad_middle 4
#define pad_ring 3
#define pad_pinky 2


bool thumb_to_index = false;
bool thumb_to_middle = false;
bool thumb_to_ring = false;
bool thumb_to_pinky = false;

int UnitTolerance = 30;

float GyroTolerance=30.0;

int KamoTalk_GyroX=0;
int KamoTalk_GyroY=0;
int KamoTalk_GyroZ=0;
