//GUI Manager

void CreateButton_Default(int cursorX, int cursorY, color colorBG, color colorSTK, String btn_text, PFont FontTXT, color colorTXT, int txtSIZE) {
  fill(colorBG);
  stroke(colorSTK);
  strokeWeight(3);
  rect(cursorX, cursorY, 300, 50, 15);
  fill(colorTXT);
  noStroke();
  textFont(FontTXT);
  textSize(txtSIZE);
  textAlign(CENTER, CENTER);
  text(btn_text, cursorX+150, cursorY+20);
}


void CreateButton_Large(int cursorX, int cursorY, color colorBG, color colorSTK, String btn_text, PFont FontTXT, color colorTXT, int txtSIZE) {
  fill(colorBG);
  stroke(colorSTK);
  strokeWeight(3);
  rect(cursorX, cursorY, 600, 100, 15);
  fill(colorTXT);
  noStroke();
  textFont(FontTXT);
  textSize(txtSIZE);
  textAlign(CENTER, CENTER);
  text(btn_text, cursorX+300, cursorY+50);
}


void PrintButton(int buttonAddress) {
  switch(buttonAddress) {
  case TRANSLATE:
    if (!ButtonHovered(TRANSLATE)) {
      CreateButton_Large((width/2)-300, 150, Color_GREEN, Color_BLACK, "TRANSLATE", Font_Default_Bold, Color_BLACK, 40);
    } else {
      CreateButton_Large((width/2)-300, 150, Color_YELLOW, Color_BLACK, "TRANSLATE", Font_Default_Bold, Color_BLACK, 40);
    }

    break;

  case ADD_GESTURE:
    if (!ButtonHovered(ADD_GESTURE)) {
      CreateButton_Large((width/2)-300, 300, Color_GREEN, Color_BLACK, "ADD GESTURE", Font_Default_Bold, Color_BLACK, 40);
    } else {
      CreateButton_Large((width/2)-300, 300, Color_YELLOW, Color_BLACK, "ADD GESTURE", Font_Default_Bold, Color_BLACK, 40);
    }

  case SETTINGS:
    if (!ButtonHovered(SETTINGS)) {
      CreateButton_Large((width/2)-300, 450, Color_GREEN, Color_BLACK, "SETTINGS", Font_Default_Bold, Color_BLACK, 40);
    } else {
      CreateButton_Large((width/2)-300, 450, Color_YELLOW, Color_BLACK, "SETTINGS", Font_Default_Bold, Color_BLACK, 40);
    }

    break;
  }
}


boolean ButtonHovered(int buttonAddress) {
  switch(buttonAddress) {
  case TRANSLATE:
    if (mouseX>ButtonGetCursor(TRANSLATE, csrX) && mouseX<ButtonGetCursor(TRANSLATE, csrA) && mouseY>ButtonGetCursor(TRANSLATE, csrY) && mouseY<ButtonGetCursor(TRANSLATE, csrB)) {
      return true;
    } else {
      return false;
    }

  case ADD_GESTURE:
    if (mouseX>ButtonGetCursor(ADD_GESTURE, csrX) && mouseX<ButtonGetCursor(ADD_GESTURE, csrA) && mouseY>ButtonGetCursor(ADD_GESTURE, csrY) && mouseY<ButtonGetCursor(ADD_GESTURE, csrB)) {
      return true;
    } else {
      return false;
    }

  case SETTINGS:
    if (mouseX>ButtonGetCursor(SETTINGS, csrX) && mouseX<ButtonGetCursor(SETTINGS, csrA) && mouseY>ButtonGetCursor(SETTINGS, csrY) && mouseY<ButtonGetCursor(SETTINGS, csrB)) {
      return true;
    } else {
      return false;
    }
}

  return false;
}

int ButtonGetCursor(int buttonAddress, int cursor) {

  switch(buttonAddress) {

  case TRANSLATE:
    switch(cursor) {
    case csrX:
      return ((width/2)-300);
    case csrY:
      return 150;
    case csrA:
      return ((width/2)+300);
    case csrB:
      return 150+100;
    default:
      return 0;
    }

  case ADD_GESTURE:
    switch(cursor) {
    case csrX:
      return ((width/2)-300);
    case csrY:
      return 300;
    case csrA:
      return ((width/2)+300);
    case csrB:
      return 300+100;
    default:
      return 0;
    }

  case SETTINGS:
    switch(cursor) {
    case csrX:
      return ((width/2)-300);
    case csrY:
      return 450;
    case csrA:
      return ((width/2)+300);
    case csrB:
      return 450+100;
    default:
      return 0;
    }
  }

  return 0;
}
