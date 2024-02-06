//DISPLAY HOME
//Screen Address: 0x0000


boolean display_HOME_initialize=false;


void display_HOME() {
  fill(#ffffff);
  strokeWeight(0);
  textFont(Font_Default_Bold, 30);
  textSize(50);
  textAlign(CENTER, CENTER);
  text("KAMOTALK 2024", width/2, 30);


  PrintButton(TRANSLATE);

  PrintButton(ADD_GESTURE);


}


void display_HOME_setup() {
  display_HOME_initialize=true;
}
