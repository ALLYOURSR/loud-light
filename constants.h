#pragma once

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
};

class VacuumLampConstants : public Constants
{
public:
	VacuumLampConstants();
};

class LEDConstants : public Constants
{
public:
	LEDConstants();
};