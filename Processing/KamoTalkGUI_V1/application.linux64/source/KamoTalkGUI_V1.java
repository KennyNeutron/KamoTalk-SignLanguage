import processing.core.*; 
import processing.data.*; 
import processing.event.*; 
import processing.opengl.*; 

import guru.ttslib.*; 

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


//import processing.serial.*;

PFont Font_Default_Regular;
PFont Font_Default_Bold;

int Color_BLACK= color(0, 0, 0);
int Color_RED= color(255, 0, 0);
int Color_GREEN= color(0, 255, 0);
int Color_BLUE=color(0, 0, 255);
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

//Serial mySerialPort;
int MSerialPort_Val;
String str_ToSpeak="st";

boolean str_ToSpeak_printed=false;

int currentScreen=0x0000;


public void setup() {
  
  tts = new TTS();
  frameRate(60);
  background(0xff808080);

  Font_Default_Regular=createFont("OpenSansRegular.ttf", 48);
  Font_Default_Bold=createFont("OpenSansBold.ttf", 48);

  //String portName = Serial.list()[0];
  //mySerialPort = new Serial(this, "/dev/ttyUSB0", 9600);
  ColorBG=color(0xff808080);

  background(ColorBG);

  currentScreen=0x0000;
}


public void draw() {

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
  case 0x3000:
    DisplaySettings();
    break;
  default:
    DisplayHome();
    break;
  }



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

  fill(0xff000000);
  strokeWeight(0);
  textFont(Font_Default_Regular, 30);
  textSize(15);
  textAlign(LEFT, TOP);
  text("SCREEN:"+hex(currentScreen), 0, 0);
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
  //tts.speak("The quick brown fox jumps over the lazy dog");
  if (ButtonHovered(TRANSLATE) && currentScreen==0) {
    //tts.speak("TRANSLATE");
    DisplayHome_init=false;
    currentScreen=0x1000;
  } else if (ButtonHovered(ADD_GESTURE) && currentScreen==0) {
    //tts.speak("ADD GESTURE");
  } else if (ButtonHovered(SETTINGS) && currentScreen==0) {
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

  //Translate Screen
  if (currentScreen==0x1000) {
    //BackButton
    if (mouseX>25 && mouseX<175 && mouseY>25 && mouseY<75 ) {
      currentScreen=0x0000;
      DisplayTranslate_init=false;
    }

    //Tutorial
    if (mouseX>=10 && mouseX<=110 && mouseY>=620 && mouseY<=650) {
      currentScreen=0x1100;
      DisplayTranslate_init=false;
    }
  }

  //Tutorial Screen
  if (currentScreen==0x1100) {
    //BackButton
    if (mouseX>25 && mouseX<175 && mouseY>25 && mouseY<75 ) {
      currentScreen=0x1000;
      DisplayTutorial_init=false;
    }

    //Next Button
    if (mouseX>1020 && mouseX<1170 && mouseY>300 && mouseY<350) {
      if (CurrentLetter=='Z') {
        CurrentLetter='A';
      } else {
        CurrentLetter++;
      }
    }

    //Previous Button
    if (mouseX>30 && mouseX<180 && mouseY>300 && mouseY<350) {
      if (CurrentLetter=='A') {
        CurrentLetter='Z';
      } else {
        CurrentLetter--;
      }
    }
  }
}


public void keyPressed() {

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
}

boolean DisplaySettings_init=false;

String pwEntered="";


public void DisplaySettings() {
  if (!DisplaySettings_init) {
    DisplaySettings_setup();
  }

  background(ColorBG);

  fill(0xffffffff);
  strokeWeight(0);
  textFont(Font_Default_Bold, 45);
  textSize(50);
  textAlign(CENTER, CENTER);
  text("SETTINGS", width/2, 30);


  if (mouseX>25 && mouseX<175 && mouseY>25 && mouseY<75 ) {
    CreateButton_Small(25, 25, Color_YELLOW, Color_BLACK, "BACK", Font_Default_Bold, Color_BLACK, 25);
  } else { 
    CreateButton_Small(25, 25, Color_CYAN, Color_BLACK, "BACK", Font_Default_Bold, Color_BLACK, 25);
  }

  fill(Color_BLACK);
  rect(450, 150, 300, 50);

  fill(Color_BLACK);
  strokeWeight(0);
  textFont(Font_Default_Regular, 45);
  textSize(20);
  textAlign(CENTER, CENTER);
  text("ENTER GLOVES PINCODE", width/2, 130);

  textSize(30);
  fill(Color_CYAN);
  text(pwEntered, width/2, 170);
}


public void DisplaySettings_setup() {
  background(ColorBG);





  DisplaySettings_init=true;
}


public void PrintButton_back() {
}

boolean DisplayTranslate_init=false;

char currentGesture;
char previousGesture;

int GestureCount=0;
int NoSerialCount=0;

String Sentence="";

boolean AddedToSentence=false;

boolean HasSpoken=false;

boolean Space=false;



public void DisplayTranslate() {
  background(ColorBG);

  if (!DisplayTranslate_init) {
    DisplayTranslate_setup();
  }


  fill(Color_WHITE);
  strokeWeight(0);
  textFont(Font_Default_Bold, 45);
  textSize(50);
  textAlign(CENTER, CENTER);
  text("TRANSLATE", width/2, 30);


  if (mouseX>25 && mouseX<175 && mouseY>25 && mouseY<75 ) {
    CreateButton_Small(25, 25, Color_YELLOW, Color_BLACK, "BACK", Font_Default_Bold, Color_BLACK, 25);
  } else { 
    CreateButton_Small(25, 25, Color_CYAN, Color_BLACK, "BACK", Font_Default_Bold, Color_BLACK, 25);
  }

  //DrawTerminal
  fill(Color_BLACK);
  rect(995, 120, 200, 500);

  fill(Color_RED);
  strokeWeight(0);
  textFont(Font_Default_Regular, 45);
  textSize(15);
  textAlign(CENTER, TOP);
  text("TERMINAL", 1100, 120);
  if (!Space) {
    fill(0xff00ff00);
  } else {
    fill(0xff0000ff);
  }
  textSize(30);
  textAlign(LEFT, TOP);
  text(Sentence, 100, 120);


  if (GestureCount>0) {      
    fill(0xff00ff00);
    textSize(100);
    textAlign(CENTER, TOP);
    text(currentGesture, 1100, 190);
  }

//  if (mySerialPort.available()>0) {
//    MSerialPort_Val=mySerialPort.read();
//    currentGesture=char(MSerialPort_Val);
//    if (currentGesture==previousGesture) {
//      GestureCount++;
//      if (!AddedToSentence && GestureCount>=9) {
//        if (currentGesture=='&') {
//          Space=!Space;
//          currentGesture=' ';
//        }
//        Sentence=Sentence+str(currentGesture);
//        AddedToSentence=true;
//      }
//    } else {
//      if (currentGesture>='A' && currentGesture<='Z') {
//        previousGesture=currentGesture;
//      } else if (currentGesture=='&') {
//        previousGesture=currentGesture;
//      } else if (currentGesture>='@' && !HasSpoken) {
//        fill(#00ff00);
//        textSize(20);
//        textAlign(CENTER, TOP);
//        text("TALK", 1100, 190);
//        tts.speak(Sentence);
//        HasSpoken=true;
//      }


//      GestureCount=0;
//      AddedToSentence=false;
//    }
//    NoSerialCount=0;
//  } else {
//    NoSerialCount++;
//    if (NoSerialCount>=3) {
//      HasSpoken=false;
//    }
//  }

  fill(0xffff0000);
  textSize(20);
  text(GestureCount, 1100, 150);

  //fill(#ffffff);
  //textAlign(CENTER, TOP);
  //text(NoSerialCount, 1100, 170);

  //fill(0);
  //rect(10, 620, 100, 30);
  if (mouseX>=10 && mouseX<=110 && mouseY>=620 && mouseY<=650) {
    fill(Color_YELLOW);
  } else {
    fill(Color_BLUE);
  }
  strokeWeight(0);
  textFont(Font_Default_Regular, 45);
  textSize(20);
  textAlign(LEFT, TOP);
  text("TUTORIAL", 10, 620);

  strokeWeight(3);
  line(width/2, width/2, 30, 645);
  rect(10, 645, 95, 3);
}


public void DisplayTranslate_setup() {
  background(ColorBG);
  DisplayTranslate_init=true;

  GestureCount=0;
  NoSerialCount=0;

  Sentence="";

  AddedToSentence=false;

  HasSpoken=false;

  Space=false;
}

boolean DisplayTutorial_init=false;


String img_name;
char CurrentLetter='A';
PImage CurrentImage;


public void DisplayTutorial() {
  background(ColorBG);
  if (!DisplayTutorial_init) {
    DisplayTutorial_setup();
  }

  fill(Color_WHITE);
  strokeWeight(0);
  textFont(Font_Default_Bold, 45);
  textSize(50);
  textAlign(CENTER, CENTER);
  text("TUTORIAL", width/2, 30);

  if (mouseX>25 && mouseX<175 && mouseY>25 && mouseY<75 ) {
    CreateButton_Small(25, 25, Color_YELLOW, Color_BLACK, "BACK", Font_Default_Bold, Color_BLACK, 25);
  } else { 
    CreateButton_Small(25, 25, Color_CYAN, Color_BLACK, "BACK", Font_Default_Bold, Color_BLACK, 25);
  }

  if (mouseX>1020 && mouseX<1170 && mouseY>300 && mouseY<350) {
    CreateButton_Small(1020, 300, Color_YELLOW, Color_BLACK, "NEXT", Font_Default_Bold, Color_BLACK, 25);
  } else {
    CreateButton_Small(1020, 300, Color_CYAN, Color_BLACK, "NEXT", Font_Default_Bold, Color_BLACK, 25);
  }

  if (mouseX>30 && mouseX<180 && mouseY>300 && mouseY<350) {
    CreateButton_Small(30, 300, Color_YELLOW, Color_BLACK, "PREVIOUS", Font_Default_Bold, Color_BLACK, 25);
  } else {
    CreateButton_Small(30, 300, Color_CYAN, Color_BLACK, "PREVIOUS", Font_Default_Bold, Color_BLACK, 25);
  }


  img_name="letter"+CurrentLetter+".jpg";

  imageMode(CENTER);
  image(loadImage(img_name), width/2, 300);
}


public void DisplayTutorial_setup() {
  CurrentLetter='A';
  background(ColorBG);
  DisplayTutorial_init=true;
}
//DISPLAY HOME
//Screen Address: 0x0000


boolean DisplayHome_init=false;


public void DisplayHome() {
  background(ColorBG);
  if (!DisplayHome_init) {
    DisplayHome_Setup();
  }
  fill(0xff000000);
  strokeWeight(0);
  textFont(Font_Default_Regular, 30);
  textSize(50);
  textAlign(CENTER, CENTER);
  text("KAMOTALK 2024", width/2, 30);

  PrintButton(TRANSLATE);

  PrintButton(ADD_GESTURE);
}


public void DisplayHome_Setup() {
  background(ColorBG);
  DisplayHome_init=true;
}
//GUI Manager

public void CreateButton_Small(int cursorX, int cursorY, int colorBG, int colorSTK, String btn_text, PFont FontTXT, int colorTXT, int txtSIZE) {
  fill(colorBG);
  stroke(colorSTK);
  strokeWeight(3);
  rect(cursorX, cursorY, 150, 50, 15);
  fill(colorTXT);
  noStroke();
  textFont(FontTXT);
  textSize(txtSIZE);
  textAlign(CENTER, CENTER);
  text(btn_text, cursorX+75, cursorY+20);
}

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
