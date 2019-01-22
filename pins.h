#pragma once
#include <Arduino.h>

class PinOrganizer
{
public:
	int PwmPin = 5;
	int MicPin = 0;

	int IncrementBrightnessPin = 12;
	int ACCRefPin = 8;//Just an extra power source for button logic

	//Unused currently
	int DecrementPin = 3;

	PinOrganizer();

};