//DISPLAY HOME
//Screen Address: 0x0000


boolean DisplayHome_init=false;


void DisplayHome() {
  if(!DisplayHome_init){
    DisplayHome_Setup();
  }
  fill(#000000);
  strokeWeight(0);
  textFont(Font_Default_Regular, 30);
  textSize(50);
  textAlign(CENTER, CENTER);
  text("KAMOTALK 2024", width/2, 30);

  textSize(10);
  text(str_ToSpeak, width/2, 10);


  PrintButton(TRANSLATE);

  PrintButton(ADD_GESTURE);
}


void DisplayHome_Setup() {
  background(ColorBG);
  DisplayHome_init=true;
}
