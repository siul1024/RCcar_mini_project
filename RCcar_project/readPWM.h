
#ifndef READPWM_H_
#define READPWM_H_

#define	THRpin 		18  		//(PWM0)BCM18
#define 	STRpin 		12 			//(PWM0)BCM12


typedef struct pwminfo
{
	uint32_t saveTick ;
	uint32_t period ;
	uint32_t high ;
	float fq;
	int pw;
	float dc;
}INFO;

extern uint32_t TICK_DIFF(INFO* info, uint32_t tick);
extern void Callback(int gpio, int level, uint32_t tick, INFO* myinfo);
extern void getfrequency(INFO* myinfo);
extern void getpulse_width(INFO* myinfo);
extern float getduty_cycle(uint32_t high, uint32_t period);

#endif
