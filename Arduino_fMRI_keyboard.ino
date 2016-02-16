/*
  KeyboardAndMouseControl

 Controls the mouse from five pushbuttons on an Arduino Leonardo, Micro or Due.

 Hardware:
 * 5 pushbuttons attached to D2, D3, D4, D5, D6

 The mouse movement is always relative. This sketch reads
 four pushbuttons, and uses them to set the movement of the mouse.

 WARNING:  When you use the Mouse.move() command, the Arduino takes
 over your mouse!  Make sure you have control before you use the mouse commands.

 created 15 Mar 2012
 modified 27 Mar 2012
 by Tom Igoe

 this code is in the public domain

 */

#include "Keyboard.h"
#include "Mouse.h"

// set pin numbers for the five buttons:
const int upButton = 2;
const int downButton = 3;
const int leftButton = 4;
const int rightButton = 5;


void setup() { // initialize the buttons' inputs:
  pinMode(upButton, INPUT);
  pinMode(downButton, INPUT);
  pinMode(leftButton, INPUT);
  pinMode(rightButton, INPUT);
  Keyboard.begin();
}

void loop() {

  // use the pushbuttons to control the keyboard:
  if (digitalRead(upButton) == HIGH) {
    Keyboard.press('w');
  } else { Keyboard.release('w');}
  if (digitalRead(downButton) == HIGH) {
    Keyboard.press('a');
  } else { Keyboard.release('a');}
  if (digitalRead(leftButton) == HIGH) {
    Keyboard.press('s');
  } else { Keyboard.release('s');}
  if (digitalRead(rightButton) == HIGH) {
    Keyboard.press('d');
  } else { Keyboard.release('d');}
  delay(31);
}
