################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../main.c \
../pca9685.c \
../readPWM.c \
../sonicsensor_buzzer.c 

OBJS += \
./main.o \
./pca9685.o \
./readPWM.o \
./sonicsensor_buzzer.o 

C_DEPS += \
./main.d \
./pca9685.d \
./readPWM.d \
./sonicsensor_buzzer.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	arm-linux-gnueabihf-gcc -I/usr/local/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


