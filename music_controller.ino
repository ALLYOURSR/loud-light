#include "math_.h"
#include "constants.h"
#include "Buttons.h"
#include "pins.h"
#include "logger.h"
#include "run_vars.h"
#include "smoother.h"

PinOrganizer pins = PinOrganizer();
RunVariables runVars = RunVariables();
DebugLogger logger = DebugLogger(PRINT_INTERVAL, true);//pass true or remove false to enable
Smoother smoother = Smoother();
Constants* c;


int lastOutputTime = 0;

void setup() {
	Serial.begin(74880);//Sets baud rate, enabling printing to computer when connected via USB	

	if (LIGHT_TYPE == 0)
		c = &LEDConstants();
	else
		c = &VacuumLampConstants();
		
	ButtonManager bm = ButtonManager(pins, *c);
	logger.print("Hello", 0);
	logger.print("World", 1);
	logger.flushPrintBuffer();
	logger.clear();
}

void loop() {
	runVars.maxMicVal -= c->minMaxDecay;

	runVars.rawMicVal = abs(readMicAmplitude(pins.MicPin));

	smoother.Collect(runVars.rawMicVal);
	
	int currentTime = millis();

	if (currentTime - runVars.lastAverageTime >= runVars.averageInterval)//Throttle to avoid lag. Not sure if this is necessary, but summing over a potentially large array might be relatively expensive for the little Arduino that could.
	{
		//bm.Update(currentTime);
		runVars.smoothedMicVal = smoother.GetAverage();
		runVars.lastAverageTime = currentTime;
	}


	if (currentTime - lastOutputTime >= OUTPUT_INTERVAL)
	{
		if (runVars.smoothedMicVal > runVars.maxMicVal)
			runVars.maxMicVal = runVars.smoothedMicVal;

		if (runVars.maxMicVal - runVars.minMicVal < c->mingap)
			runVars.maxMicVal = runVars.minMicVal + c->mingap;

		float val = c->WriteToLight(pins.PwmPin, runVars.smoothedMicVal, runVars.minMicVal, runVars.maxMicVal, c->minBrightness, c->maxBrightness);
		analogWrite(LED_BUILTIN, val);
		runVars.lastOutputTime = currentTime;
		lastOutputTime = currentTime;

	}

	logger.Update(currentTime);
}
