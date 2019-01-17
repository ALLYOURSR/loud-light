int mapValue(int val)
{
	//maps 0-1023 to 0-100
	//I should probably do 0-99
	float v = float(val);
	//Serial.print(v);
	return 101.0 / 1024.0*(1023.0 - v);
	//(max2-min2)/(max1-min1)*v + min2-min1; max2 and min2 correspond to the output scale

}

int mapValue(int val, float min_, float max_)
{
	//maps [min_, max_] to [0, 100]
	float v = val;
	return (val - min_)*(100) / (max_ - min_);

	//return 100.0/(max_-min_)*(1023-v) -min_;
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

float correction(float rawValue)
{
	//remaps 0-100 to a function on 0-255 to correct for perception of brightness
	return exp(.055452*rawValue) - 1;

}