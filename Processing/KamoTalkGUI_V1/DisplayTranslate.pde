
boolean DisplayTranslate_init=false;

char currentGesture;
char previousGesture;

int GestureCount=0;
int NoSerialCount=0;

String Sentence="";

boolean AddedToSentence=false;

boolean HasSpoken=false;

boolean Space=false;



void DisplayTranslate() {
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
    fill(#00ff00);
  } else {
    fill(#0000ff);
  }
  textSize(30);
  textAlign(LEFT, TOP);
  text(Sentence, 100, 120);


  if (GestureCount>0 || currentGesture=='@') {      
    fill(#00ff00);
    textSize(100);
    textAlign(CENTER, TOP);
    text(currentGesture, 1100, 190);
  }

  if (mySerialPort.available()>0) {
    MSerialPort_Val=mySerialPort.read();
    currentGesture=char(MSerialPort_Val);
    if (currentGesture==previousGesture) {
      GestureCount++;
      if (!AddedToSentence && GestureCount>=6) {
        if (currentGesture=='&') {
          Space=!Space;
          currentGesture=' ';
        }
        Sentence=Sentence+str(currentGesture);
        AddedToSentence=true;
      }
    } else {
      if (currentGesture>='A' && currentGesture<='Z') {
        previousGesture=currentGesture;
      } else if (currentGesture=='&') {
        previousGesture=currentGesture;
      } else if (currentGesture=='@' && !HasSpoken) {
        fill(#00ff00);
        textSize(20);
        textAlign(CENTER, TOP);
        text("TALK", 1100, 190);
        tts.speak(Sentence);
        HasSpoken=true;
      }


      GestureCount=0;
      AddedToSentence=false;
    }
    NoSerialCount=0;
  } else {
    NoSerialCount++;
    if (NoSerialCount>=5) {
      HasSpoken=false;
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
}
