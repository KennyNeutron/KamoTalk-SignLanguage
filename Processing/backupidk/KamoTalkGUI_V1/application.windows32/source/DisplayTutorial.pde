
boolean DisplayTutorial_init=false;


String img_name;
char CurrentLetter='A';
PImage CurrentImage;


void DisplayTutorial() {
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


void DisplayTutorial_setup() {
  CurrentLetter='A';
  background(ColorBG);
  DisplayTutorial_init=true;
}



void DisplayTutorial_ButtonFuntions() {
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
