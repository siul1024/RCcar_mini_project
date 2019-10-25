
#ifndef PCA9685_H_
#define PCA9685_H_

#define ADDRESS 0x6f
#define NumOfChannel 16

/**registers**/
#define	MODE1          0x00
#define	MODE2          0x01
#define	SUBADR1        0x02
#define	SUBADR2        0x03
#define	SUBADR3        0x04
#define	PRE_SCALE      0xFE
#define	LED0_ON_L      0x06
#define	LED0_ON_H      0x07
#define	LED0_OFF_L     0x08
#define	LED0_OFF_H     0x09

#define	ALL_LED_ON_L   0xFA
#define	ALL_LED_ON_H   0xFB
#define	ALL_LED_OFF_L  0xFC
#define	ALL_LED_OFF_H  0xFD

#define	SLEEP          0x10
#define 	RESTART        0x80

#define 	HERTZ 			 50


extern int pca9685setup(int i2cAddress, float freq);
extern void pca9685PWMFreq(int handle, float freq);
extern void pca9685PWMReset(int handle);
extern void pca9685PWMWrite(int handle, int channel, int on, int off);
extern void pca9685PWMRead(int handle, int channel, int* on, int* off);
extern void pca9685FullOn(int handle, int channel, int tf);
extern void pca9685FullOff(int handle, int channel, int tf);
extern int baseReg(int channel);
extern void PWMWrite_d(int handle, int channel, int value);
extern void OnOffWrite(int handle, int channel, int value);
extern int OnRead(int handle, int channel);
extern int OffRead(int handle, int channel);

#endif /* PCA9685_H_ */
