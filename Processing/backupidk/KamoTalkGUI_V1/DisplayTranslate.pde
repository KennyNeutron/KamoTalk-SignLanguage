
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


void DisplayTranslate() {
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
    fill(#00ff00);
  } else {
    fill(#0000ff);
  }
  textSize(60);
  textAlign(LEFT, TOP);
  text(Sentence, 100, 120);


  if (GestureCount>0 || currentGesture=='@') {      
    fill(#00ff00);
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
    currentGesture=char(MSerialPort_Val);

    if (currentGesture==previousGesture) {
      GestureCount++;
      //println("Added to Sentence:"+AddedToSentence);
      if (!AddedToSentence && GestureCount>=8) {
          if (currentGesture=='#' && !HasSpoken) {
        fill(#00ff00);
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
          if (Sentence.length()==25||Sentence.length()==50||Sentence.length()==75||Sentence.length()==100) {
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

  fill(#ff0000);
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


void DisplayTranslate_setup() {
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


void DisplayTranslate_ButtonFunctions() {
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
