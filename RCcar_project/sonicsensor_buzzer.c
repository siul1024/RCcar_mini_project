
#include <pigpio.h>
#include "sonicsensor_buzzer.h"

extern int checkthread;

float ECHOMEASURE()
{	float distance;
	unsigned long TX=0;
	unsigned long RX=0;
	unsigned long timeout=5000000;
	unsigned long Wait_time = gpioTick();

	gpioWrite(SONICTRIG,0);
	time_sleep(0.100);
	gpioWrite(SONICTRIG,1);
	time_sleep(0.010);
	gpioWrite(SONICTRIG,0);

	while(gpioRead(SONICECHO)==0 && (gpioTick()-Wait_time < timeout))
	{	if(gpioRead(SONICECHO) == 1) break;		}

	if((gpioTick() - Wait_time) > timeout)
	{	printf("--------------%d    %f  \n",gpioTick(), Wait_time);	}

	TX=gpioTick();

	while((gpioRead(SONICECHO)==1 && (gpioTick()-Wait_time)) < timeout)
	{	if(gpioRead(SONICECHO)==0) break;	}

	if((gpioTick() - Wait_time) > timeout)
	{	printf("--------------%d    %f  \n", gpioTick(), Wait_time);	}

	RX=gpioTick();

	distance = (RX - TX) / (float) 58.0;
	//printf("%4.2fcm\n", distance);

	return distance;
}


void* Warningbuzzer()
{	while(1)
	{	float distance = ECHOMEASURE();
		printf("------------------------------------------------------distance = %4.2f\n", distance);
		if(dist_stop < distance && distance < dist_buzzer)
		{	gpioPWM(BUZZER, 128);
			time_sleep(0.200);
			gpioPWM(BUZZER, 0);
		}
		if(0 < distance && distance <= dist_stop)
		{	gpioPWM(BUZZER, 128);
			time_sleep(0.100);
			gpioPWM(BUZZER, 0);
			checkthread = 1;
		}
		time_sleep(0.100);
	}
}
