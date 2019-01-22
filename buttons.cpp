#include "buttons.h"

ButtonManager::ButtonManager(const PinOrganizer pins, Constants& constants)
{
	Pins = pins;
	CurrentConstants = &constants;//Side effects, I know, but this is a toy arduino example in pseudo cpp so I'm going with it
}

void ButtonManager::Update(float currentTime)
{
	if (currentTime - lastReadTime >= BUTTON_READ_INTERVAL)
	{
		if (digitalRead(Pins.IncrementBrightnessPin) == LOW)//The cheapo switchboard I'm using opens the circuit on press, you may need to switch to LOW for your application
		{
			CurrentConstants->maxBrightness = int(CurrentConstants->maxBrightness + 1) % 100;
		}
		lastReadTime = currentTime;
	}
}


