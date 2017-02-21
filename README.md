# akuhell
This repository contains code that makes it easy to use an arduino as keyboard with non-US layout.

Its name is composed of letters of the topics involved:
- Arduino
- Keyboard
- USB
- HID
- Language Layout

And because I have seen quite a few people asking for help in this area,
but no generalized ready-to-use solution, I tweaked the result to contain 
the name of an allegedly unpleasant place. 

## Background

As you might know, some Arduinos (Leonardo or Uno) can easily be used as USB-keyboard
with the Keyboard-library that is included in the IDE or with this 3rd-Party library:
https://github.com/NicoHood/HID
But when you use this with a host (e.g. a Windows PC) that is set to a non-US (e.g. German)
keyboard-layout you will soon find that not all of the simulated keystrokes yield the
expected result. This happens because both libraries use a fixed mapping for 7bit-ASCII
to HID-Codes of an US-Keyboard.

After some research I came to a similar conclusion as
RingoM (https://github.com/NicoHood/HID/issues/22#issuecomment-138728447):
A mapping from UTF-8 to HID-Codes is needed that can be switched depending
on the desired keyboard-layout. And since the code for handling UTF-8 strings
seems to be missing in the standard libraries, I had to implement that, too.

This repository contains the code that I came up with, but there are some caveats:
- I consider this a prototype / proof of concept
- currently it contains only EN_US and DE_DE keyboard-layouts
- currently the code is not really "organized" / object oriented
- I am an Arduino newbie
- My last experience with C++ was in 2005 with MSVC

So, proposals on how to improve the code are welcome!

To compile this, I used the Arduino IDE 1.6.11 and the "HID-Project" library 2.4.3

Update: A quick test with Arduino IDE 1.8.1 and "HID-Project" library 2.4.4 yielded
the same results for the provided sample code.


# akaub
- Android
- Keyboard
- Arduino
- USB
- Bluetooth

The akaub Arduino sketch uses the akuhell code to combine an Arduino that can be used as keyboard
(e.g. Leonardo) and an HC-06 Bluetooth-Module. With this device you can send keystrokes from an Android
smartphone via Bluetooth to a PC using a serial terminal app as if they were typed on a "normal" keyboard.
I used a tiny 32U4 Arduino that has a mikro USB connector and provides solder points for power and serial
lines. Since the 32U4 pins are 3.3V tolerant, I just had to connect RX0 of the Arduino to TX of the
BT-module (and of course VCC and GND - both componets use 5V as VCC) and it worked.  

The akuhell-files in this subdirectory are copies of the files in the akuhell directory
(it seems that the Arduino IDE is not able to include files from arbitrary directories).


Build Status:

[![Build status](https://ci.appveyor.com/api/projects/status/dn8aw7grml3f3ry4/branch/master?svg=true)](https://ci.appveyor.com/project/donid/akuhell/branch/master)

