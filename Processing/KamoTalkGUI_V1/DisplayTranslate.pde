
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
  if (!DisplayTranslate_init) {
    DisplayTranslate_setup();
  }

  fill(#ffffff);
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
  fill(#000000);
  rect(995, 120, 200, 500);

  fill(#ff0000);
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

  if (mySerialPort.available()>0) {
    MSerialPort_Val=mySerialPort.read();
    currentGesture=char(MSerialPort_Val);
    if (currentGesture==previousGesture) {
      fill(#00ff00);
      textSize(100);
      textAlign(CENTER, TOP);
      text(currentGesture, 1100, 190);
      GestureCount++;
      if (!AddedToSentence && GestureCount>=15) {
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
      } else if (currentGesture>='@' && !HasSpoken) {
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
    if (NoSerialCount>=3) {
      HasSpoken=false;
    }
  }

  fill(#ff0000);
  textSize(20);
  text(GestureCount, 1100, 150);

  //fill(#ffffff);
  //textAlign(CENTER, TOP);
  //text(NoSerialCount, 1100, 170);
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
