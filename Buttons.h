#pragma once
#include "constants.h"
#include "utils.h"

class ButtonManager
{
public:
	PinOrganizer Pins;
	Constants* CurrentConstants;
	RunConfig Config;//Arduino language won't compile if member name is a type name?
	
	ButtonManager(PinOrganizer pins, Constants constants, RunConfig runConfig)
	{
		Pins = pins;
		CurrentConstants = &constants;
		Config = runConfig;		
	}	

	void Update(float currentTime)
	{
		if (digitalRead(Pins.IncrementBrightnessPin) == HIGH)
		{
			CurrentConstants->maxBrightness = int(CurrentConstants->maxBrightness + 10) % 100;
		}
	}


};