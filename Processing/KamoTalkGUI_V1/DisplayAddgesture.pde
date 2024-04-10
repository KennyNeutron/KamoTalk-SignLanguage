
boolean DisplayAddgesture_init=false;
int currentSlot=1;

String currentlyDisplaying="";
String currentToSave="";
boolean SaveAllow=false;

int serialDetect=0;

char ch_currentSlot='1';

void DisplayAddgesture() {
  if (!DisplayAddgesture_init) {
    DisplayAddgesture_setup();
  }

  background(ColorBG);

  fill(0);
  rect(200, 150, 800, 400);

  fill(#ffffff);
  strokeWeight(0);
  textFont(Font_Default_Bold, 45);
  textSize(50);
  textAlign(CENTER, CENTER);
  text("Registered Hand Signs", width/2, 30);



  textFont(Font_Default_Regular, 45);
  textSize(30);
  textAlign(LEFT, TOP);
  text("Current Slot:", 200, 100);
  fill(Color_BLUE);
  textFont(Font_Default_Bold, 45);
  textSize(30);
  text("SLOT#"+(currentSlot), 380, 100);

  fill(Color_GREEN);
  textFont(Font_Default_Regular, 45);
  textSize(20);
  if (currentlyDisplaying.length()==0) {
    text("NONE", 230, 170);
  } else {
    text(currentlyDisplaying, 230, 170);
  }

  text(currentlyDisplaying.length()+"/250", 950, 120);

  if (mouseX>25 && mouseX<100 && mouseY>620 && mouseY<645) {
    CreateButton_XSmall(25, 620, Color_ORANGE, Color_BLACK, "TALK", Font_Default_Bold, Color_BLACK, 15);
  } else {  
    CreateButton_XSmall(25, 620, Color_YELLOW, Color_BLACK, "TALK", Font_Default_Bold, Color_BLACK, 15);
  }



  if (mouseX>25 && mouseX<175 && mouseY>25 && mouseY<75 ) {
    CreateButton_Small(25, 25, Color_YELLOW, Color_BLACK, "BACK", Font_Default_Bold, Color_BLACK, 25);
  } else { 
    CreateButton_Small(25, 25, Color_CYAN, Color_BLACK, "BACK", Font_Default_Bold, Color_BLACK, 25);
  }

  if (mouseX>1020 && mouseX<1170 && mouseY>300 && mouseY<350) {
    CreateButton_Small(1020, 300, Color_YELLOW, Color_BLACK, "NEXT", Font_Default_Bold, Color_BLACK, 25);
  } else {
    CreateButton_Small(1020, 300, Color_CYAN, Color_BLACK, "NEXT", Font_Default_Bold, Color_BLACK, 25);
  }

  if (mouseX>30 && mouseX<180 && mouseY>300 && mouseY<350) {
    CreateButton_Small(30, 300, Color_YELLOW, Color_BLACK, "PREVIOUS", Font_Default_Bold, Color_BLACK, 25);
  } else {
    CreateButton_Small(30, 300, Color_CYAN, Color_BLACK, "PREVIOUS", Font_Default_Bold, Color_BLACK, 25);
  }


  if (mouseX>430 && mouseX<580 && mouseY>580 && mouseY<630) {
    CreateButton_Small(430, 580, Color_ORANGE, Color_BLACK, "DELETE", Font_Default_Bold, Color_BLACK, 25);
  } else {
    CreateButton_Small(430, 580, Color_RED, Color_BLACK, "DELETE", Font_Default_Bold, Color_BLACK, 25);
  }


  if (!SaveAllow) {
    CreateButton_Small(620, 580, Color_GRAY, Color_BLACK, "Duplicate", Font_Default_Bold, Color_BLACK, 25);
  } else {
    if (mouseX>620 && mouseX<770 && mouseY>580 && mouseY<630) {
      CreateButton_Small(620, 580, Color_ORANGE, Color_BLACK, "SAVE", Font_Default_Bold, Color_BLACK, 25);
    } else {
      CreateButton_Small(620, 580, Color_GREEN, Color_BLACK, "SAVE", Font_Default_Bold, Color_BLACK, 25);
    }
  }



  //println(mySerialPort.available());
  if (mySerialPort.available()==0) {
    serialDetect++;
    if (serialDetect>=50) {
      SaveAllow=true;
      serialDetect=0;
    }
  } else {
    serialDetect=0;
    MSerialPort_Val=mySerialPort.read();
    SaveAllow=false;
  }
}



void DisplayAddgesture_setup() {
  background(ColorBG);
  DisplayAddgesture_init=true;
  currentlyDisplaying="";
  currentToSave="";
  //println("init");
  currentlyDisplaying=savedHandsignWordDisplay[currentSlot];
}


void DisplayAddgesture_ButtonFunctions() {
  //Back Button
  if (mouseX>25 && mouseX<175 && mouseY>25 && mouseY<75 ) {
    currentScreen=0x0000;
    DisplayAddgesture_init=false;
  }

  //Next Button
  if (mouseX>1020 && mouseX<1170 && mouseY>300 && mouseY<350) {
    if (currentSlot>=30) {
      currentSlot=1;
      ch_currentSlot='1';
    } else {
      currentSlot++;
      ch_currentSlot++;
    }
    DisplayAddgesture_init=false;
  }

  //Previous Button
  if (mouseX>30 && mouseX<180 && mouseY>300 && mouseY<350) {
    if (currentSlot<=1) {
      currentSlot=30;
      ch_currentSlot='N';
    } else {
      currentSlot--;
      ch_currentSlot--;
    }
    DisplayAddgesture_init=false;
  }

  //Talk Button
  if (mouseX>25 && mouseX<100 && mouseY>620 && mouseY<645) {
    tts.speak(savedHandsignWordDisplay[currentSlot]);
  }


  //DeleteButton
  if (mouseX>430 && mouseX<580 && mouseY>580 && mouseY<630) {

    handsignData.setString(currentSlot-1, "word", "");
    handsignData.setString(currentSlot-1, "display", "");
    saveTable(handsignData, "handsign/handsign.csv");
    println("deleted!");


    LoadSavedFile();

    String sToWrite="{"+ch_currentSlot+"}";
    println("{"+ch_currentSlot+"}");
    mySerialPort.write(sToWrite); 
    DisplayAddgesture_init=false;
  }

  //Save Button
  if (mouseX>620 && mouseX<770 && mouseY>580 && mouseY<630) {
    handsignData.setString(currentSlot-1, "word", currentToSave);
    handsignData.setString(currentSlot-1, "display", currentlyDisplaying);
    saveTable(handsignData, "handsign/handsign.csv");
    println("saved!");


    LoadSavedFile();
    String sToWrite="<"+ch_currentSlot+">";
    println("<"+ch_currentSlot+">");
    mySerialPort.write(sToWrite); 

    DisplayAddgesture_init=false;
  }
}
