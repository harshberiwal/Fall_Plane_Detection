################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/Fall_Plane_detection.c \
../source/I2C.c \
../source/SysTick.c \
../source/accelerometer.c \
../source/cbfifo.c \
../source/command_processor.c \
../source/gpio.c \
../source/mtb.c \
../source/semihost_hardfault.c \
../source/test_cbfifo.c \
../source/uart.c 

C_DEPS += \
./source/Fall_Plane_detection.d \
./source/I2C.d \
./source/SysTick.d \
./source/accelerometer.d \
./source/cbfifo.d \
./source/command_processor.d \
./source/gpio.d \
./source/mtb.d \
./source/semihost_hardfault.d \
./source/test_cbfifo.d \
./source/uart.d 

OBJS += \
./source/Fall_Plane_detection.o \
./source/I2C.o \
./source/SysTick.o \
./source/accelerometer.o \
./source/cbfifo.o \
./source/command_processor.o \
./source/gpio.o \
./source/mtb.o \
./source/semihost_hardfault.o \
./source/test_cbfifo.o \
./source/uart.o 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=1 -DPRINTF_FLOAT_ENABLE=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"D:\CU BOULDER\Coursework\Sem 1 - PES\Fall_plane_detection\board" -I"D:\CU BOULDER\Coursework\Sem 1 - PES\Fall_plane_detection\source" -I"D:\CU BOULDER\Coursework\Sem 1 - PES\Fall_plane_detection" -I"D:\CU BOULDER\Coursework\Sem 1 - PES\Fall_plane_detection\drivers" -I"D:\CU BOULDER\Coursework\Sem 1 - PES\Fall_plane_detection\CMSIS" -I"D:\CU BOULDER\Coursework\Sem 1 - PES\Fall_plane_detection\utilities" -I"D:\CU BOULDER\Coursework\Sem 1 - PES\Fall_plane_detection\startup" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source

clean-source:
	-$(RM) ./source/Fall_Plane_detection.d ./source/Fall_Plane_detection.o ./source/I2C.d ./source/I2C.o ./source/SysTick.d ./source/SysTick.o ./source/accelerometer.d ./source/accelerometer.o ./source/cbfifo.d ./source/cbfifo.o ./source/command_processor.d ./source/command_processor.o ./source/gpio.d ./source/gpio.o ./source/mtb.d ./source/mtb.o ./source/semihost_hardfault.d ./source/semihost_hardfault.o ./source/test_cbfifo.d ./source/test_cbfifo.o ./source/uart.d ./source/uart.o

.PHONY: clean-source

