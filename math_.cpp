// 
// 
// 

#include "math_.h"

float correction(float rawValue)
{
	//remaps 0-100 to a function on 0-255
	//[0,255] corresponds to valid DigitalWrite PWM duty cycle value range
	//The function is exponential to correct for human brightness perception
	return exp(.055452*rawValue) - 1;

}

float getAverage(float* arr, int len)
{
	float sum = 0;
	for (int i = 0; i < len; i++)
	{
		sum += arr[i];

	}
	//print(arr[6],0);
	return sum / len;
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

void writeToLight(int pin, float rawPinValue, float minAmp, float maxAmp, float minBrightness, float maxBrightness)
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