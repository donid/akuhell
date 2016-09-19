#include "HID-Project.h"


//LAYOUT_US_ENGLISH is used/tested in ImprovedKeylayouts.h -> we can't use it
//instead of arbitrary values: https://msdn.microsoft.com/en-us/goglobal/bb964664.aspx
#define KBD_LAYOUT_EN_US 1033
#define KBD_LAYOUT_DE_DE 1031

#define KEYBOARD_LAYOUT_LANG KBD_LAYOUT_DE_DE


#if !defined(KEYBOARD_LAYOUT_LANG)
#error This keyboard layout language is not defined.
#endif



enum KeyboardModifier : uint8_t
{
  KEYMODIF_NONE = 0,
  KEYMODIF_LEFT_CTRL = 1,
  KEYMODIF_LEFT_SHIFT = 2,
  KEYMODIF_LEFT_ALT = 4,
  KEYMODIF_LEFT_WINDOWS = 8,
};


size_t Keyboard_write(KeyboardKeycode k, KeyboardModifier modifier)
{
  if (modifier & KEYMODIF_LEFT_CTRL)
  {
    Keyboard.press(KEY_LEFT_CTRL);
  }
  if (modifier & KEYMODIF_LEFT_SHIFT)
  {
    Keyboard.press(KEY_LEFT_SHIFT);
  }
  if (modifier & KEYMODIF_LEFT_ALT)
  {
    Keyboard.press(KEY_LEFT_ALT);
  }
  if (modifier & KEYMODIF_LEFT_WINDOWS)
  {
    Keyboard.press(KEY_LEFT_WINDOWS);
  }

  Keyboard.press(k);
  Keyboard.releaseAll();//todo: library-version of write calls release only when retval of press!=0 and returns retval
}


// EN_US version of this is the same as the values in HID_project\src\HID-APIs\ImprovedKeylayouts.h
size_t Keyboard_convertUtf8CharacterToKeycode(String ch, KeyboardKeycode & k, KeyboardModifier & modifier)
{
  modifier=KEYMODIF_NONE;
      
  if(ch.length()==1)
  {
    char firstByte=ch.charAt(0);
    if     (firstByte==0x08) { k=KEY_BACKSPACE; return 0; }
    else if(firstByte==0x09) { k=KEY_TAB; return 0; }
    else if(firstByte==0x0A) { k=KEY_ENTER; return 0; }//todo: use 0x0D (CR)? 
    else if(firstByte==0x1B) { k=KEY_ESC; return 0; }
    else if(firstByte==0x20) { k=KEY_SPACE; return 0; }
    else if(firstByte==0x21) { k=KEY_1; modifier=KEYMODIF_LEFT_SHIFT; return 0; } // !
#if KEYBOARD_LAYOUT_LANG == KBD_LAYOUT_EN_US
    else if(firstByte==0x22) { k=KEY_QUOTE; modifier=KEYMODIF_LEFT_SHIFT; return 0; } // "
    else if(firstByte==0x23) { k=KEY_3; modifier=KEYMODIF_LEFT_SHIFT; return 0; } // #
#endif
#if KEYBOARD_LAYOUT_LANG == KBD_LAYOUT_DE_DE
    else if(firstByte==0x22) { k=KEY_2; modifier=KEYMODIF_LEFT_SHIFT; return 0; } // "
    else if(firstByte==0x23) { k=KEY_BACKSLASH; return 0; } // #
#endif
    else if(firstByte==0x24) { k=KEY_4; modifier=KEYMODIF_LEFT_SHIFT; return 0; } // $
    else if(firstByte==0x25) { k=KEY_5; modifier=KEYMODIF_LEFT_SHIFT; return 0; } // %
#if KEYBOARD_LAYOUT_LANG == KBD_LAYOUT_EN_US
    else if(firstByte==0x26) { k=KEY_7; modifier=KEYMODIF_LEFT_SHIFT; return 0; } // &
    else if(firstByte==0x27) { k=KEY_QUOTE; return 0; } // '
    else if(firstByte==0x28) { k=KEY_9; modifier=KEYMODIF_LEFT_SHIFT; return 0; } // (
    else if(firstByte==0x29) { k=KEY_0; modifier=KEYMODIF_LEFT_SHIFT; return 0; } // )
    else if(firstByte==0x2A) { k=KEY_8; modifier=KEYMODIF_LEFT_SHIFT; return 0; } // *
    else if(firstByte==0x2B) { k=KEY_EQUAL; modifier=KEYMODIF_LEFT_SHIFT; return 0; } // +
#endif
#if KEYBOARD_LAYOUT_LANG == KBD_LAYOUT_DE_DE
    else if(firstByte==0x26) { k=KEY_6; modifier=KEYMODIF_LEFT_SHIFT; return 0; } // &
    else if(firstByte==0x27) { k=KEY_BACKSLASH; modifier=KEYMODIF_LEFT_SHIFT; return 0; } // '
    else if(firstByte==0x28) { k=KEY_8; modifier=KEYMODIF_LEFT_SHIFT; return 0; } // (
    else if(firstByte==0x29) { k=KEY_9; modifier=KEYMODIF_LEFT_SHIFT; return 0; } // )
    else if(firstByte==0x2A) { k=KEY_RIGHT_BRACE; modifier=KEYMODIF_LEFT_SHIFT; return 0; } // *
    else if(firstByte==0x2B) { k=KEY_RIGHT_BRACE; return 0; } // +
#endif
    else if(firstByte==0x2C) { k=KEY_COMMA; return 0; } // ,
    else if(firstByte==0x2E) { k=KEY_PERIOD; return 0; } // .
#if KEYBOARD_LAYOUT_LANG == KBD_LAYOUT_EN_US    
    else if(firstByte==0x2D) { k=KEY_MINUS; return 0; } // -
    else if(firstByte==0x2F) { k=KEY_SLASH; return 0; } // /
#endif
#if KEYBOARD_LAYOUT_LANG == KBD_LAYOUT_DE_DE
    else if(firstByte==0x2D) { k=KEY_SLASH; return 0; } // -
    else if(firstByte==0x2F) { k=KEY_7; modifier=KEYMODIF_LEFT_SHIFT; return 0; } // /
#endif
    else if(firstByte==0x30) { k=KEY_0; return 0; } // 0
    else if(firstByte>=0x31&&firstByte<=0x39) { k=(KeyboardKeycode)(KEY_1+(firstByte-0x31)); return 0; } // 1 to 9
#if KEYBOARD_LAYOUT_LANG == KBD_LAYOUT_EN_US    
    else if(firstByte==0x3A) { k=KEY_SEMICOLON; modifier=KEYMODIF_LEFT_SHIFT; return 0; } // :
    else if(firstByte==0x3B) { k=KEY_SEMICOLON; return 0; } // ;
    else if(firstByte==0x3C) { k=KEY_COMMA; modifier=KEYMODIF_LEFT_SHIFT; return 0; } // <
    else if(firstByte==0x3D) { k=KEY_EQUAL; return 0; } // =
    else if(firstByte==0x3E) { k=KEY_PERIOD; modifier=KEYMODIF_LEFT_SHIFT; return 0; } // >
    else if(firstByte==0x3F) { k=KEY_SLASH; modifier=KEYMODIF_LEFT_SHIFT; return 0; } // ?
    else if(firstByte==0x40) { k=KEY_2; modifier=KEYMODIF_LEFT_SHIFT; return 0; } // @
#endif
#if KEYBOARD_LAYOUT_LANG == KBD_LAYOUT_DE_DE
    else if(firstByte==0x3A) { k=KEY_PERIOD; modifier=KEYMODIF_LEFT_SHIFT; return 0; } // :    
    else if(firstByte==0x3B) { k=KEY_COMMA; modifier=KEYMODIF_LEFT_SHIFT; return 0; } // ;    
    else if(firstByte==0x3C) { k=KEY_NON_US; return 0; } // <    
    else if(firstByte==0x3D) { k=KEY_0; modifier=KEYMODIF_LEFT_SHIFT; return 0; } // =    
    else if(firstByte==0x3E) { k=KEY_NON_US; modifier=KEYMODIF_LEFT_SHIFT; return 0; } // >    
    else if(firstByte==0x3F) { k=KEY_MINUS; modifier=KEYMODIF_LEFT_SHIFT; return 0; } // ?    
    else if(firstByte==0x40) { k=KEY_Q; modifier=(KeyboardModifier)(KEYMODIF_LEFT_CTRL|KEYMODIF_LEFT_ALT); return 0; } // @
#endif
    else if(firstByte>=0x41&&firstByte<=0x58) { k=(KeyboardKeycode)(KEY_A+(firstByte-0x41)); modifier=KEYMODIF_LEFT_SHIFT; return 0; } // A to X
#if KEYBOARD_LAYOUT_LANG == KBD_LAYOUT_EN_US
    else if(firstByte==0x59) { k=KEY_Y; modifier=KEYMODIF_LEFT_SHIFT; return 0; } // Y
    else if(firstByte==0x5A) { k=KEY_Z; modifier=KEYMODIF_LEFT_SHIFT; return 0; } // Z
    else if(firstByte==0x5B) { k=KEY_LEFT_BRACE; return 0; } // [
    else if(firstByte==0x5C) { k=KEY_BACKSLASH; return 0; } // '\'
    else if(firstByte==0x5D) { k=KEY_RIGHT_BRACE; return 0; } // ]
    else if(firstByte==0x5E) { k=KEY_6; modifier=KEYMODIF_LEFT_SHIFT; return 0; } // ^
    else if(firstByte==0x5F) { k=KEY_MINUS; modifier=KEYMODIF_LEFT_SHIFT; return 0; } // _
    else if(firstByte==0x60) { k=KEY_TILDE; return 0; } // `
#endif
#if KEYBOARD_LAYOUT_LANG == KBD_LAYOUT_DE_DE
    else if(firstByte==0x59) { k=KEY_Z; modifier=KEYMODIF_LEFT_SHIFT; return 0; } // Y
    else if(firstByte==0x5A) { k=KEY_Y; modifier=KEYMODIF_LEFT_SHIFT; return 0; } // Z    
    else if(firstByte==0x5B) { k=KEY_8; modifier=(KeyboardModifier)(KEYMODIF_LEFT_CTRL|KEYMODIF_LEFT_ALT); return 0; } // [
    else if(firstByte==0x5C) { k=KEY_MINUS; modifier=(KeyboardModifier)(KEYMODIF_LEFT_CTRL|KEYMODIF_LEFT_ALT); return 0; } // '\'
    else if(firstByte==0x5D) { k=KEY_9; modifier=(KeyboardModifier)(KEYMODIF_LEFT_CTRL|KEYMODIF_LEFT_ALT); return 0; } // ]
    else if(firstByte==0x5E) { k=KEY_TILDE; return 0; } // ^    
    else if(firstByte==0x5F) { k=KEY_SLASH; modifier=KEYMODIF_LEFT_SHIFT; return 0; } // _    
    else if(firstByte==0x60) { k=KEY_EQUAL; modifier=KEYMODIF_LEFT_SHIFT; return 0; } // `
#endif
    else if(firstByte>=0x61&&firstByte<=0x78) { k=(KeyboardKeycode)(KEY_A+(firstByte-0x61)); return 0; } // a to x
#if KEYBOARD_LAYOUT_LANG == KBD_LAYOUT_EN_US
    else if(firstByte==0x79) { k=KEY_Y; return 0; } // y
    else if(firstByte==0x7A) { k=KEY_Z; return 0; } // z    
    else if(firstByte==0x7B) { k=KEY_LEFT_BRACE; modifier=KEYMODIF_LEFT_SHIFT; return 0; } // {
    else if(firstByte==0x7C) { k=KEY_BACKSLASH; modifier=KEYMODIF_LEFT_SHIFT; return 0; } // |
    else if(firstByte==0x7D) { k=KEY_RIGHT_BRACE; modifier=KEYMODIF_LEFT_SHIFT; return 0; } // }
    else if(firstByte==0x7E) { k=KEY_TILDE; modifier=KEYMODIF_LEFT_SHIFT; return 0; } // ~
#endif
#if KEYBOARD_LAYOUT_LANG == KBD_LAYOUT_DE_DE
    else if(firstByte==0x79) { k=KEY_Z; return 0; } // y
    else if(firstByte==0x7A) { k=KEY_Y; return 0; } // z
    else if(firstByte==0x7B) { k=KEY_7; modifier=(KeyboardModifier)(KEYMODIF_LEFT_CTRL|KEYMODIF_LEFT_ALT); return 0; } // {    
    else if(firstByte==0x7C) { k=KEY_NON_US; modifier=(KeyboardModifier)(KEYMODIF_LEFT_CTRL|KEYMODIF_LEFT_ALT); return 0; } // |
    else if(firstByte==0x7D) { k=KEY_0; modifier=(KeyboardModifier)(KEYMODIF_LEFT_CTRL|KEYMODIF_LEFT_ALT); return 0; } // }    
    else if(firstByte==0x7E) { k=KEY_RIGHT_BRACE; modifier=(KeyboardModifier)(KEYMODIF_LEFT_CTRL|KEYMODIF_LEFT_ALT); return 0; } // ~
#endif
    else if(firstByte==0x7F) { k=KEY_DELETE; return 0; } // DEL(Entf)
  }
  else if(ch.length()==2)
  {
    byte firstByte=ch.charAt(0);
    byte secondByte=ch.charAt(1);
    //Serial.println("2bytes");
    //Serial.println(firstByte, HEX);
    //Serial.println(secondByte, HEX);
#if KEYBOARD_LAYOUT_LANG == KBD_LAYOUT_DE_DE
    if(firstByte==0xC2 && secondByte==0xA7) { k=KEY_3; modifier=KEYMODIF_LEFT_SHIFT; return 0; } // §
    else if(firstByte==0xC2 && secondByte==0xB2) { k=KEY_2; modifier=(KeyboardModifier)(KEYMODIF_LEFT_CTRL|KEYMODIF_LEFT_ALT); return 0; } // ²
    else if(firstByte==0xC2 && secondByte==0xB3) { k=KEY_3; modifier=(KeyboardModifier)(KEYMODIF_LEFT_CTRL|KEYMODIF_LEFT_ALT); return 0; } // ³
    else if(firstByte==0xC2 && secondByte==0xB4) { k=KEY_EQUAL; return 0; } // ´
    else if(firstByte==0xC2 && secondByte==0xB5) { k=KEY_M; modifier=(KeyboardModifier)(KEYMODIF_LEFT_CTRL|KEYMODIF_LEFT_ALT); return 0; } // µ
    else if(firstByte==0xC2 && secondByte==0xB0) { k=KEY_TILDE; modifier=KEYMODIF_LEFT_SHIFT; return 0; } // ° (Degree) // 0xC2 0xBA 'MASCULINE ORDINAL INDICATOR' locks the same!
    else if(firstByte==0xC3 && secondByte==0x84) { k=KEY_QUOTE; modifier=KEYMODIF_LEFT_SHIFT; return 0; } // Ä
    else if(firstByte==0xC3 && secondByte==0x96) { k=KEY_SEMICOLON; modifier=KEYMODIF_LEFT_SHIFT; return 0; } // Ö
    else if(firstByte==0xC3 && secondByte==0x9C) { k=KEY_LEFT_BRACE; modifier=KEYMODIF_LEFT_SHIFT; return 0; } // Ü
    else if(firstByte==0xC3 && secondByte==0x9F) { k=KEY_MINUS; return 0; } // ß
    else if(firstByte==0xC3 && secondByte==0xA4) { k=KEY_QUOTE; return 0; } // ä
    else if(firstByte==0xC3 && secondByte==0xB6) { k=KEY_SEMICOLON; return 0; } // ö
    else if(firstByte==0xC3 && secondByte==0xBC) { k=KEY_LEFT_BRACE; return 0; } // ü
#endif
  }
  else if(ch.length()==3)
  {
    byte firstByte=ch.charAt(0); // when using 'char' the comparison does not seem to work and println prints e.g. FFFFFFE2
    byte secondByte=ch.charAt(1);
    byte thirdByte=ch.charAt(2);

#if KEYBOARD_LAYOUT_LANG == KBD_LAYOUT_DE_DE
    //Serial.println("fb");
    //Serial.println(firstByte, HEX);
    //Serial.println(secondByte, HEX);
    //Serial.println(thirdByte, HEX);
    if(firstByte==0xE2 && secondByte==0x82 && thirdByte==0xAC) { k=KEY_E; modifier=(KeyboardModifier)(KEYMODIF_LEFT_CTRL|KEYMODIF_LEFT_ALT); return 0; } // €
#endif
  } 
  
  return 1;//unable to convert
}

void Keyboard_writeUtf8Character(const String & ch)
{
  KeyboardKeycode k=KEY_RESERVED;//invalid
  KeyboardModifier modifier=KEYMODIF_NONE;
  Keyboard_convertUtf8CharacterToKeycode(ch, k, modifier);//todo: check retval
  //Serial.print("wutf ");
  //Serial.print(k);
  //Serial.print(" ");
  //Serial.println(modifier);
  Keyboard_write(k, modifier);
}


int utf8_charlen(byte firstByte)
{
  if      (firstByte>=0   && firstByte<=127) return 1;
  else if ((firstByte & 0xE0) == 0xC0) return 2;
  else if ((firstByte & 0xF0) == 0xE0) return 3;
  else if ((firstByte & 0xF8) == 0xF0) return 4;
  //else if ((firstByte & 0xFC) == 0xF8) return 5; //byte 5, unnecessary in 4 byte UTF-8
  //else if ((firstByte & 0xFE) == 0xFC) return 6; //byte 6, unnecessary in 4 byte UTF-8
  else return -1;//invalid utf8
}


int utf8_strlen(const String & str)
{
    int byteCount=str.length();
    int result=0;
    for (int i=0; i < byteCount;)
    {
        byte currentFirstByte = str.charAt(i);
        int charlen = utf8_charlen(currentFirstByte);
        if(currentFirstByte==-1)
        {
          return -1;//invalid utf8
        }
        i+=charlen;
        ++result;
    }
    return result;
}

void Keyboard_writeUtf8String(const String & ch)
{
    int byteCount=ch.length();
    for (int i=0; i < byteCount;)
    {
        byte currentFirstByte = ch.charAt(i);
        int charlen = utf8_charlen(currentFirstByte);
        if(currentFirstByte==-1)
        {
          return;//invalid utf8
        }
        String currentChar=ch.substring(i,i+charlen);
        Keyboard_writeUtf8Character(currentChar);
        i+=charlen;
    }
}

int buttonPin = 9;  // Set a button to any pin

void setup()
{
  pinMode(buttonPin, INPUT);  // Set the button as an input
  digitalWrite(buttonPin, HIGH);  // Pull the button high
}

void loop()
{
  if (digitalRead(buttonPin) == 0)  // if the button goes low
  {
    Serial.println("button low");
    Keyboard_writeUtf8Character("²");
    Keyboard_writeUtf8Character("€");
    Keyboard_writeUtf8Character("y");
    Keyboard_writeUtf8Character("$");
    Keyboard_writeUtf8Character("#");
    Keyboard_writeUtf8Character("0");
    Keyboard_writeUtf8Character("1");

    Keyboard_writeUtf8String(" ^°1!2²\"3§³4$5%6&7/{8([9)]0=}ß?\\´`qQ@wWeE€rRtTzZuUiIoOpPüÜ+*~aAsSdDfFgGhHjJkKlLöÖäÄ#'<>|yYxXcCvVbBnNmMµ,;.:-_");
   
    delay(1000);  // delay so there aren't a kajillion z's
  }
}


