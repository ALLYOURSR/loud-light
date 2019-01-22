#pragma once
//Just some helpful stuff







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

	int smootherLength = 150;
	float smootherArray[150];
	int smootherIndex = 0;

	float lastOutputTime = 0;
};

class RunConfig
{
public:
	//For readability, centralized location for misc constants
	int outputInterval = 100;//ms
	int printInterval = 100;//ms

};

void collect(float* arr, int len, int* currentIndex, float val)
{
	//Really just cycles the array
	arr[(*currentIndex)] = val;

	(*currentIndex) += 1;
	if ((*currentIndex) == len)
		(*currentIndex) = 0;

}