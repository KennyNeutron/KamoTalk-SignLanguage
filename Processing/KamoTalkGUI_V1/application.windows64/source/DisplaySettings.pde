
boolean DisplaySettings_init=false;

String pwEntered="";
int currentCOM=0;

void DisplaySettings() {
  if (!DisplaySettings_init) {
    DisplaySettings_setup();
  }

  background(ColorBG);

  fill(#ffffff);
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
    CreateButton_XSmall(760, 160, Color_YELLOW, Color_BLACK, "SAVE", Font_Default_Bold, Color_BLACK, 15);
  } else {
    CreateButton_XSmall(760, 160, Color_GREEN, Color_BLACK, "SAVE", Font_Default_Bold, Color_BLACK, 15);
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


void DisplaySettings_setup() {
  background(ColorBG);

  DisplaySettings_init=true;
}

String dpw="";
void DisplaySettings_ButtonFunctions() {
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

boolean pwMatch() {
  LoadSavedFile();
  if (dpw.equals(pwEntered)) {
    return true;
  } else {
    return false;
  }
}
