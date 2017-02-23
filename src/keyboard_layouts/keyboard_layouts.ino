#include "HID-Project.h"

#include "akuhell_languages.h"
// choose the language-layout
#define KEYBOARD_LAYOUT_LANG KBD_LAYOUT_DE_DE
#include "akuhell.h"

int buttonPin = 9;  // Set a button to any pin

void setup()
{
  pinMode(buttonPin, INPUT);  // Set the button as an input
  digitalWrite(buttonPin, HIGH);  // Pull the button high
  //Serial.begin(9600);
  //Serial.println("akuhell initialize v1");
}

void loop()
{
  if (digitalRead(buttonPin) == 0)  // if the button goes low
  {
    Serial.println("button low (v1)");

    String s1="h§öß";
    String s2=utf8_charAt(s1,2);
    Keyboard_writeUtf8Character(s2);
    
    Keyboard_writeUtf8Character("²");
    Keyboard_writeUtf8Character("€");
    Keyboard_writeUtf8Character("y");
    Keyboard_writeUtf8Character("$");
    Keyboard_writeUtf8Character("#");
    Keyboard_writeUtf8Character("0");
    Keyboard_writeUtf8Character("1");

    Keyboard_writeUtf8String(" ^°1!2²\"3§³4$5%6&7/{8([9)]0=}ß?\\´`qQ@wWeE€rRtTzZuUiIoOpPüÜ+*~aAsSdDfFgGhHjJkKlLöÖäÄ#'<>|yYxXcCvVbBnNmMµ,;.:-_");
   
    delay(1000);
  }
}


