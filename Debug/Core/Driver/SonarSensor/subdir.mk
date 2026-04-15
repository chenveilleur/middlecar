################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/Driver/SonarSensor/SonarSensor.cpp 

OBJS += \
./Core/Driver/SonarSensor/SonarSensor.o 

CPP_DEPS += \
./Core/Driver/SonarSensor/SonarSensor.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Driver/SonarSensor/%.o Core/Driver/SonarSensor/%.su Core/Driver/SonarSensor/%.cyclo: ../Core/Driver/SonarSensor/%.cpp Core/Driver/SonarSensor/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m3 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Core/Driver/MotorDriver -I../Core/Driver/SonarSensor -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Driver-2f-SonarSensor

clean-Core-2f-Driver-2f-SonarSensor:
	-$(RM) ./Core/Driver/SonarSensor/SonarSensor.cyclo ./Core/Driver/SonarSensor/SonarSensor.d ./Core/Driver/SonarSensor/SonarSensor.o ./Core/Driver/SonarSensor/SonarSensor.su

.PHONY: clean-Core-2f-Driver-2f-SonarSensor

