#pragma once
//Just some helpful stuff

#define PRINT_BUFFER_LENGTH 4
#define SMOOTHER_LENGTH 150

class DebugLogger
{
	//Clean ish (i.e. hack) way to print additional material
	//Prints each element of printBuffer into a corresponding column specified by index.
	//Remember to call flushPrintBuffer() to actually print to the screen!
public:
	
	float PrintInterval;
	int lastPrintTime = 0;
	bool Enabled;
	
private:
	int printBufferLength = PRINT_BUFFER_LENGTH;
	String printBuffer[PRINT_BUFFER_LENGTH];

public:
	DebugLogger(float printInterval, bool enabled = true)
	{
		Enabled = enabled;
		PrintInterval = printInterval;
	}

	void Update(float currentTime)
	{
		if (currentTime - lastPrintTime >= PrintInterval)
		{
			flushPrintBuffer();
			lastPrintTime = currentTime;
		}
	}

	void print(float val, int index)
	{
			printBuffer[index] = String(val);
	}

	void print(String val, int index)
	{
			printBuffer[index] = val;
	}

	void print(float val, String title, int index)
	{
		printBuffer[index] = title + ": " + String(val);
	}

	void flushPrintBuffer()
	{
		if (Enabled)
		{
			String output = " -- ";
			for (int i = 0; i < printBufferLength; i++)
			{
				output += printBuffer[i] + " -- ";
			}
			Serial.println(output);
		}
	}

	void clear()
	{
		for (int i = 0; i < printBufferLength; i++)
		{
			printBuffer[i] = "";
		}
	}
	
};

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

class RunVariables
{
	//For readability, centralized location for misc values
public:
	int lastAverageTime = 0;
	int averageInterval = 1;

	float smoothedMicVal = 0;

	float minMicVal = 0;
	float maxMicVal = 0;

	int rawMicVal = 0;
	float light_mic_val = 0;

	int smootherLength = SMOOTHER_LENGTH;
	float smootherArray[SMOOTHER_LENGTH];
	int smootherIndex = 0;

	float lastOutputTime = 0;
};

class RunConfig
{
public:
	//For readability, centralized location for misc constants
	int outputInterval = 1;//ms
	int printInterval = 100;//ms

};

void collect(float* arr, int len, int* currentIndex, float val)
{
	//Really just cycles a circular array
	arr[(*currentIndex)] = val;

	(*currentIndex) += 1;
	if ((*currentIndex) == len)
		(*currentIndex) = 0;

}