//DISPLAY HOME
//Screen Address: 0x0000


boolean DisplayHome_init=false;


void DisplayHome() {
  background(ColorBG);
  if (!DisplayHome_init) {
    DisplayHome_Setup();
  }
  fill(#000000);
  strokeWeight(0);
  textFont(Font_Default_Bold, 30);
  textSize(50);
  textAlign(CENTER, CENTER);
  text("KAMOTALK 2024", width/2, 30);

  PrintButton(TRANSLATE);

  PrintButton(ADD_GESTURE);
}


void DisplayHome_Setup() {
  background(ColorBG);
  DisplayHome_init=true;
}
