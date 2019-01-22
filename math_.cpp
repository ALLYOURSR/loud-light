#include "math_.h"

float correction(float rawValue)
{	//remaps 0-100 to a function on 0-255
	//[0,255] corresponds to valid DigitalWrite PWM duty cycle value range
	//The function is exponential to correct for human brightness perception
	//Hint: for rawValue=0, returns 0. For rawValue = 100, returns 255

	return exp(.055452*rawValue) - 1;
}



float sample(int pin, int duration)
{
	//I'm pretty sure this blocks for int duration every time it works....heh
	//Need multithreading - looks fine to the human eye though. Just be careful with larger values
	//or the light could start to lag. Idea: implement delay?
	int startMillis = millis();
	unsigned int signalMax = 0;
	unsigned int signalMin = 1024;

	// collect data for 50 mS
	while (millis() - startMillis < duration)
	{
		int val = analogRead(0);
		if (val < 1024)  // toss out spurious readings
		{
			if (val > signalMax)
			{
				signalMax = val;  // save just the max levels
			}
			else if (val < signalMin)
			{
				signalMin = val;  // save just the min levels
			}
		}
	}

}

float readMicAmplitude(int pin)
{
	//256 represents min amplitude, 0 represents max. Boy was this a headache to figure out empirically
	return float(analogRead(pin) - 256);
}

int mapValue(int val)
{
	//maps 0-1023 to 0-100
	//I should probably do 0-99?
	float v = float(val);
	
	return 101.0 / 1024.0*(1023.0 - v);
	//(max2-min2)/(max1-min1)*v + min2-min1; max2 and min2 correspond to the output scale

}

int mapValue(int val, float min_, float max_)
{
	//maps [min_, max_] to [0, 100]
	float v(val);
	return (val - min_)*(100) / (max_ - min_);
}

int mapValue(int val, float min_, float max_, float newMin, float newMax)
{
	//maps [min_, max_] to [newMin, newMax]
	float v(val);
	return (val - min_)*(newMax-newMin) / (max_ - min_) + newMin;
}

float writeToLight(int pin, float rawPinValue, float minAmp, float maxAmp, float minBrightness, float maxBrightness)
{
	//minBrightness and maxBrightness are the uncorrected brightness scale, start with 0, 100 and experiment
	//minAmp and maxAmp are the current time window average amplitude range, adjusted to keep the light responsive.
	
	//For LED:
	//0-100 seem to work
	
	//For the vac-lamp,
	//max brightness should be reduced to keep within range.
	//A value of 40 for max brightness seems to work remarkably well for 12" lamps 
	
	float normed = mapValue(rawPinValue, minAmp, maxAmp, minBrightness, maxBrightness);
	float out = correction(normed);
	analogWrite(pin, out);
	return out;
}

float toVolts(int val)
{
	return float(val) * 5 / 1024;

}

float toVolts(float val)
{
	return val * 5 / 1024;

}

float fromVolts(float val)
{
	return val * 1024 / 5;
}