#pragma once

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

float correction(float rawValue);

float readMicAmplitude(int pin);

int mapValue(int val);

int mapValue(int val, float min_, float max_);

int mapValue(int val, float min_, float max_, float newMin, float newMax);

float writeToLight(int pin, float rawPinValue, float minAmp, float maxAmp, float minBrightness, float maxBrightness);

float toVolts(int val);

float toVolts(float val);

float fromVolts(float val);


