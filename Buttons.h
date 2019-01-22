#pragma once
#include "constants.h"
#include "pins.h"
#include "config.h"
#include <Arduino.h>

class ButtonManager
{
public:
	PinOrganizer Pins;
	Constants* CurrentConstants;
	
private:
	float lastReadTime = 0;

public:
	ButtonManager(const PinOrganizer pins, Constants& constants);

	void Update(float currentTime);


};