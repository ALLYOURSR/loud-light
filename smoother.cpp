#include "smoother.h"

void Smoother::Collect(float val)
{
	//Really just cycles the array
	_smootherArray[(_smootherIndex)] = val;
	
	(_smootherIndex) += 1;

	_smootherIndex = _smootherIndex % _smootherLength;

}

float Smoother::GetAverage()
{
	float sum = 0;

	for (int i = 0; i < _smootherLength; i++)
	{
		sum += _smootherArray[i];

	}
	//print(arr[6],0);
	return sum / _smootherLength;
}


//=====================================
//Smoother_alt
//=====================================
Smoother_alt::Smoother_alt(int size)
{
	_smootherArray = new float[SMOOTHER_LENGTH];
	this->_size = size;
}

void Smoother_alt::Collect(float val)
{
	//Really just cycles the array
	*(_start + _currentIndex) = val;
	_currentIndex = ++_currentIndex % _size;

}

Smoother_alt::~Smoother_alt()
{
	delete[] _smootherArray;
}

float Smoother_alt::GetSize()
{
	return _size;
}

void Smoother_alt::SetSize(int size)
{
	//Being able to set size at runtime is sort of overkill in this application, 
	//but a demonstration of useful getters/setters
	if (size > 0 && size <= _smootherLength)
	{
		_size = size;
		_start = &_smootherArray[_smootherLength - _size];
		_currentIndex = _currentIndex % _size;//This might disrupt the order of the array temporarily, but that's fine in this application
	}
	else if (size > _smootherLength)//Resize the underlying arrray
	{
		_smootherLength = size;
		_size = size;

		delete[] _smootherArray;//Free up now unused memory
		_smootherArray = new float[size];//Reallocate new array
	}
	else
	{
		//Normally I'd throw an exception, but I don't think there is a meaningful way to handle errors on an arduino.
	}
}

float Smoother_alt::GetAverage()
{
	float sum = 0;
	//Unfortunately, arduino cpp does not support iterators, so some custom pointer math here
	for (auto i = _start; i != (_smootherArray + _smootherLength); i++)
	{
		sum += *i;

	}
	//print(arr[6],0);
	return sum / _size;
}