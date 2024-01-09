import guru.ttslib.*; //<>//

//KamoTalk V1.0.0

PFont Font_Default_Regular;
PFont Font_Default_Bold;

color Color_BLACK= color(0, 0, 0);
color Color_RED= color(255, 0, 0);
color Color_GREEN= color(0, 255, 0);
color Color_WHITE= color(255, 255, 255);
color Color_CYAN= color(0, 255, 255);
color Color_MAGENTA= color(255, 0, 255);
color Color_YELLOW= color(255, 255, 0);

final int csrX=0xABAB;
final int csrY=0xABAC;
final int csrA=0xABAD;
final int csrB=0xABAE;

final int TRANSLATE=0x0000;
final int ADD_GESTURE=0x0001;
final int SETTINGS=0x0002;

TTS tts;

void setup() {
  size(1200, 650);
  tts = new TTS();
  frameRate(60);
  background(#808080);

  Font_Default_Regular=createFont("OpenSansRegular.ttf", 48);
  Font_Default_Bold=createFont("OpenSansBold.ttf", 48);
}


void draw() {
  background(#808080);

  display_HOME();


  println(ButtonGetCursor(TRANSLATE, csrX));
  println(ButtonGetCursor(TRANSLATE, csrA));
  println(mouseX);
  println(ButtonHovered(TRANSLATE));
}

void mousePressed() {
  tts.speak("PRESSED ");
  if (ButtonHovered(TRANSLATE)) {
    tts.speak("TRANSLATE");
  } else if (ButtonHovered(ADD_GESTURE)) {
    tts.speak("ADD GESTURE");
  } else if (ButtonHovered(SETTINGS)) {
    tts.speak("SETTINGS");
  } else {
    tts.speak("NOTHING");
  }

  //tts.speak("Oi! Eu sou um esboço Processing falando");
}
