#pragma once
#include "constants.h"
#include "utils.h"

class ButtonManager
{
public:
	PinOrganizer Pins;
	Constants* CurrentConstants;
	RunConfig Config;//Arduino language won't compile if member name is a type name?
	
private:
	float lastReadTime = 0;
	float readInterval = 100;

public:
	ButtonManager(const PinOrganizer pins, Constants& constants, const RunConfig runConfig)
	{
		Pins = pins;
		CurrentConstants = &constants;//Side effects, I know, but this is a toy arduino example in pseudo cpp so I'm going with it
		Config = runConfig;		
	}	

	void Update(float currentTime)
	{
		if (currentTime - lastReadTime >= readInterval)
		{
			if (digitalRead(Pins.IncrementBrightnessPin) == LOW)//The cheapo switchboard I'm using opens the circuit on press, you may need to switch to LOW for your application
			{
				CurrentConstants->maxBrightness = int(CurrentConstants->maxBrightness + 1) % 100;
			}
			lastReadTime = currentTime;
		}
	}


};