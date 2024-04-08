import processing.core.*; 
import processing.data.*; 
import processing.event.*; 
import processing.opengl.*; 

import guru.ttslib.*; 

import java.util.HashMap; 
import java.util.ArrayList; 
import java.io.File; 
import java.io.BufferedReader; 
import java.io.PrintWriter; 
import java.io.InputStream; 
import java.io.OutputStream; 
import java.io.IOException; 

public class ttstest extends PApplet {



TTS tts;

public void setup() {
  
  
  tts = new TTS();
}

public void draw() {
  background(255);
  fill(255);
  ellipse( 35, 30, 25, 35 );
  ellipse( 65, 30, 25, 35 );
  fill(0);
  ellipse( 40, 35, 10, 10 );
  ellipse( 60, 35, 10, 10 );
  noFill();
  arc(50,50,50,50,0,PI);
  
}

public void mousePressed() {
  tts.speak("Hi! I am a speaking Processing sketch");
}
  public void settings() {  size(100,100);  smooth(); }
  static public void main(String[] passedArgs) {
    String[] appletArgs = new String[] { "ttstest" };
    if (passedArgs != null) {
      PApplet.main(concat(appletArgs, passedArgs));
    } else {
      PApplet.main(appletArgs);
    }
  }
}
