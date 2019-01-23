#pragma once
#include <math.h>
#include "math_.h"

//Pretend this class is abstract. Not supported in this arduino c++
class Constants
{
public:
	float rawValue = 1;
	float increment = .01;//bit of 255 pulse width
	bool increasing = 1;

	float minMaxDecay = .01;//Adds or subtracts this value on every loop to ensure tight envelope

	float minBrightness = 0;
	float maxBrightness = 100;

	int rawMicVal = 0;
	float light_mic_val = 0;

	float mingap = .06;//In volts here, but watch out, converted in setup()

	float outputThresholdVolts = .1;//Increases apparent responsiveness by keeping light off during transient quiet parts

protected:
	Constants()
	{

	}
	virtual float Correction(float rawValue)
	{
		//This shouldn't need a definition with a proper abstract class, but the compiler complains.
		//Putting this here allows convenient adjustment for different brightness output curves
		Serial.println(rawValue);
	}

public:
	float WriteToLight(int pin, float rawPinValue, float minAmp, float maxAmp, float minBrightness, float maxBrightness);
};

class VacuumLampConstants : public Constants
{
public:
	VacuumLampConstants();

	float Correction(float rawValue);
};

class LEDConstants : public Constants
{
public:
	LEDConstants();

	float Correction(float rawValue);
};