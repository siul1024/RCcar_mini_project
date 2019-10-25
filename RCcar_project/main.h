
#ifndef MAIN_H_
#define MAIN_H_


#define	weighting 		0.8 	//0 ~ 1
#define 	MAX_PWM 		4096
#define	time_slow		7
#define	decstep_slow	5
#define	decstep		4

/*** pin ***/
#define 	LIGHT_R		10 //BCM10//
#define 	LIGHT_Y		27 //BCM27

extern int saveTHRpw;
extern int saveSTRpw;



int calcTicks(float impulseMs, int hertz)
{
	float cycleMs = 1000.0f / hertz;
	return (int)(MAX_PWM * impulseMs / cycleMs + 0.5f);
}

int THRcalibration(int pw, float step)
{
	int result = (weighting * pw) + ((1-weighting) * saveTHRpw);
	if(pw > 2000) 				result = 2000;
	if(pw < 1000) 				result = 1000;
	if(pw < 1550 && pw > 1450)	result = 1500;
	saveTHRpw = result;
	result = (pw-1500)/step + 1500;
	printf("thrpulse = %d\n\n", result);
	return result;
}


int STRcalibration(int pw)
{
	int result = (weighting * pw) + ((1-weighting) * saveSTRpw);
	if(pw > 2000) 				result = 2000;
	if(pw < 1000) 				result = 1000;
	if(pw < 1550 && pw > 1450)	result = 1500;
	saveSTRpw = result;
	//printf("strpulse = %d\n\n", result);
	return result;
}












#endif /* MAIN_H_ */
