//KamoTalk V1.0.0 //<>//

import guru.ttslib.*;
import processing.serial.*;

PFont Font_Default_Regular;
PFont Font_Default_Bold;

color Color_BLACK= color(0, 0, 0);
color Color_RED= color(255, 0, 0);
color Color_GREEN= color(0, 255, 0);
color Color_BLUE=color(0, 0, 255);
color Color_WHITE= color(255, 255, 255);
color Color_CYAN= color(0, 255, 255);
color Color_MAGENTA= color(255, 0, 255);
color Color_YELLOW= color(255, 255, 0);
color Color_ORANGE=color(255, 128, 0);
color Color_GRAY=color(128, 128, 128);

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

String [] savedHandsignWord = new String[31];
String [] savedHandsignWordDisplay = new String[31];

Table handsignData;

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

  handsignData = loadTable("handsign/handsign.csv", "header");

  handsignData.setString(1, "pw", "8899");
  saveTable(handsignData, "handsign/handsign.csv");

  LoadSavedFile();
}


void draw() {

  switch(currentScreen) {
  case 0x0000:
    DisplayHome();
    break;
  case 0x1000:
    DisplayTranslate();
    break;
  case 0x1100:
    DisplayTutorial();
    break;
  case 0x2000:
    DisplayAddgesture();
    break;
  case 0x3000:
    DisplaySettings();
    break;
  default:
    DisplayHome();
    break;
  }


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
  if (ButtonHovered(TRANSLATE) && currentScreen==0) {
    //tts.speak("TRANSLATE");
    DisplayHome_init=false;
    currentScreen=0x1000;
  } else if (ButtonHovered(ADD_GESTURE) && currentScreen==0) {
    //tts.speak("ADD GESTURE");
    DisplayHome_init=false;
    currentScreen=0x2000;
    ch_currentSlot='1';
  } else if (ButtonHovered(SETTINGS) && currentScreen==0) {
    //tts.speak("SETTINGS");
    DisplayHome_init=false;
    currentScreen=0x3000;
  } else {
    //tts.speak("NOTHING");
  }

  //Translate Screen
  if (currentScreen==0x1000) {
    DisplayTranslate_ButtonFunctions();
  }

  //Tutorial Screen
  if (currentScreen==0x1100) {
    DisplayTutorial_ButtonFuntions();
  }

  //Add HandSign Screen
  if (currentScreen==0x2000) {
    DisplayAddgesture_ButtonFunctions();
  }

  //Settings Screen
  if (currentScreen==0x3000) {
    //BackButton
    DisplaySettings_ButtonFunctions();
  }
}


void keyPressed() {

  if (currentScreen==0x3000) {
    if (key==BACKSPACE) {
      if (pwEntered.length()>0) {
        pwEntered=pwEntered.substring(0, pwEntered.length()-1);
      }
    } else {
      if (key>='0' && key<='9' && pwEntered.length()<4) {
        pwEntered=pwEntered+key;
      }
    }
  }


  if (currentScreen==0x2000) {
    println("f:"+int(key));
    if (key>='!' && key<='z' && currentlyDisplaying.length()<250) {
      currentToSave=currentToSave+key;
      if (currentlyDisplaying.length()==65 || currentlyDisplaying.length()==130 || currentlyDisplaying.length()==195) {
        currentlyDisplaying=currentlyDisplaying+"\n"+key;
      } else {
        currentlyDisplaying=currentlyDisplaying+key;
        println("word:"+currentlyDisplaying);
      }
    } else if (key==BACKSPACE) {
      if (currentlyDisplaying.length()>0) {
        currentlyDisplaying=currentlyDisplaying.substring(0, currentlyDisplaying.length()-1);
        currentToSave=currentToSave.substring(0, currentToSave.length()-1);
      }
    } else if (key==32) {
      if (currentlyDisplaying.length()==65 || currentlyDisplaying.length()==130 || currentlyDisplaying.length()==195) {
        currentlyDisplaying=currentlyDisplaying+"\n"+key;
      } else {
        currentlyDisplaying=currentlyDisplaying+ " ";
      }
      currentToSave=currentToSave+" ";
    }
  }
}


void LoadSavedFile() {
  for (int i=0; i<=30; i++) {
    savedHandsignWord[i]="";
    savedHandsignWordDisplay[i]="";
  }


  int a=1;
  for (TableRow row : handsignData.rows()) {
    int id = row.getInt("id");
    savedHandsignWord[a] = row.getString("word");
    savedHandsignWordDisplay[a] = row.getString("display");
    a++;
  }
}
