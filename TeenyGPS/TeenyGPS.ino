/*
    TeenyGPS 
    
    for use with teensy3 and the Xplane plugin for teensy to add 13 buttons and 2 single or 1
    dual encoder 


    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
    
    

*/

#include <ClickButton.h>
#include <Encoder.h>


//pin configs
const int LEDPIN = 13;
const int RESOLUTION = 4;
const int BUTTON_ENT = 14;
const int BUTTON_CRSR = 15;
const int BUTTON_RNGUP = 16;
const int BUTTON_RNGDN = 17;
const int BUTTON_D = 18;
const int BUTTON_MENU = 19;
const int BUTTON_CLR = 20;
const int BUTTON_CDI = 21;
const int BUTTON_OBS = 22;
const int BUTTON_MSG = 23;
const int BUTTON_FLP = 12;


ClickButton button_ent(BUTTON_ENT, LOW, CLICKBTN_PULLUP);
ClickButton button_crsr(BUTTON_CRSR, LOW, CLICKBTN_PULLUP);
ClickButton button_rngup(BUTTON_RNGUP, LOW, CLICKBTN_PULLUP);
ClickButton button_rngdn(BUTTON_RNGDN, LOW, CLICKBTN_PULLUP);
ClickButton button_D(BUTTON_D, LOW, CLICKBTN_PULLUP);
ClickButton button_Menu(BUTTON_MENU, LOW, CLICKBTN_PULLUP);
ClickButton button_CLR(BUTTON_CLR, LOW, CLICKBTN_PULLUP);
ClickButton button_CDI(BUTTON_CDI, LOW, CLICKBTN_PULLUP);
ClickButton button_OBS(BUTTON_OBS, LOW, CLICKBTN_PULLUP);
ClickButton button_MSG(BUTTON_MSG, LOW, CLICKBTN_PULLUP);
ClickButton button_FLP(BUTTON_FLP, LOW, CLICKBTN_PULLUP);

const int coarsedn= 5;
const int coarseup= 6;
const int fineup= 8;
const int finedn= 7;


Encoder Page1(coarseup, coarsedn); // GPS coarse up and Down
Encoder Fine(fineup, finedn); // GPS fine up and Down

FlightSimCommand COM1CoarseUp;
FlightSimCommand COM1CoarseDown;
FlightSimCommand COM1FineUp;
FlightSimCommand COM1FineDown;
FlightSimCommand COM1ENT;
FlightSimCommand COM1CRSR;
FlightSimCommand RNGDN;
FlightSimCommand RNGUP;
FlightSimCommand DIRECT;
FlightSimCommand MENU;
FlightSimCommand CLR;
FlightSimCommand CDI;
FlightSimCommand OBS;
FlightSimCommand MSG;
FlightSimCommand FLP;


// reset endcoders to 0
long com1_enc = 0;  
long com2_enc = 0;
long enc1 = 0;
long enc2 = 0;


void setup(){
  Serial.begin(38400);  //debug serial output
  // debounce and pin setup
  pinMode(13,OUTPUT); //debug to led 13
  pinMode(BUTTON_ENT, INPUT_PULLUP);
  button_ent.debounceTime   = 20;   // Debounce timer in ms

// XPlane Refs
  COM1CoarseUp = XPlaneRef("sim/GPS/g430n1_page_up");
  COM1CoarseDown = XPlaneRef("sim/GPS/g430n1_page_dn");
  COM1FineUp = XPlaneRef("sim/GPS/g430n1_chapter_up");
  COM1FineDown = XPlaneRef("sim/GPS/g430n1_chapter_dn");
  COM1CRSR = XPlaneRef("sim/GPS/g430n1_cursor");
  COM1ENT = XPlaneRef("sim/GPS/g430n1_ent");
  RNGDN = XPlaneRef("sim/GPS/g430n1_zoom_out");
  RNGUP = XPlaneRef("sim/GPS/g430n1_zoom_in");
  MENU = XPlaneRef("sim/GPS/g430n1_menu");
  CLR = XPlaneRef("sim/GPS/g430n1_clr");
  CDI = XPlaneRef("sim/GPS/g430n1_cdi");  
  OBS = XPlaneRef("sim/GPS/g430n1_obs");
  MSG = XPlaneRef("sim/GPS/g430n1_msg");  
  FLP = XPlaneRef("sim/GPS/g430n1_fpl");
  DIRECT = XPlaneRef("sim/GPS/g430n1_direct");
  
}

void loop(){
  FlightSim.update();
// Right side Encoder (should be one dual encoder)
   enc1 = Page1.read();
  if (enc1 > com1_enc + RESOLUTION)
  {
    COM1CoarseDown.once();
    //Serial.println("Coarse Down"); //debuging code
    com1_enc = enc1;
  }
  else if (enc1 < com1_enc - RESOLUTION)
  {
    COM1CoarseUp.once();
    //Serial.println("Coarse UP!"); //debuging code
    com1_enc = enc1;
  }

  enc2 = Fine.read();
  if (enc2 > com2_enc + RESOLUTION)
  {
    COM1FineDown.once();
//   Serial.println("Fine Down!"); //debuging code
    com2_enc = enc2;
  }
  else if (enc2 < com2_enc - RESOLUTION)
  {

    COM1FineUp.once();
//    Serial.println("Fine UP!"); //debuging code
    com2_enc = enc2;
  }

// Buttons from here 


  button_ent.Update();
  if(button_ent.clicks == 1){
    COM1CRSR.once();
    Serial.println("COM1ENT");
  }
 
 button_crsr.Update(); 
  if(button_crsr.clicks == 1){
    COM1CRSR.once();
 //   Serial.println("COM1CRSR"); //debuging code
 }
  
button_rngdn.Update();
  if(button_rngdn.clicks == 1){
    RNGDN.once();
//  Serial.println("RNGDN");//debuging code
  }

  button_rngup.Update();
  if(button_rngup.clicks == 1){
    RNGUP.once();
//    Serial.println("RNGUP"); //debuging code
  }

  button_D.Update();
  if(button_D.clicks == 1){
    DIRECT.once();
    //Serial.println("Direct"); //debuging code
  }
  button_Menu.Update();
  if(button_Menu.clicks == 1){
    MENU.once();
    //Serial.println("Menu");//debuging code
  }
  button_CLR.Update();
  if(button_CLR.clicks == 1){
    CLR.once();
    //Serial.println("CLR");//debuging code
  }
  button_CDI.Update();
  if(button_CDI.clicks == 1){
    CDI.once();
    //Serial.println("CDI"); //debuging code
  }
  
  button_OBS.Update();
  if(button_OBS.clicks == 1){
    OBS.once();
    //Serial.println("OBS");//debuging code
  }

  button_MSG.Update();
  if(button_MSG.clicks == 1){
    MSG.once();
    //Serial.println("MSG");//debuging code
  }

  button_FLP.Update();
  if(button_FLP.clicks == 1){
    FLP.once();
    //Serial.println("FLP"); //debuging code
  }


}


