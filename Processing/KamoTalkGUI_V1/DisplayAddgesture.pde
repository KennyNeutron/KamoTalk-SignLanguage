
boolean DisplayAddgesture_init=false;
int currentSlot=1;



void DisplayAddgesture() {
  if (!DisplayAddgesture_init) {
    DisplayAddgesture_setup();
  }

  background(ColorBG);

  fill(0);
  rect(200, 150, 800, 400);

  fill(#ffffff);
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
  textSize(20);
  if (savedHandsignWordDisplay[currentSlot].length()==0) {
    text("NONE", 205, 150);
  } else {
    text(savedHandsignWordDisplay[currentSlot], 205, 150);
  }

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

  if (mouseX>620 && mouseX<770 && mouseY>580 && mouseY<630) {
    CreateButton_Small(620, 580, Color_ORANGE, Color_BLACK, "SAVE", Font_Default_Bold, Color_BLACK, 25);
  } else {
    CreateButton_Small(620, 580, Color_GREEN, Color_BLACK, "SAVE", Font_Default_Bold, Color_BLACK, 25);
  }
}


void DisplayAddgesture_setup() {
  background(ColorBG);
  DisplayAddgesture_init=true;
  //savedHandsignWordDisplay[1]="Hey, how have you been? I've been meaning to catch up with you. \nWhat's new in your life lately?";
  //savedHandsignWordDisplay[2]="Good day! I hope you're doing well. How's your day been shaping up?";

  //savedHandsignWord[1]="Hey, how have you been? I've been meaning to catch up with you. What's new in your life lately?";
  //savedHandsignWord[2]="Good day! I hope you're doing well. How's your day been shaping up?";

  ///savedHandsignWordDisplay[2]="Hey there, stranger! It feels like it's been ages since we last talked. How have you been keeping yourself busy?";
}


void DisplayAddgesture_ButtonFunctions() {
  //Back Button
  if (mouseX>25 && mouseX<175 && mouseY>25 && mouseY<75 ) {
    currentScreen=0x0000;
    DisplaySettings_init=false;
  }

  //Next Button
  if (mouseX>1020 && mouseX<1170 && mouseY>300 && mouseY<350) {
    if (currentSlot>=30) {
      currentSlot=1;
    } else {
      currentSlot++;
    }
  }

  //Previous Button
  if (mouseX>30 && mouseX<180 && mouseY>300 && mouseY<350) {
    if (currentSlot<=1) {
      currentSlot=30;
    } else {
      currentSlot--;
    }
  }

  //Talk Button
  if (mouseX>25 && mouseX<100 && mouseY>620 && mouseY<645) {
        tts.speak(savedHandsignWordDisplay[currentSlot]);
  }
}
