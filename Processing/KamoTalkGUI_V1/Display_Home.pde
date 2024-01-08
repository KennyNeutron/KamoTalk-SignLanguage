//DISPLAY HOME
//Screen Address: 0x0000


boolean display_HOME_initialize=false;

void display_HOME() {
  if (!display_HOME_initialize) {
    display_HOME_setup();
  }
}


void display_HOME_setup() {
  CreateButton_Default((width/2)-150, 200, Color_GREEN, Color_BLACK, "TRANSLATE", Font_Default_Bold, Color_BLACK, 30);
  CreateButton_Default((width/2)-150, 300, Color_GREEN, Color_BLACK, "ADD GESTURE", Font_Default_Bold, Color_BLACK, 25);
  CreateButton_Default((width/2)-150, 400, Color_GREEN, Color_BLACK, "SETTINGS", Font_Default_Bold, Color_BLACK, 30);

  display_HOME_initialize=true;
}
