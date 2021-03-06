
#include "rgb_dmd.h"


#include <Arduino.h>
#include <inttypes.h>
//#include "VersionInfo.h"

#include <String.h>
#include "rgb_dmd.h"
#include "inputSerial.h"
//#include "InputUSB.h"
//#include "Settings.h"

//#include "MatrixSetup.h"
//#include "Palettes.h"


#include "SplashScreen.h"

const PalleteInfo logoPallete2 = {
  "Logo",
  {
    {0x00, 0x00, 0x00},
    {0xFF, 0x00, 0x00},
    {0x00, 0xFF, 0x00},
    {0x00, 0x00, 0xFF},
    {0xFF, 0xFF, 0xFF},
    {0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00}
  }
};

const uint8_t logo4Bit2[10][32] = {
  {0x11, 0x11, 0x11, 0x11, 0x00, 0x02, 0x22, 0x22, 0x22, 0x20, 0x33, 0x33, 0x33, 0x33, 0x00, 0x00, 0x04, 0x44, 0x44, 0x44, 0x00, 0x04, 0x44, 0x00, 0x00, 0x04, 0x44, 0x04, 0x44, 0x44, 0x44, 0x00},
  {0x11, 0x11, 0x11, 0x11, 0x10, 0x22, 0x22, 0x22, 0x22, 0x20, 0x33, 0x33, 0x33, 0x33, 0x30, 0x00, 0x04, 0x44, 0x44, 0x44, 0x40, 0x04, 0x44, 0x40, 0x00, 0x44, 0x44, 0x04, 0x44, 0x44, 0x44, 0x40},
  {0x11, 0x10, 0x00, 0x11, 0x10, 0x22, 0x20, 0x00, 0x00, 0x00, 0x33, 0x30, 0x00, 0x33, 0x30, 0x00, 0x04, 0x44, 0x00, 0x44, 0x44, 0x04, 0x44, 0x44, 0x04, 0x44, 0x44, 0x04, 0x44, 0x00, 0x44, 0x44},
  {0x11, 0x10, 0x00, 0x11, 0x10, 0x22, 0x20, 0x00, 0x00, 0x00, 0x33, 0x30, 0x00, 0x33, 0x30, 0x00, 0x04, 0x44, 0x00, 0x04, 0x44, 0x04, 0x44, 0x44, 0x44, 0x44, 0x44, 0x04, 0x44, 0x00, 0x04, 0x44},
  {0x11, 0x11, 0x11, 0x11, 0x00, 0x22, 0x20, 0x22, 0x22, 0x00, 0x33, 0x33, 0x33, 0x33, 0x00, 0x00, 0x04, 0x44, 0x00, 0x04, 0x44, 0x04, 0x44, 0x44, 0x44, 0x44, 0x44, 0x04, 0x44, 0x00, 0x04, 0x44},
  {0x11, 0x11, 0x11, 0x11, 0x00, 0x22, 0x20, 0x22, 0x22, 0x20, 0x33, 0x33, 0x33, 0x33, 0x00, 0x00, 0x04, 0x44, 0x00, 0x04, 0x44, 0x04, 0x44, 0x04, 0x44, 0x04, 0x44, 0x04, 0x44, 0x00, 0x04, 0x44},
  {0x11, 0x10, 0x00, 0x11, 0x10, 0x22, 0x20, 0x00, 0x22, 0x20, 0x33, 0x30, 0x00, 0x33, 0x30, 0x00, 0x04, 0x44, 0x00, 0x04, 0x44, 0x04, 0x44, 0x00, 0x40, 0x04, 0x44, 0x04, 0x44, 0x00, 0x04, 0x44},
  {0x11, 0x10, 0x00, 0x11, 0x10, 0x22, 0x20, 0x00, 0x22, 0x20, 0x33, 0x30, 0x00, 0x33, 0x30, 0x00, 0x04, 0x44, 0x00, 0x44, 0x44, 0x04, 0x44, 0x00, 0x00, 0x04, 0x44, 0x04, 0x44, 0x00, 0x44, 0x44},
  {0x11, 0x10, 0x00, 0x11, 0x10, 0x22, 0x22, 0x22, 0x22, 0x20, 0x33, 0x33, 0x33, 0x33, 0x30, 0x44, 0x04, 0x44, 0x44, 0x44, 0x40, 0x04, 0x44, 0x00, 0x00, 0x04, 0x44, 0x04, 0x44, 0x44, 0x44, 0x40},
  {0x11, 0x10, 0x00, 0x11, 0x10, 0x02, 0x22, 0x22, 0x22, 0x00, 0x33, 0x33, 0x33, 0x33, 0x00, 0x44, 0x04, 0x44, 0x44, 0x44, 0x00, 0x04, 0x44, 0x00, 0x00, 0x04, 0x44, 0x04, 0x44, 0x44, 0x44, 0x00}
};














String inputString;         // a string to hold incoming data
boolean stringComplete;  // whether the string is complete


Command commands[] ={
  {"help",&help,0,"Show help commands"},
  {"version",&cmd_version,0,"Show Version"},
  {"testje",&cmd_testje,0,"run test function"},
  {"pixel",&cmd_pixel,0,"pixel"},
    {"pixel2",&cmd_pixel,0,"pixel2"},
  {"swap",&cmd_swap,0,"swap"},
  {"clear",&cmd_clear,0,"cleaer screen"},

 // {"rxenable",&cmd_rxenable,0,"Enable channel n"},
//  {"rxdisable",&cmd_rxdisable,0,"Disable channel n"},
//  {"txframe",&cmd_testje,0,"FRAME SEND TEST"},
  
  
  {"ping",&ping,0,"Keep alive test"},
};





// serial
void serialInit() {
    Serial.begin(57600);
    Serial.flush();


  inputString = "";         // a string to hold incoming data 
  stringComplete = false;  // whether the string is complete
} //serialInit

void parseCommand(String cmd, String param) {
  int found = 0;
  cmd.toLowerCase();
  for(unsigned int j=0;j<(sizeof(commands)/sizeof(Command)) ;j++){
    if ( commands[j].name == cmd ){
      commands[j].func( param );
      found = 1 ;
    }
  }

    if ( found == 0 ){
      Serial.println("Command not found.");
    }

} //parseCommand


/*
void loop() {
 
//parseCommand("Help","param1");
//parseCommand("version","param1");
//parseCommand("ping","param1");
//parseCommand("pinG","param1");
//parseCommand("piNg","param1");

if (stringComplete) {
    Serial.print("INPUTSTRING:");
    Serial.println(inputString);

    String param = "";
    String cmd = "";
    // command with parameters
    if ( inputString.indexOf(" ") >0 ) {
      Serial.println("MULTICOMMAND");
      cmd = inputString.substring(0, inputString.indexOf(" "));
      param = inputString.substring( inputString.indexOf(" ")+1);
  } else {
    cmd = inputString;
    
  }

Serial.print("SPLIT#");
Serial.print(cmd);
Serial.print("#");
Serial.print(param);
Serial.println("#");
    
    parseCommand(cmd,param);
    // clear the string:
    inputString = "";
    stringComplete = false;
  }




//Command v ={"name",&test1,"help"};
//v.func("test");



delay(100);
}
*/


/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
void serialEvent() {
//  while (Serial.available()) {
  if (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
       if (inChar == '\n') {
      stringComplete = true;
    } else {
    inputString += inChar;
    }
  }
  if (stringComplete) {
  commandStringComplete();
  }
}

void commandStringComplete() {

    Serial.print("INPUTSTRING:");
    Serial.println(inputString);

    String param = "";
    String cmd = "";
    // command with parameters
    if ( inputString.indexOf(" ") >0 ) {
      Serial.println("MULTICOMMAND");
      cmd = inputString.substring(0, inputString.indexOf(" "));
      param = inputString.substring( inputString.indexOf(" ")+1);
  } else {
    cmd = inputString;
  }

/*
Serial.print("SPLIT#");
Serial.print(cmd);
Serial.print("#");
Serial.print(param);
Serial.println("#");
  */  
    parseCommand(cmd,param);
    // clear the string:
    inputString = "";
    stringComplete = false;
  }






void help(String param ){
Serial.println();
Serial.println("Known commands");
Serial.println("==============");
for(unsigned int i=0;i<(sizeof(commands)/sizeof(Command)) ;i++){
  Serial.print( commands[i].name );
  Serial.print( " - ");
  Serial.println( commands[i].help );
}
Serial.println();
}

void cmd_version(String param ){
Serial.print(F("+RGBDMD:VERSION:"));
//Serial.print( BVERSION );
Serial.println("#");
Serial.println(versionString);
//Serial.print("+");
}



void ping(String param ){
  Serial.println("pong");
}

void cmd_swap(String param ) {
  backgroundLayer.swapBuffers();
}




void cmd_pixel(String param ) {
    rgb24 myColor = {0xff, 0xff, 0xff}; // white
backgroundLayer.drawPixel(0,0,myColor);


}
void cmd_pixel2(String param ) {
  rgb24 myColor = {0xff, 0xff, 0xff}; // white
  
backgroundLayer.drawPixel(5,5,myColor);


}


void cmd_clear(String param ) {
backgroundLayer.fillScreen({0,0,0});
backgroundLayer.swapBuffers(false);
}

void cmd_testje(String param ) {
  Serial.println("testje");

   // matrix.addLayer(&backgroundLayer); 
  backgroundLayer.fillScreen(logoPallete2.colors[10]);
  
  for (uint16_t y = 0; y < 10; y++) {
    rgb24* pixelPtr = backgroundLayer.backBuffer() + ((y + 6) * COL_COUNT) + 32;
    for (uint16_t x = 0; x < 32; x++) {
      *pixelPtr = logoPallete2.colors[logo4Bit2[y][x] >> 4]; pixelPtr++;
      *pixelPtr = logoPallete2.colors[logo4Bit2[y][x] & 0x0F]; pixelPtr++;
    }
  }


    // Need some actual font methods, but this will do for now
    backgroundLayer.setFont(font5x7);
    backgroundLayer.drawString(2, 24, logoPallete2.colors[4], "DID:");
    backgroundLayer.drawString(2 + (5*3), 24, logoPallete2.colors[4], idString);
    backgroundLayer.drawString(COL_COUNT - 2 - (5 * versionLength) - (5*2), 24, logoPallete2.colors[4], "V:");
    backgroundLayer.drawString(COL_COUNT - 2 - (5 * versionLength), 24, logoPallete2.colors[4], versionString);
  
  backgroundLayer.swapBuffers();

  scrollingLayer1.setMode(wrapForward);
  scrollingLayer2.setMode(bounceForward);
  scrollingLayer3.setMode(bounceReverse);
  scrollingLayer4.setMode(wrapForward);
  scrollingLayer5.setMode(bounceForward);

  scrollingLayer1.setColor({0xff, 0xff, 0xff});
  scrollingLayer2.setColor({0xff, 0x00, 0xff});
  scrollingLayer3.setColor({0xff, 0xff, 0x00});
  scrollingLayer4.setColor({0x00, 0x00, 0xff});
  scrollingLayer5.setColor({0xff, 0x00, 0x00});

  scrollingLayer1.setSpeed(10);
  scrollingLayer2.setSpeed(20);
  scrollingLayer3.setSpeed(40);
  scrollingLayer4.setSpeed(80);
  scrollingLayer5.setSpeed(120);

  scrollingLayer1.setFont(gohufont11b);
  scrollingLayer2.setFont(gohufont11);
  scrollingLayer3.setFont(font8x13);
  scrollingLayer4.setFont(font6x10);
  scrollingLayer5.setFont(font5x7);

  scrollingLayer4.setRotation(rotation270);
  scrollingLayer5.setRotation(rotation90);

  scrollingLayer1.setOffsetFromTop((kMatrixHeight/2) - 5);
  scrollingLayer2.setOffsetFromTop((kMatrixHeight/4) - 5);
  scrollingLayer3.setOffsetFromTop((kMatrixHeight/2 + kMatrixHeight/4) - 5);
  scrollingLayer4.setOffsetFromTop((kMatrixWidth/2 + kMatrixWidth/4) - 5);
  scrollingLayer5.setOffsetFromTop((kMatrixWidth/2 + kMatrixWidth/4) - 5);

  scrollingLayer1.start("Layer 1", -1);
  scrollingLayer2.start("Layer 2", -1);
  scrollingLayer3.start("Layer 3", -1);
  scrollingLayer4.start("Layer 4", -1);
scrollingLayer5.start("Layer 5", -1);
}


