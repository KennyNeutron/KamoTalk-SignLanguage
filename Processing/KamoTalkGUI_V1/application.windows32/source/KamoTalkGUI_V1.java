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

//KamoTalk V1.0.0




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
int Color_ORANGE=color(255, 128, 0);
int Color_GRAY=color(128, 128, 128);

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

int currentScreen=0x0000;

String [] savedHandsignWord = new String[31];
String [] savedHandsignWordDisplay = new String[31];

Table handsignData;


public void setup() {
  
  tts = new TTS();
  frameRate(60);
  background(0xff808080);

  Font_Default_Regular=createFont("OpenSansRegular.ttf", 48);
  Font_Default_Bold=createFont("OpenSansBold.ttf", 48);

  //String portName = Serial.list()[0];
  //mySerialPort = new Serial(this, "COM4", 9600);
  ColorBG=color(0xff808080);

  background(ColorBG);

  currentScreen=0x0000;

  handsignData = loadTable("handsign/handsign.csv", "header");


  saveTable(handsignData, "handsign/handsign.csv");

  LoadSavedFile();
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

  //Screen Debugging
  //fill(#000000);
  //strokeWeight(0);
  //textFont(Font_Default_Regular, 30);
  //textSize(15);
  //textAlign(LEFT, TOP);
  //text("SCREEN:"+hex(currentScreen), 0, 0);
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
  //tts.speak("PRESSED ");
  //tts.speak("The quick brown fox jumps over the lazy dog");
  if (ButtonHovered(TRANSLATE) && currentScreen==0 &&pwMatch()) {
    //tts.speak("TRANSLATE");
    DisplayHome_init=false;
    currentScreen=0x1000;
  } else if (ButtonHovered(ADD_GESTURE) && currentScreen==0&&pwMatch()) {
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


  if (currentScreen==0x2000) {
    println("f:"+PApplet.parseInt(key));
    if (key>='!' && key<='z' && currentlyDisplaying.length()<100) {
      currentToSave=currentToSave+key;
      if (currentlyDisplaying.length()==30 || currentlyDisplaying.length()==60 || currentlyDisplaying.length()==90|| currentlyDisplaying.length()==120) {
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
      if (currentlyDisplaying.length()==30 || currentlyDisplaying.length()==60 || currentlyDisplaying.length()==90 || currentlyDisplaying.length()==120) {
        currentlyDisplaying=currentlyDisplaying+"\n"+key;
      } else {
        currentlyDisplaying=currentlyDisplaying+ " ";
      }
      currentToSave=currentToSave+" ";
    }
  }
}


public void LoadSavedFile() {
  for (int i=0; i<=30; i++) {
    savedHandsignWord[i]="";
    savedHandsignWordDisplay[i]="";
  }


  int a=1;
  for (TableRow row : handsignData.rows()) {
    int id = row.getInt("id");
    savedHandsignWord[a] = row.getString("word");
    savedHandsignWordDisplay[a] = row.getString("display");
    if (a==1) {
      dpw=row.getString("pw");
      currentCOM=row.getInt("comport");
    } else if (a==2) {
      pwEntered=row.getString("pw");
    }
    a++;
  }
}

boolean initCOMportINIT=false;
public void initCOMport() {
  if (!initCOMportINIT) {
    String comName="COM"+str(currentCOM);
    mySerialPort = new Serial(this, comName, 9600);
  }

  initCOMportINIT=true;
}

boolean DisplayAddgesture_init=false;
int currentSlot=1;

String currentlyDisplaying="";
String currentToSave="";
boolean SaveAllow=false;

int serialDetect=0;

char ch_currentSlot='1';

public void DisplayAddgesture() {
  if (!DisplayAddgesture_init) {
    DisplayAddgesture_setup();
  }

  background(ColorBG);

  fill(0);
  rect(200, 150, 800, 400);

  fill(0xffffffff);
  strokeWeight(0);
  textFont(Font_Default_Bold, 45);
  textSize(50);
  textAlign(CENTER, CENTER);
  text("Registered Hand Signs", width/2, 30);



  textFont(Font_Default_Regular, 45);
  textSize(30);
  textAlign(LEFT, TOP);
  text("Current Slot:", 200, 100);
  fill(Color_BLUE);
  textFont(Font_Default_Bold, 45);
  textSize(30);
  text("SLOT#"+(currentSlot), 380, 100);

  fill(Color_GREEN);
  textFont(Font_Default_Regular, 45);
  textSize(40);
  if (currentlyDisplaying.length()==0) {
    text("NONE", 230, 170);
  } else {
    text(currentlyDisplaying, 230, 170);
  }

  text(currentlyDisplaying.length()+"/100", 950, 100);

  if (mouseX>25 && mouseX<100 && mouseY>620 && mouseY<645) {
    CreateButton_XSmall(25, 620, Color_ORANGE, Color_BLACK, "TALK", Font_Default_Bold, Color_BLACK, 15);
  } else {  
    CreateButton_XSmall(25, 620, Color_YELLOW, Color_BLACK, "TALK", Font_Default_Bold, Color_BLACK, 15);
  }



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


  if (mouseX>430 && mouseX<580 && mouseY>580 && mouseY<630) {
    CreateButton_Small(430, 580, Color_ORANGE, Color_BLACK, "DELETE", Font_Default_Bold, Color_BLACK, 25);
  } else {
    CreateButton_Small(430, 580, Color_RED, Color_BLACK, "DELETE", Font_Default_Bold, Color_BLACK, 25);
  }


  if (!SaveAllow) {
    CreateButton_Small(620, 580, Color_GRAY, Color_BLACK, "Duplicate", Font_Default_Bold, Color_BLACK, 25);
  } else {
    if (mouseX>620 && mouseX<770 && mouseY>580 && mouseY<630) {
      CreateButton_Small(620, 580, Color_ORANGE, Color_BLACK, "SAVE", Font_Default_Bold, Color_BLACK, 25);
    } else {
      CreateButton_Small(620, 580, Color_GREEN, Color_BLACK, "SAVE", Font_Default_Bold, Color_BLACK, 25);
    }
  }



  //println(mySerialPort.available());
  if (mySerialPort.available()==0) {
    serialDetect++;
    if (serialDetect>=50) {
      SaveAllow=true;
      serialDetect=0;
    }
  } else {
    serialDetect=0;
    MSerialPort_Val=mySerialPort.read();
    SaveAllow=false;
  }
}



public void DisplayAddgesture_setup() {
  background(ColorBG);
  DisplayAddgesture_init=true;
  currentlyDisplaying="";
  currentToSave="";
  //println("init");
  currentlyDisplaying=savedHandsignWordDisplay[currentSlot];
  initCOMport();
}


public void DisplayAddgesture_ButtonFunctions() {
  //Back Button
  if (mouseX>25 && mouseX<175 && mouseY>25 && mouseY<75 ) {
    currentScreen=0x0000;
    DisplayAddgesture_init=false;
  }

  //Next Button
  if (mouseX>1020 && mouseX<1170 && mouseY>300 && mouseY<350) {
    if (currentSlot>=30) {
      currentSlot=1;
      ch_currentSlot='1';
    } else {
      currentSlot++;
      ch_currentSlot++;
    }
    DisplayAddgesture_init=false;
  }

  //Previous Button
  if (mouseX>30 && mouseX<180 && mouseY>300 && mouseY<350) {
    if (currentSlot<=1) {
      currentSlot=30;
      ch_currentSlot='N';
    } else {
      currentSlot--;
      ch_currentSlot--;
    }
    DisplayAddgesture_init=false;
  }

  //Talk Button
  if (mouseX>25 && mouseX<100 && mouseY>620 && mouseY<645) {
    tts.speak(savedHandsignWordDisplay[currentSlot]);
  }


  //DeleteButton
  if (mouseX>430 && mouseX<580 && mouseY>580 && mouseY<630) {

    handsignData.setString(currentSlot-1, "word", "");
    handsignData.setString(currentSlot-1, "display", "");
    saveTable(handsignData, "handsign/handsign.csv");
    println("deleted!");


    LoadSavedFile();

    String sToWrite="{"+ch_currentSlot+"}";
    println("{"+ch_currentSlot+"}");
    mySerialPort.write(sToWrite); 
    DisplayAddgesture_init=false;
  }

  //Save Button
  if (mouseX>620 && mouseX<770 && mouseY>580 && mouseY<630) {
    handsignData.setString(currentSlot-1, "word", currentToSave);
    handsignData.setString(currentSlot-1, "display", currentlyDisplaying);
    saveTable(handsignData, "handsign/handsign.csv");
    println("saved!");


    LoadSavedFile();
    String sToWrite="<"+ch_currentSlot+">";
    println("<"+ch_currentSlot+">");
    mySerialPort.write(sToWrite); 

    DisplayAddgesture_init=false;
  }
}

boolean DisplaySettings_init=false;

String pwEntered="";
int currentCOM=0;

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

  if (mouseX>365 && mouseX<440 && mouseY>160 && mouseY<185) {
    CreateButton_XSmall(365, 160, Color_YELLOW, Color_BLACK, "DELETE", Font_Default_Bold, Color_BLACK, 15);
  } else {
    CreateButton_XSmall(365, 160, Color_RED, Color_BLACK, "DELETE", Font_Default_Bold, Color_BLACK, 15);
  }

  if (mouseX>760 && mouseX<835 && mouseY>160 && mouseY<185) {
    CreateButton_XSmall(760, 160, Color_YELLOW, Color_BLACK, "ENTER", Font_Default_Bold, Color_BLACK, 15);
  } else {
    CreateButton_XSmall(760, 160, Color_GREEN, Color_BLACK, "ENTER", Font_Default_Bold, Color_BLACK, 15);
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



  strokeWeight(0);
  fill(Color_BLACK);
  rect(525, 350, 150, 50);

  fill(Color_BLACK);
  strokeWeight(0);
  textFont(Font_Default_Regular, 45);
  textSize(20);
  textAlign(CENTER, CENTER);
  text("SELECT COMPORT", width/2, 330);

  textSize(30);
  fill(Color_GREEN);
  text("COM"+str(currentCOM), width/2, 370);

  if (mouseX>440 && mouseX<515 && mouseY>360 && mouseY<385) {
    CreateButton_XSmall(440, 360, Color_YELLOW, Color_BLACK, "PREV", Font_Default_Bold, Color_BLACK, 15);
  } else {
    CreateButton_XSmall(440, 360, Color_CYAN, Color_BLACK, "PREV", Font_Default_Bold, Color_BLACK, 15);
  }

  if (mouseX>685 && mouseX<760 && mouseY>360 && mouseY<385) {
    CreateButton_XSmall(685, 360, Color_YELLOW, Color_BLACK, "NEXT", Font_Default_Bold, Color_BLACK, 15);
  } else {
    CreateButton_XSmall(685, 360, Color_CYAN, Color_BLACK, "NEXT", Font_Default_Bold, Color_BLACK, 15);
  }
}


public void DisplaySettings_setup() {
  background(ColorBG);

  DisplaySettings_init=true;
}

String dpw="";
public void DisplaySettings_ButtonFunctions() {
  //Back Button
  if (mouseX>25 && mouseX<175 && mouseY>25 && mouseY<75 ) {
    currentScreen=0x0000;
    DisplaySettings_init=false;
  }

  //Save Button
  if (mouseX>760 && mouseX<835 && mouseY>160 && mouseY<185) {
    handsignData.setString(1, "pw", pwEntered);
    saveTable(handsignData, "handsign/handsign.csv");
    LoadSavedFile();
  }

  //Delete Button
  if (mouseX>365 && mouseX<440 && mouseY>160 && mouseY<185) {
    handsignData.setString(1, "pw", "");
    saveTable(handsignData, "handsign/handsign.csv");
    pwEntered="";
    LoadSavedFile();
  }

  //Prev Button
  if (mouseX>440 && mouseX<515 && mouseY>360 && mouseY<385) {
    currentCOM--;
    if (currentCOM<0) {
      currentCOM=99;
    }
    handsignData.setInt(0, "comport", currentCOM);
    saveTable(handsignData, "handsign/handsign.csv");
    initCOMportINIT=false;
  }

  //Next Button
  if (mouseX>685 && mouseX<760 && mouseY>360 && mouseY<385) {
    currentCOM++;
    if (currentCOM>=99) {
      currentCOM=0;
    }
    handsignData.setInt(0, "comport", currentCOM);
    saveTable(handsignData, "handsign/handsign.csv");
    initCOMportINIT=false;
  }
}

public boolean pwMatch() {
  LoadSavedFile();
  if (dpw.equals(pwEntered)) {
    return true;
  } else {
    return false;
  }
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

boolean AllowTranslate=false;
int LastMillisTranslate=0;


public void DisplayTranslate() {
  if (millis()-LastMillisTranslate>3000) {
    AllowTranslate=true;
  }
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
  rect(995, 120, 200, 250);

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
  textSize(55);
  textAlign(LEFT, TOP);
  text(Sentence, 30, 120);


  if (GestureCount>0 || currentGesture=='@') {      
    fill(0xff00ff00);
    textSize(100);
    textAlign(CENTER, TOP);
    if (currentGesture>='[' && currentGesture<='z') {
      text("%", 1100, 190);
    } else {
      text(currentGesture, 1100, 190);
    }
  }

  if (mySerialPort.available()>0 && AllowTranslate) {
    MSerialPort_Val=mySerialPort.read();
    currentGesture=PApplet.parseChar(MSerialPort_Val);

    if (currentGesture==previousGesture) {
      GestureCount++;
      //println("Added to Sentence:"+AddedToSentence);
      if (!AddedToSentence && GestureCount>=8) {
          if (currentGesture=='#' && !HasSpoken) {
        fill(0xff00ff00);
        textSize(20);
        textAlign(CENTER, TOP);
        text("TALK", 1100, 190);
        tts.speak(Sentence);
        HasSpoken=true;
        AddedToSentence=true;
        GestureCount=0;
        previousGesture=30;
      }else if (currentGesture=='}') {
          Sentence="";
          AddedToSentence=true;
          GestureCount=0;
        } else if (currentGesture=='&') {
          Space=!Space;
          currentGesture=' ';
        } else if (currentGesture=='$') {
          if (Sentence.charAt(Sentence.length()-1)=='n') {
            Sentence=Sentence.substring(0, Sentence.length()-2);
            AddedToSentence=true;
            GestureCount=0;
            previousGesture=30;
          } else if (Sentence.charAt(Sentence.length()-1)==' ') {
            Space=!Space;
            Sentence=Sentence.substring(0, Sentence.length()-1);
            AddedToSentence=true;
            GestureCount=0;
          } else {
            Sentence=Sentence.substring(0, Sentence.length()-1);
            AddedToSentence=false;
            GestureCount=0;
            previousGesture=30;
          }
        }

        if (currentGesture>='[' &&currentGesture<='z' && !HasSpoken) {
          Sentence=savedHandsignWordDisplay[currentGesture-90];
          println("speak:"+str(currentGesture-90));
          tts.speak(savedHandsignWord[currentGesture-90]);
          HasSpoken=true;
          AddedToSentence=true;
        } else {
          if (Sentence.length()==26||Sentence.length()==52||Sentence.length()==78||Sentence.length()==104) {
            if (currentGesture!='$') {
              Sentence=Sentence+"\n"+str(currentGesture);
            }
          } else {
            if (currentGesture!='$' && currentGesture!='}' && currentGesture!='#' ) {
              Sentence=Sentence+str(currentGesture);
            }
          }
          AddedToSentence=true;
        }
      }
    } else {
      if (currentGesture>='!' && currentGesture<='z' && currentGesture!='#') {
        previousGesture=currentGesture;
      } else if (currentGesture<='}') {
        previousGesture=currentGesture;
      }
      GestureCount=0;
      AddedToSentence=false;
    }
    NoSerialCount=0;
  } else {
    NoSerialCount++;
    HasSpoken=false;
    if (NoSerialCount>=15) {
      HasSpoken=false;
      GestureCount=0;
    }
  }

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
  LoadSavedFile();
  AllowTranslate=false;
  LastMillisTranslate=millis();
}


public void DisplayTranslate_ButtonFunctions() {
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

  initCOMport();
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

  if (CurrentLetter>='A' && CurrentLetter<='Z') {
    img_name="letter"+CurrentLetter+".jpg";
  } else if (CurrentLetter>='0' && CurrentLetter<='9') {
    img_name="number"+CurrentLetter+".jpg";
  } else {
    img_name="letterA.jpg";
  }

  imageMode(CENTER);
  image(loadImage(img_name), width/2, 350);
}


public void DisplayTutorial_setup() {
  CurrentLetter='A';
  background(ColorBG);
  DisplayTutorial_init=true;
}



public void DisplayTutorial_ButtonFuntions() {
  //BackButton
  if (mouseX>25 && mouseX<175 && mouseY>25 && mouseY<75 ) {
    currentScreen=0x1000;
    DisplayTutorial_init=false;
  }

  //Next Button
  if (mouseX>1020 && mouseX<1170 && mouseY>300 && mouseY<350) {
    if (CurrentLetter=='Z') {
      CurrentLetter='0';
    } else if (CurrentLetter=='9') {
      CurrentLetter='A';
    } else {
      CurrentLetter++;
    }
  }

  //Previous Button
  if (mouseX>30 && mouseX<180 && mouseY>300 && mouseY<350) {
    if (CurrentLetter=='A') {
      CurrentLetter='9';
    } else if (      CurrentLetter=='0') {
      CurrentLetter='Z';
    } else {
      CurrentLetter--;
    }
  }
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
  textFont(Font_Default_Bold, 30);
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

public void CreateButton_XSmall(int cursorX, int cursorY, int colorBG, int colorSTK, String btn_text, PFont FontTXT, int colorTXT, int txtSIZE) {
  fill(colorBG);
  stroke(colorSTK);
  strokeWeight(1);
  rect(cursorX, cursorY, 75, 25, 6);
  fill(colorTXT);
  noStroke();
  textFont(FontTXT);
  textSize(txtSIZE);
  textAlign(CENTER, CENTER);
  text(btn_text, cursorX+38, cursorY+12);
}

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
    if (!pwMatch()) {
      CreateButton_Large((width/2)-300, 150, 0xffD3D3D3, Color_BLACK, "TRANSLATE", Font_Default_Bold, Color_BLACK, 40);
    } else {
      if (!ButtonHovered(TRANSLATE)) {
        CreateButton_Large((width/2)-300, 150, Color_GREEN, Color_BLACK, "TRANSLATE", Font_Default_Bold, Color_BLACK, 40);
      } else {
        CreateButton_Large((width/2)-300, 150, Color_YELLOW, Color_BLACK, "TRANSLATE", Font_Default_Bold, Color_BLACK, 40);
      }
    }
    break;

  case ADD_GESTURE:
    if (!pwMatch()) {
      CreateButton_Large((width/2)-300, 300, 0xffD3D3D3, Color_BLACK, "ADD HANDSIGN", Font_Default_Bold, Color_BLACK, 40);
    } else {
      if (!ButtonHovered(ADD_GESTURE)) {
        CreateButton_Large((width/2)-300, 300, Color_GREEN, Color_BLACK, "ADD HANDSIGN", Font_Default_Bold, Color_BLACK, 40);
      } else {
        CreateButton_Large((width/2)-300, 300, Color_YELLOW, Color_BLACK, "ADD HANDSIGN", Font_Default_Bold, Color_BLACK, 40);
      }
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
