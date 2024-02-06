import processing.core.*; 
import processing.data.*; 
import processing.event.*; 
import processing.opengl.*; 

import guru.ttslib.*; 
import processing.serial.*; 

import java.util.HashMap; 
import java.util.ArrayList; 
import java.io.File; 
import java.io.BufferedReader; 
import java.io.PrintWriter; 
import java.io.InputStream; 
import java.io.OutputStream; 
import java.io.IOException; 

public class KamoTalkGUI_V1 extends PApplet {

//KamoTalk V1.0.0 //<>//




PFont Font_Default_Regular;
PFont Font_Default_Bold;

int Color_BLACK= color(0, 0, 0);
int Color_RED= color(255, 0, 0);
int Color_GREEN= color(0, 255, 0);
int Color_WHITE= color(255, 255, 255);
int Color_CYAN= color(0, 255, 255);
int Color_MAGENTA= color(255, 0, 255);
int Color_YELLOW= color(255, 255, 0);

int ColorBG=color(0xff808080);

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


public void setup() {
  
  tts = new TTS();
  frameRate(60);
  background(0xff808080);

  Font_Default_Regular=createFont("OpenSansRegular.ttf", 48);
  Font_Default_Bold=createFont("OpenSansBold.ttf", 48);

  String portName = Serial.list()[0];
  mySerialPort = new Serial(this, portName, 115200);
  ColorBG=color(0xff808080);

  background(ColorBG);
}


public void draw() {


  display_HOME();


  println(ButtonGetCursor(TRANSLATE, csrX));
  println(ButtonGetCursor(TRANSLATE, csrA));
  println(mouseX);
  println(ButtonHovered(TRANSLATE));


  if (mySerialPort.available()>0) {
    str_ToSpeak_printed=false;
    str_ToSpeak="";
    MSerialPort_Val=mySerialPort.read();
    //println(str(MSerialPort_Val));
    //serialPrintOnScreen(str(MSerialPort_Val));
    if (MSerialPort_Val=='<') {
      while (MSerialPort_Val!='>') {
        while (mySerialPort.available()==0) ;
        MSerialPort_Val=mySerialPort.read();
        str_ToSpeak=str_ToSpeak+PApplet.parseChar(MSerialPort_Val);
      }
      if (!str_ToSpeak_printed) {
        str_ToSpeak_printed=true;
        tts.speak(str_ToSpeak);
      }
    }
  }
}


public void serialPrintOnScreen(String StrToPrint) {
  fill(0xffffffff);
  strokeWeight(0);
  textFont(Font_Default_Bold, 30);
  textSize(20);
  textAlign(CENTER, CENTER);
  text(StrToPrint, 10, 10);
  //delay(500);
}


public void mousePressed() {
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
//DISPLAY HOME
//Screen Address: 0x0000


boolean display_HOME_initialize=false;


public void display_HOME() {
  fill(0xffffffff);
  strokeWeight(0);
  textFont(Font_Default_Bold, 30);
  textSize(50);
  textAlign(CENTER, CENTER);
  text("KAMOTALK 2024", width/2, 30);


  PrintButton(TRANSLATE);

  PrintButton(ADD_GESTURE);


}


public void display_HOME_setup() {
  display_HOME_initialize=true;
}
//GUI Manager

public void CreateButton_Default(int cursorX, int cursorY, int colorBG, int colorSTK, String btn_text, PFont FontTXT, int colorTXT, int txtSIZE) {
  fill(colorBG);
  stroke(colorSTK);
  strokeWeight(3);
  rect(cursorX, cursorY, 300, 50, 15);
  fill(colorTXT);
  noStroke();
  textFont(FontTXT);
  textSize(txtSIZE);
  textAlign(CENTER, CENTER);
  text(btn_text, cursorX+150, cursorY+20);
}


public void CreateButton_Large(int cursorX, int cursorY, int colorBG, int colorSTK, String btn_text, PFont FontTXT, int colorTXT, int txtSIZE) {
  fill(colorBG);
  stroke(colorSTK);
  strokeWeight(3);
  rect(cursorX, cursorY, 600, 100, 15);
  fill(colorTXT);
  noStroke();
  textFont(FontTXT);
  textSize(txtSIZE);
  textAlign(CENTER, CENTER);
  text(btn_text, cursorX+300, cursorY+50);
}


public void PrintButton(int buttonAddress) {
  switch(buttonAddress) {
  case TRANSLATE:
    if (!ButtonHovered(TRANSLATE)) {
      CreateButton_Large((width/2)-300, 150, Color_GREEN, Color_BLACK, "TRANSLATE", Font_Default_Bold, Color_BLACK, 40);
    } else {
      CreateButton_Large((width/2)-300, 150, Color_YELLOW, Color_BLACK, "TRANSLATE", Font_Default_Bold, Color_BLACK, 40);
    }

    break;

  case ADD_GESTURE:
    if (!ButtonHovered(ADD_GESTURE)) {
      CreateButton_Large((width/2)-300, 300, Color_GREEN, Color_BLACK, "ADD GESTURE", Font_Default_Bold, Color_BLACK, 40);
    } else {
      CreateButton_Large((width/2)-300, 300, Color_YELLOW, Color_BLACK, "ADD GESTURE", Font_Default_Bold, Color_BLACK, 40);
    }

  case SETTINGS:
    if (!ButtonHovered(SETTINGS)) {
      CreateButton_Large((width/2)-300, 450, Color_GREEN, Color_BLACK, "SETTINGS", Font_Default_Bold, Color_BLACK, 40);
    } else {
      CreateButton_Large((width/2)-300, 450, Color_YELLOW, Color_BLACK, "SETTINGS", Font_Default_Bold, Color_BLACK, 40);
    }

    break;
  }
}


public boolean ButtonHovered(int buttonAddress) {
  switch(buttonAddress) {
  case TRANSLATE:
    if (mouseX>ButtonGetCursor(TRANSLATE, csrX) && mouseX<ButtonGetCursor(TRANSLATE, csrA) && mouseY>ButtonGetCursor(TRANSLATE, csrY) && mouseY<ButtonGetCursor(TRANSLATE, csrB)) {
      return true;
    } else {
      return false;
    }

  case ADD_GESTURE:
    if (mouseX>ButtonGetCursor(ADD_GESTURE, csrX) && mouseX<ButtonGetCursor(ADD_GESTURE, csrA) && mouseY>ButtonGetCursor(ADD_GESTURE, csrY) && mouseY<ButtonGetCursor(ADD_GESTURE, csrB)) {
      return true;
    } else {
      return false;
    }

  case SETTINGS:
    if (mouseX>ButtonGetCursor(SETTINGS, csrX) && mouseX<ButtonGetCursor(SETTINGS, csrA) && mouseY>ButtonGetCursor(SETTINGS, csrY) && mouseY<ButtonGetCursor(SETTINGS, csrB)) {
      return true;
    } else {
      return false;
    }
}

  return false;
}

public int ButtonGetCursor(int buttonAddress, int cursor) {

  switch(buttonAddress) {

  case TRANSLATE:
    switch(cursor) {
    case csrX:
      return ((width/2)-300);
    case csrY:
      return 150;
    case csrA:
      return ((width/2)+300);
    case csrB:
      return 150+100;
    default:
      return 0;
    }

  case ADD_GESTURE:
    switch(cursor) {
    case csrX:
      return ((width/2)-300);
    case csrY:
      return 300;
    case csrA:
      return ((width/2)+300);
    case csrB:
      return 300+100;
    default:
      return 0;
    }

  case SETTINGS:
    switch(cursor) {
    case csrX:
      return ((width/2)-300);
    case csrY:
      return 450;
    case csrA:
      return ((width/2)+300);
    case csrB:
      return 450+100;
    default:
      return 0;
    }
  }

  return 0;
}
  public void settings() {  size(1200, 650); }
  static public void main(String[] passedArgs) {
    String[] appletArgs = new String[] { "KamoTalkGUI_V1" };
    if (passedArgs != null) {
      PApplet.main(concat(appletArgs, passedArgs));
    } else {
      PApplet.main(appletArgs);
    }
  }
}
