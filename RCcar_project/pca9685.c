

#include "pca9685.h"



int pca9685setup(int i2cAddress, float freq)
{
	int handle = i2cOpen(1, ADDRESS, 0);
	if (handle < 0)
	{
		printf("failed i2cOpen... \n");
		exit(0);
	}

	int settings = i2cReadByteData(handle, MODE1) & 0x7f;
	int autoInc = settings | 0x20;

	i2cWriteByteData(handle, MODE1, autoInc);

	if (freq > 0)
	{
		pca9685PWMFreq(handle, freq);
	}
	return handle;
}


void pca9685PWMFreq(int handle, float freq)
{
	freq = (freq>1000 ? 1000 : (freq<40 ? 40 : freq));  //조건

	int prescale = (int)(25000000.0f / (4096*freq) - 0.5f);

	int settings = i2cReadByteData(handle, MODE1) & 0x7f;


	int restart = (settings & 0xEF) | RESTART;

	i2cWriteByteData(handle, MODE1, (settings | SLEEP)); //sleep
	i2cWriteByteData(handle, PRE_SCALE, prescale);	//prescale
	i2cWriteByteData(handle, MODE1, (settings & 0xEF));	//wake
	time_sleep(0.005);
	i2cWriteByteData(handle, MODE1, ((settings & 0xEF) | RESTART));  //restart
}

//set all CHANNELs back to default values(:full off = 1)
void pca9685PWMReset(int handle)
{
	i2cWriteWordData(handle, ALL_LED_ON_L, 0x0);
	i2cWriteWordData(handle, ALL_LED_ON_L + 2, 0x1000);
}

void pca9685PWMWrite(int handle, int channel, int on, int off)
{
	int reg = baseReg(channel);
	i2cWriteWordData(handle, reg,   (on & 0x0fff));
	i2cWriteWordData(handle, reg+2, (off & 0x0fff));
}

void pca9685PWMRead(int handle, int channel, int* on, int* off)
{
	int reg = baseReg(channel);
	if (on)
		*on = i2cReadWordData(handle, reg);
	if (off)
		*off = i2cReadWordData(handle, reg);
}

void pca9685FullOn(int handle, int channel, int tf)
{
	int reg = baseReg(channel) +1;  // LEDX_ON_H
	int state =  i2cReadByteData(handle, reg);

	state = tf ? (state | SLEEP) : (state & 0xEF);
	i2cWriteByteData(handle, reg, state);
	if(tf)
	pca9685FullOff(handle, channel, 0);
}

void pca9685FullOff(int handle, int channel, int tf)
{
	int reg = baseReg(channel) +3;  // LEDX_OFF_H
	int state =  i2cReadByteData(handle, reg);

	state = tf ? (state | SLEEP) : (state & 0xEF);
	i2cWriteByteData(handle, reg, state);
}

int baseReg(int channel)
{
	return (channel >= NumOfChannel ? ALL_LED_ON_L : LED0_ON_L + 4*channel);
}

void PWMWrite_d(int handle, int channel, int value)
{
	if (value >= 4096)
		pca9685FullOn(handle, channel, 1);
	else if (value>0)
		pca9685PWMWrite(handle, channel, 0, value);
	else
		pca9685FullOff(handle, channel, 1);
}

void OnOffWrite(int handle, int channel, int value)
{
	if (value)
		pca9685FullOn(handle, channel, 1);
	else
		pca9685FullOff(handle, channel, 1);
}

int OnRead(int handle, int channel)
{
	int on;
	pca9685PWMRead(handle, channel, 0, &on);

	return on;
}

int OffRead(int handle, int channel)
{
	int off;
	pca9685PWMRead(handle, channel, 0, &off);

	return off;
}

