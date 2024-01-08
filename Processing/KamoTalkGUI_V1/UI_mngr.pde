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
