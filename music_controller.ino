#include "math_.h"
#include "constants.h"
#include "utils.h"
#include "Buttons.h"

PinOrganizer pins = PinOrganizer();
RunVariables runVars = RunVariables();
RunConfig conf = RunConfig();
DebugLogger logger = DebugLogger(conf.printInterval, true);//pass true or remove false to enable


Constants c = LEDConstants();
//Constants c = VacuumLampConstants();

int lastOutputTime = 0;

void setup() {
	Serial.begin(74880);//Sets baud rate, enabling printing to computer when connected via USB

	pins.Initialize();

	logger.print("Hello", 0);
	logger.print("World", 1);
	logger.flushPrintBuffer();
	logger.clear();
}

void loop() {
	runVars.maxMicVal -= c.minMaxDecay;

	runVars.rawMicVal = abs(readMicAmplitude(pins.MicPin));
		
	collect(runVars.smootherArray, runVars.smootherLength, &runVars.smootherIndex, runVars.rawMicVal);
	int currentTime = millis();

	if (currentTime - runVars.lastAverageTime >= runVars.averageInterval)//Throttle to avoid lag. Not sure if this is necessary.
	{
		runVars.smoothedMicVal = getAverage(runVars.smootherArray, runVars.smootherLength);
		runVars.lastAverageTime = currentTime;
	}		

	
	if (currentTime - lastOutputTime >= conf.outputInterval)
	{
		if (runVars.smoothedMicVal > runVars.maxMicVal)
			runVars.maxMicVal = runVars.smoothedMicVal;

		if (runVars.maxMicVal - runVars.minMicVal < c.mingap)
			runVars.maxMicVal = runVars.minMicVal + c.mingap;

		writeToLight(pins.PwmPin, runVars.smoothedMicVal, runVars.minMicVal, runVars.maxMicVal, c.minBrightness, c.maxBrightness);
		writeToLight(LED_BUILTIN, runVars.smoothedMicVal, runVars.minMicVal, runVars.maxMicVal, c.minBrightness, c.maxBrightness);
		runVars.lastOutputTime = currentTime;
		lastOutputTime = currentTime;		
	}
	
	logger.Update(currentTime);

	
}
