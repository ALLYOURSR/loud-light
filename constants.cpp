#include "constants.h"

float Constants::WriteToLight(int pin, float rawPinValue, float minAmp, float maxAmp, float minBrightness, float maxBrightness)
{
	//minBrightness and maxBrightness are the uncorrected brightness scale, start with 0, 100 and experiment
	//minAmp and maxAmp are the current time window average amplitude range, adjusted to keep the light responsive.

	//For LED:
	//0-100 seem to work

	//For the vac-lamp,
	//max brightness should be reduced to keep within range.
	//A value of 40 for max brightness seems to work remarkably well for 12" lamps 

	float normed = mapValue(rawPinValue, minAmp, maxAmp, minBrightness, maxBrightness);
	float out = Correction(normed);
	analogWrite(pin, out);
	return out;
}


LEDConstants::LEDConstants()
{
	maxBrightness = 100;
}

float LEDConstants::Correction(float rawValue)
{	//remaps 0-100 to a function on 0-255
	//[0,255] corresponds to valid DigitalWrite PWM duty cycle value range
	//The function is exponential to correct for human brightness perception
	//Hint: for rawValue=0, returns 0. For rawValue = 100, returns 255
	Serial.println(rawValue);
	return exp(.055452*rawValue) - 1;
}

VacuumLampConstants::VacuumLampConstants()
{
	maxBrightness = 100;//I noticed that as voltage V is increased from 0, vacuum lamps start at a point in the center
					   //and ionize progressively outwards, l(V) = aV + V_b approximately. I abuse the HV transformers that
					   //power the lamps, powering them with PWM identical to LEDs. I speculate PWM proportionally regulates 
					   //HV output V.

}

float VacuumLampConstants::Correction(float rawValue)
{
	//I've modified the correction function to have a more gradual come on and emphasize the partially lit effect.
	//If you plot this function and the one for LEDConstants, you'll see the difference!

	//Note: my arduino died before I could test this particular equation.
	Serial.println(rawValue);
	return .001*exp(.12453*rawValue) - 1;
}