#pragma once
#include "config.h"

//This is just a cyclical array
class Smoother
{
private:
	int _smootherLength = SMOOTHER_LENGTH;
	float _smootherArray[SMOOTHER_LENGTH];
	int _smootherIndex = 0;

public:	
	void Collect(float val);

	float GetAverage();

};


//Alternative, resizable implementation, where I can show off my fancy pointer skills
//Of course, in real c++ I'd be using modern SmartPtr(s)
class Smoother_alt
{
private:
	int _smootherLength = SMOOTHER_LENGTH;
	float* _smootherArray;
	int _currentIndex = 0;

	//Sort of a hack. Instead of reallocating the array on resize, we save cycles and simply adjust
	//the bounds that are used to calculate the average. Downside is that max size is limited at compile time, though
	//we could add a true resize method.
	int _size;
	float* _start;
public:
	Smoother_alt(int size);

	void Collect(float val);

	float GetAverage();

	float GetSize();
	
	void SetSize(int size);

	~Smoother_alt();
};