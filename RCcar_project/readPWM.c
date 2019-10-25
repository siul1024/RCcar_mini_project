
#include <pigpio.h>
#include "readPWM.h"

uint32_t TICK_DIFF(INFO* info, uint32_t tick)
{	uint32_t tickdiff;
	tickdiff = tick - (info->saveTick);
	(info->saveTick) = tick;
	return tickdiff;
}

void Callback(int gpio, int level, uint32_t tick, INFO* myinfo)
{	if(level == 1)
	{	uint32_t t = TICK_DIFF(myinfo, tick);
		myinfo->period = t;
	}
	if(level == 0)
	{	uint32_t t = TICK_DIFF(myinfo, tick);
		myinfo->high = t;
	}
}

void getfrequency(INFO* myinfo)
{	int result;

	if(myinfo->period != 0)
		result = 1000000 / myinfo->period;
	else result = 0;

	myinfo->fq = result;
}

void getpulse_width(INFO* myinfo)
{
	 myinfo->pw = myinfo->high;
}

float getduty_cycle(uint32_t high, uint32_t period)
{	float result;
	if(period != 0)
	{
		result = (float) 100.0 * high / period;
	}
	return result;
}
