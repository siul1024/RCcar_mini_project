#ifndef SONICSENSOR_BUZZER_H_
#define SONICSENSOR_BUZZER_H_

#define 	BUZZER 		13			//(PWM1)BCM13
#define 	SONICTRIG		6			//BCM6
#define 	SONICECHO		19			//BCM19
#define 	dist_stop		60
#define	dist_buzzer	100

extern float ECHOMEASURE();
extern void* Warningbuzzer();

#endif /* SONICSENSOR_BUZZER_H_ */
