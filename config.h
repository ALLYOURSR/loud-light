#pragma once
constexpr int OUTPUT_INTERVAL = 100;
constexpr int PRINT_INTERVAL = 100;
constexpr int SMOOTHER_LENGTH = 150;
constexpr int BUTTON_READ_INTERVAL = 100;


//In other applications, I'll typically create config classes, like the one below.
//This way I can still keep all the config in one place, while using inheritance to create specialized configs 
//(e.g. for debug or different microcontrollers), and further organize configs into nested classes
class Config
{
public:
	int OutputInterval = 100;
	int PrintInterval = 100;
	int SmootherLength = 150;
	int ButtonReadInterval = 100;
};

