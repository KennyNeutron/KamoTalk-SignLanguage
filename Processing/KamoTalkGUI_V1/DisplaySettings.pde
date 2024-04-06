
boolean DisplaySettings_init=false;


void DisplaySettings() {
  if (!DisplaySettings_init) {
    DisplaySettings_setup();
  }

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
}


void DisplaySettings_setup() {
  background(ColorBG);
  DisplaySettings_init=true;
}


void PrintButton_back() {
}
