################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../L1_FreeRTOS/portable/run_time_stats.c 

OBJS += \
./L1_FreeRTOS/portable/run_time_stats.o 

C_DEPS += \
./L1_FreeRTOS/portable/run_time_stats.d 


# Each subdirectory must supply rules for building sources it contributes
L1_FreeRTOS/portable/%.o: ../L1_FreeRTOS/portable/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Os -fmessage-length=0 -ffunction-sections -fdata-sections -Wall -Wshadow -Wlogical-op -Wfloat-equal -DBUILD_CFG_MPU=0 -I"C:\SJSU_Dev\SJSU_Dev\projects\SnF\BLE" -I"C:\SJSU_Dev\SJSU_Dev\projects\SnF\BLE\newlib" -I"C:\SJSU_Dev\SJSU_Dev\projects\SnF\BLE\L0_LowLevel" -I"C:\SJSU_Dev\SJSU_Dev\projects\SnF\BLE\L1_FreeRTOS" -I"C:\SJSU_Dev\SJSU_Dev\projects\SnF\BLE\L1_FreeRTOS\include" -I"C:\SJSU_Dev\SJSU_Dev\projects\SnF\BLE\L1_FreeRTOS\portable\no_mpu" -I"C:\SJSU_Dev\SJSU_Dev\projects\SnF\BLE\L2_Drivers" -I"C:\SJSU_Dev\SJSU_Dev\projects\SnF\BLE\L2_Drivers\base" -I"C:\SJSU_Dev\SJSU_Dev\projects\SnF\BLE\L3_Utils" -I"C:\SJSU_Dev\SJSU_Dev\projects\SnF\BLE\L3_Utils\tlm" -I"C:\SJSU_Dev\SJSU_Dev\projects\SnF\BLE\L4_IO" -I"C:\SJSU_Dev\SJSU_Dev\projects\SnF\BLE\L4_IO\fat" -I"C:\SJSU_Dev\SJSU_Dev\projects\SnF\BLE\L4_IO\wireless" -I"C:\SJSU_Dev\SJSU_Dev\projects\SnF\BLE\L5_Application" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


