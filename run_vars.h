#pragma once
class RunVariables
{
	//For readability, centralized location for misc values
public:
	int lastAverageTime = 0;
	int averageInterval = 25;

	float smoothedMicVal = 0;

	float minMicVal = 0;
	float maxMicVal = 0;

	int rawMicVal = 0;
	float light_mic_val = 0;

	float lastOutputTime = 0;
};