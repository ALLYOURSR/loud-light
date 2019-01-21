#pragma once

class PinOrganizer
{
public:

	int PwmPin = 5;
	int MicPin = 0;

	int IncrementBrightnessPin = 12;
	int AccPowerPin = 8;

	//Unused currently
	int DecrementPin = 3;

	void Initialize()
	{
		pinMode(PwmPin, OUTPUT);
		pinMode(MicPin, OUTPUT);

		pinMode(AccPowerPin, OUTPUT);
		digitalWrite(AccPowerPin, HIGH);

		pinMode(IncrementBrightnessPin, INPUT);
	}

};