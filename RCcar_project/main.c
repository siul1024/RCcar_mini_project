#include <stdio.h>
#include <stdlib.h>
#include <pigpio.h>
#include <pthread.h>

#include "main.h"
#include "readPWM.h"
#include "pca9685.h"
#include "sonicsensor_buzzer.h"


int checkthread = 0;

int saveTHRpw = 1500;
int saveSTRpw = 1500;


int main (void)
{
	INFO* STRinfo = malloc(sizeof(INFO));
	INFO* THRinfo = malloc(sizeof(INFO));
	//라이브러리 초기화, 성공시 버전반환
	if (gpioInitialise() < 0)
	{   printf(" pigpio initialisation failed.\n");
	    return 0;
	}

	//핀모드 설정
	gpioSetMode(THRpin, PI_INPUT);
	gpioSetMode(STRpin, PI_INPUT);
	gpioSetMode(BUZZER, PI_OUTPUT);
	gpioSetMode(SONICTRIG, PI_OUTPUT);
	gpioSetMode(SONICECHO, PI_INPUT);
	gpioSetMode(LIGHT_R, PI_OUTPUT);
	gpioSetMode(LIGHT_Y, PI_OUTPUT);

	gpioSetISRFuncEx(STRpin, EITHER_EDGE, 1, Callback, STRinfo);
	gpioSetISRFuncEx(THRpin, EITHER_EDGE, 1, Callback, THRinfo);

	pthread_t* p1 = gpioStartThread(Warningbuzzer, NULL);

	while(1)
	{
		int handle = pca9685setup(ADDRESS, HERTZ);
		if (handle < 0)
				printf("Error: i2cOpen\n");
		time_sleep(0.005);

		getpulse_width(STRinfo);
		getpulse_width(THRinfo);
		pca9685PWMReset(handle);
		THRinfo->pw = THRcalibration(THRinfo->pw, decstep);
		STRinfo->pw = STRcalibration(STRinfo->pw);

		if(checkthread == 1)
		{	clock_t t1, t2;

			pca9685PWMReset(handle);
			PWMWrite_d(handle, 1, calcTicks(1.55, HERTZ));	//back
			time_sleep(0.3);										//delay
			PWMWrite_d(handle, 1, calcTicks(1.5, HERTZ));		//stop
			i2cClose(handle);
			gpioWrite(LIGHT_R, 1);
			time_sleep(3);

			gpioWrite(LIGHT_R, 0);
			gpioWrite(LIGHT_Y, 1);
			t1 = gpioTick();
			while(1)
			{
				handle = pca9685setup(ADDRESS, 50);
				if (handle < 0)
					printf("Error: i2cOpen\n");
				time_sleep(0.005);

				getpulse_width(STRinfo);
				getpulse_width(THRinfo);

				pca9685PWMReset(handle);
				THRinfo->pw = THRcalibration(THRinfo->pw, decstep_slow);
				STRinfo->pw = STRcalibration(STRinfo->pw);
				PWMWrite_d(handle, 0, calcTicks(STRinfo->pw/1000.0, HERTZ));
				PWMWrite_d(handle, 1, calcTicks(THRinfo->pw/1000.0, HERTZ));
				time_sleep(0.005);
				i2cClose(handle);

				t2 = gpioTick();
				if ((t2-t1) > ( time_slow * CLOCKS_PER_SEC)) break ;
			}
			gpioWrite(LIGHT_Y, 0);
			checkthread = 0;

			handle = pca9685setup(ADDRESS, 50);
			if (handle < 0)
				printf("Error: i2cOpen\n");
			time_sleep(0.005);
		}

		PWMWrite_d(handle, 0, calcTicks(STRinfo->pw/1000.0, HERTZ));
		PWMWrite_d(handle, 1, calcTicks(THRinfo->pw/1000.0, HERTZ));

		i2cClose(handle);
		time_sleep(0.005);
	}
	//종료
	gpioStopThread(p1); time_sleep(0.3);
	gpioTerminate();
	free(STRinfo); free(THRinfo);
	return 0 ;
}




