#include "logger.h"
#pragma once



DebugLogger::DebugLogger(float printInterval, bool enabled = true)
{
	Enabled = enabled;
	PrintInterval = printInterval;
}

void DebugLogger::Update(float currentTime)
{
	if (currentTime - lastPrintTime >= PrintInterval)
	{
		flushPrintBuffer();
		lastPrintTime = currentTime;

		Serial.println("printing");
	}
}

void DebugLogger::print(float val, int index)
{
	printBuffer[index] = String(val);
}

void DebugLogger::print(String val, int index)
{
	printBuffer[index] = val;
}

void DebugLogger::print(float val, String title, int index)
{
	printBuffer[index] = title + ": " + String(val);
}

void DebugLogger::flushPrintBuffer()
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

void DebugLogger::clear()
{
	for (int i = 0; i < printBufferLength; i++)
	{
		printBuffer[i] = "";
	}
}

