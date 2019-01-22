#pragma once
#include <WString.h>
#include <HardwareSerial.h>
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
	DebugLogger(float printInterval, bool enabled = true);

	void Update(float currentTime);

	void print(float val, int index);

	void print(String val, int index);

	void print(float val, String title, int index);

	void flushPrintBuffer();

	void clear();

};