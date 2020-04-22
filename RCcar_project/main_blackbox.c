#include<stdio.h>
#include<wiringPi.h>
#include<stdlib.h>
#include<time.h>

#define VIV 3
#define BUZZER 23

char* timeToString(struct tm *t);

int main() {

	if (wiringPiSetup() == -1)
		return 1;
	pinMode(VIV, INPUT);	
	pinMode(BUZZER, OUTPUT);	

	struct tm *t;
	time_t timer;

	//printf("%s\n", timeToString(t));

	while (1) {
		int a = digitalRead(VIV);	

		printf("%d\n", a);
		digitalWrite(BUZZER, 0);		
		if (a == 0) {			

			digitalWrite(BUZZER, 1);		

			timer = time(NULL);   
			t = localtime(&timer); 
			char bash[40];
			sprintf(bash, "%s %s", "sh black.sh", timeToString(t));
			printf("%s\n",timeToString(t));
			printf("%s\n", bash);
			system(bash);	
			delay(100);
		}
		delay(10);
	}
}

char* timeToString(struct tm *t) {
	static char s[20];

	sprintf(s, "%04d-%02d-%02d %02d-%02d-%02d", t->tm_year + 1900,
			t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);

	return s;
}
