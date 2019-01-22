#pragma once
#define PRINT_BUFFER_LENGTH 4

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