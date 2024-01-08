//KamoTalk V1.0.0

PFont Font_Default_Regular;
PFont Font_Default_Bold;

color Color_BLACK= color(0, 0, 0);
color Color_RED= color(255, 0, 0);
color Color_GREEN= color(0, 255, 0);
color Color_WHITE= color(255, 255, 255);
color Color_CYAN= color(0, 255, 255);
color Color_MAGENTA= color(255, 0, 255);
color Color_YELLOW= color(255, 255, 0);




void setup() {
  size(1200, 650);
  background(#808080);

  Font_Default_Regular=createFont("OpenSansRegular.ttf", 48);
  Font_Default_Bold=createFont("OpenSansBold.ttf", 48);

  fill(#ffffff);
  strokeWeight(0);
  textFont(Font_Default_Bold, 30);
  textSize(30);
  textAlign(CENTER, CENTER);
  text("KAMOTALK 2024", width/2, 30);

  
}


void draw() {
  display_HOME();
}
