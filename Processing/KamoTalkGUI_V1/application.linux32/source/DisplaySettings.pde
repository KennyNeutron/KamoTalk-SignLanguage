
boolean DisplaySettings_init=false;

String pwEntered="";


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


void DisplaySettings_setup() {
  background(ColorBG);





  DisplaySettings_init=true;
}


void PrintButton_back() {
}
