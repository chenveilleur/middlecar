################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/Driver/MotorDriver/MotorDriver.cpp 

OBJS += \
./Core/Driver/MotorDriver/MotorDriver.o 

CPP_DEPS += \
./Core/Driver/MotorDriver/MotorDriver.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Driver/MotorDriver/%.o Core/Driver/MotorDriver/%.su Core/Driver/MotorDriver/%.cyclo: ../Core/Driver/MotorDriver/%.cpp Core/Driver/MotorDriver/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m3 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Core/Driver/MotorDriver -I../Core/Driver/SonarSensor -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Driver-2f-MotorDriver

clean-Core-2f-Driver-2f-MotorDriver:
	-$(RM) ./Core/Driver/MotorDriver/MotorDriver.cyclo ./Core/Driver/MotorDriver/MotorDriver.d ./Core/Driver/MotorDriver/MotorDriver.o ./Core/Driver/MotorDriver/MotorDriver.su

.PHONY: clean-Core-2f-Driver-2f-MotorDriver

