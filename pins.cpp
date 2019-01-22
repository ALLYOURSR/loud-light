#include "pins.h"
PinOrganizer::PinOrganizer()
{
	pinMode(PwmPin, OUTPUT);
	pinMode(MicPin, OUTPUT);

	pinMode(ACCRefPin, OUTPUT);
	digitalWrite(ACCRefPin, HIGH);

	pinMode(IncrementBrightnessPin, INPUT);
}