// Android
// Bluetooth
// USB
// Arduino
// Keyboard

#include "HID-Project.h"

#include "akuhell_languages.h"
// choose the language-layout
#define KEYBOARD_LAYOUT_LANG KBD_LAYOUT_DE_DE
#include "akuhell.h"


String utf8char="";
int charLen=0;


void setup()
{
  Serial1.begin(9600);
}

void loop()
{  
  
  if (Serial1.available())
  {
    while(Serial1.available())
    {
      byte bt = Serial1.read();
      //Serial.print("bt ");
      //Serial.println(String(bt, HEX));
      if(utf8char.length()==0)
      {
        charLen=utf8_charlen(bt);
        //Serial.print("charLen ");
        //Serial.println(String(charLen, DEC));
      }
      utf8char+=(char)bt;
      //Serial.print("utf8char len");
      //Serial.println(String(utf8char.length(), DEC));

      if(utf8char.length()==charLen)
      {
        //Serial.print("writeutf8");
        Keyboard_writeUtf8Character(utf8char);
        utf8char="";
      }
    } 
  }  
}
