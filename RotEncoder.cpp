/*
  RotEncoder.cpp - Library for Rotary Encoder Forward and Reverse Motion detection and Push Button debounce without delay.
  Created by Pushkar H. Sheth, 9th June 2017.
  Released into the public domain.
*/

#include "RotEncoder.h"

RotEncoder::RotEncoder(int encPinA, int encPinB, int encButPin)
{
  pinMode (encPinA, INPUT_PULLUP);
  pinMode (encPinB, INPUT_PULLUP);
  attachInterrupt (digitalPinToInterrupt (encPinA), isr, CHANGE);
  pinMode (encButPin, INPUT_PULLUP); // setup the button pin

	oldButtonState = HIGH;  // assume switch open because of pull-up resistor
	debounceTime = 10;  // milliseconds
	
	buttonPressed = 0; // a flag variable  

}// end of RotEncoder

void RotEncoder::isr()
{
  if (digitalRead (encoderPinA))
    up = digitalRead (encoderPinB);
  else
    up = !digitalRead (encoderPinB);
  fired = true;
}  // end of isr


void RotEncoder::readEncoder()
{
  rotaryCount = 0;
  selected = 0;
  if (fired)
	{
    if (up)
      rotaryCount++;
    else
      rotaryCount--;
    fired = false;
    selected = rotaryCount ;


    return selected;
	} // end if fired
} // end of readEncoder

bool RotEncoder::buttonpressedfunc()
{
	byte buttonState = digitalRead(encButPin); 
  if (buttonState != oldButtonState){
    if (millis () - buttonPressTime >= debounceTime){ // debounce
      buttonPressTime = millis ();  // when we closed the switch 
      oldButtonState =  buttonState;  // remember for next time 
      if (buttonState == LOW){
        Serial.println ("Button closed"); // DEBUGGING: print that button has been closed
        buttonPressed = 1;
      }
      else {
        Serial.println ("Button opened"); // DEBUGGING: print that button has been opened
        buttonPressed = 0; 
      }  
    }  // end if debounce time up
  } // end of state change

}
