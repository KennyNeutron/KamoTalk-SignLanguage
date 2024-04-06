//KamoTalk V1.0.0 //<>//

import guru.ttslib.*;
import processing.serial.*;

PFont Font_Default_Regular;
PFont Font_Default_Bold;

color Color_BLACK= color(0, 0, 0);
color Color_RED= color(255, 0, 0);
color Color_GREEN= color(0, 255, 0);
color Color_WHITE= color(255, 255, 255);
color Color_CYAN= color(0, 255, 255);
color Color_MAGENTA= color(255, 0, 255);
color Color_YELLOW= color(255, 255, 0);

color ColorBG=color(#808080);

final int csrX=0xABAB;
final int csrY=0xABAC;
final int csrA=0xABAD;
final int csrB=0xABAE;

final int TRANSLATE=0x0000;
final int ADD_GESTURE=0x0001;
final int SETTINGS=0x0002;

TTS tts;

Serial mySerialPort;
int MSerialPort_Val;
String str_ToSpeak="st";

boolean str_ToSpeak_printed=false;

int currentScreen=0x0000;


void setup() {
  size(1200, 650);
  tts = new TTS();
  frameRate(60);
  background(#808080);

  Font_Default_Regular=createFont("OpenSansRegular.ttf", 48);
  Font_Default_Bold=createFont("OpenSansBold.ttf", 48);

  String portName = Serial.list()[0];
  mySerialPort = new Serial(this, "COM4", 9600);
  ColorBG=color(#808080);

  background(ColorBG);

  currentScreen=0x0000;
}


void draw() {

  switch(currentScreen) {
  case 0x0000:
    DisplayHome();
    break;
  case 0x1000:
    DisplayTranslate();
    break;
  case 0x3000:
    DisplaySettings();
    break;
  default:
    DisplayHome();
    break;
  }



  println(ButtonGetCursor(TRANSLATE, csrX));
  println(ButtonGetCursor(TRANSLATE, csrA));
  println(mouseX);
  println(ButtonHovered(TRANSLATE));


  //if (mySerialPort.available()>0) {
  //  str_ToSpeak_printed=false;
  //  str_ToSpeak="";
  //  MSerialPort_Val=mySerialPort.read();
  //  //println(str(MSerialPort_Val));
  //  //serialPrintOnScreen(str(MSerialPort_Val));
  //  if (MSerialPort_Val=='<') {
  //    while (MSerialPort_Val!='>') {
  //      while (mySerialPort.available()==0) ;
  //      MSerialPort_Val=mySerialPort.read();
  //      str_ToSpeak=str_ToSpeak+char(MSerialPort_Val);
  //    }
  //    if (!str_ToSpeak_printed) {
  //      str_ToSpeak_printed=true;
  //      tts.speak(str_ToSpeak);
  //    }
  //  }
  //}

  fill(#000000);
  strokeWeight(0);
  textFont(Font_Default_Regular, 30);
  textSize(15);
  textAlign(LEFT, TOP);
  text("SCREEN:"+hex(currentScreen), 0, 0);
}


void serialPrintOnScreen(String StrToPrint) {
  fill(#ffffff);
  strokeWeight(0);
  textFont(Font_Default_Bold, 30);
  textSize(20);
  textAlign(CENTER, CENTER);
  text(StrToPrint, 10, 10);
  //delay(500);
}


void mousePressed() {
  //tts.speak("PRESSED ");
  //tts.speak("The quick brown fox jumps over the lazy dog");
  if (ButtonHovered(TRANSLATE)) {
    //tts.speak("TRANSLATE");
    DisplayHome_init=false;
    currentScreen=0x1000;
  } else if (ButtonHovered(ADD_GESTURE)) {
    //tts.speak("ADD GESTURE");
  } else if (ButtonHovered(SETTINGS)) {
    //tts.speak("SETTINGS");
    DisplayHome_init=false;
    currentScreen=0x3000;
  } else {
    //tts.speak("NOTHING");
  }

  //Settings Screen
  if (currentScreen==0x3000) {
    //BackButton
    if (mouseX>25 && mouseX<175 && mouseY>25 && mouseY<75 ) {
      currentScreen=0x0000;
      DisplaySettings_init=false;
    }
  }

  if (currentScreen==0x1000) {
    //BackButton
    if (mouseX>25 && mouseX<175 && mouseY>25 && mouseY<75 ) {
      currentScreen=0x0000;
      DisplayTranslate_init=false;
    }
  }
  //tts.speak("Oi! Eu sou um esboço Processing falando");
}
