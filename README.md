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
on the desired keyboard-layout.

This repository contains the code that I came up with, but there are some caveats:
- I consider this a prototype / proof of concept
- currently it contains only EN_US and DE_DE keyboard-layouts
- currently the code is not really "organized" / object oriented
- I am an Arduino newbie
- My last experience with C++ was in 2005 with MSVC

So, proposals on how to improve the code are welcome!

To compile this, I used the Arduino IDE 1.6.11 and the "HID-Project" library 2.4.3