#include "constants.h"


VacuumLampConstants::VacuumLampConstants()
{
	maxBrightness = 40;//I noticed that as voltage V is increased from 0, vacuum lamps start at a point in the center
					   //and ionize progressively outwards, l(V) = aV + V_b approximately. I abuse the HV transformers that
					   //power the lamps, powering them with PWM identical to LEDs. I speculate PWM proportionally regulates 
					   //HV output V.
}

LEDConstants::LEDConstants()
{
	maxBrightness = 100;
}