/*
  RotEncoder.h - Library for Rotary Encoder Forward and Reverse Motion detection and debounce without delay.
  Created by Pushkar H. Sheth, 9th June 2017.
  Released into the public domain.
*/

#ifndef RotEncoder_h
#define RotEncoder_h

class RotEncoder
{
  public:
    RotEncoder(const byte encPinA, const byte encPinB, const byte encButPin);
    void isr();
	int readEncoder();
    bool buttonpressedfunc();
	volatile bool fired;
	int selected;
  private:
	volatile bool up;
	byte oldButtonState;  // assume switch open because of pull-up resistor
	const unsigned long debounceTime;  // milliseconds
	unsigned long buttonPressTime;  // when the switch last changed state
	boolean buttonPressed; // a flag variable
	
	static long rotaryCount;
};

#endif