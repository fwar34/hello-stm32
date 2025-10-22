################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/dht11.c \
../Core/Src/dma.c \
../Core/Src/ec11.c \
../Core/Src/gpio.c \
../Core/Src/main.c \
../Core/Src/my_spi1.c \
../Core/Src/process_command.c \
../Core/Src/process_key.c \
../Core/Src/process_render.c \
../Core/Src/protocol.c \
../Core/Src/protocol_statemachine.c \
../Core/Src/receive_buffer.c \
../Core/Src/spi.c \
../Core/Src/spinlock.c \
../Core/Src/st7735s.c \
../Core/Src/stm32f1xx_hal_msp.c \
../Core/Src/stm32f1xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f1xx.c \
../Core/Src/tim.c \
../Core/Src/timer3.c \
../Core/Src/usart.c \
../Core/Src/w25q64.c 

OBJS += \
./Core/Src/dht11.o \
./Core/Src/dma.o \
./Core/Src/ec11.o \
./Core/Src/gpio.o \
./Core/Src/main.o \
./Core/Src/my_spi1.o \
./Core/Src/process_command.o \
./Core/Src/process_key.o \
./Core/Src/process_render.o \
./Core/Src/protocol.o \
./Core/Src/protocol_statemachine.o \
./Core/Src/receive_buffer.o \
./Core/Src/spi.o \
./Core/Src/spinlock.o \
./Core/Src/st7735s.o \
./Core/Src/stm32f1xx_hal_msp.o \
./Core/Src/stm32f1xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f1xx.o \
./Core/Src/tim.o \
./Core/Src/timer3.o \
./Core/Src/usart.o \
./Core/Src/w25q64.o 

C_DEPS += \
./Core/Src/dht11.d \
./Core/Src/dma.d \
./Core/Src/ec11.d \
./Core/Src/gpio.d \
./Core/Src/main.d \
./Core/Src/my_spi1.d \
./Core/Src/process_command.d \
./Core/Src/process_key.d \
./Core/Src/process_render.d \
./Core/Src/protocol.d \
./Core/Src/protocol_statemachine.d \
./Core/Src/receive_buffer.d \
./Core/Src/spi.d \
./Core/Src/spinlock.d \
./Core/Src/st7735s.d \
./Core/Src/stm32f1xx_hal_msp.d \
./Core/Src/stm32f1xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f1xx.d \
./Core/Src/tim.d \
./Core/Src/timer3.d \
./Core/Src/usart.d \
./Core/Src/w25q64.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/dht11.cyclo ./Core/Src/dht11.d ./Core/Src/dht11.o ./Core/Src/dht11.su ./Core/Src/dma.cyclo ./Core/Src/dma.d ./Core/Src/dma.o ./Core/Src/dma.su ./Core/Src/ec11.cyclo ./Core/Src/ec11.d ./Core/Src/ec11.o ./Core/Src/ec11.su ./Core/Src/gpio.cyclo ./Core/Src/gpio.d ./Core/Src/gpio.o ./Core/Src/gpio.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/my_spi1.cyclo ./Core/Src/my_spi1.d ./Core/Src/my_spi1.o ./Core/Src/my_spi1.su ./Core/Src/process_command.cyclo ./Core/Src/process_command.d ./Core/Src/process_command.o ./Core/Src/process_command.su ./Core/Src/process_key.cyclo ./Core/Src/process_key.d ./Core/Src/process_key.o ./Core/Src/process_key.su ./Core/Src/process_render.cyclo ./Core/Src/process_render.d ./Core/Src/process_render.o ./Core/Src/process_render.su ./Core/Src/protocol.cyclo ./Core/Src/protocol.d ./Core/Src/protocol.o ./Core/Src/protocol.su ./Core/Src/protocol_statemachine.cyclo ./Core/Src/protocol_statemachine.d ./Core/Src/protocol_statemachine.o ./Core/Src/protocol_statemachine.su ./Core/Src/receive_buffer.cyclo ./Core/Src/receive_buffer.d ./Core/Src/receive_buffer.o ./Core/Src/receive_buffer.su ./Core/Src/spi.cyclo ./Core/Src/spi.d ./Core/Src/spi.o ./Core/Src/spi.su ./Core/Src/spinlock.cyclo ./Core/Src/spinlock.d ./Core/Src/spinlock.o ./Core/Src/spinlock.su ./Core/Src/st7735s.cyclo ./Core/Src/st7735s.d ./Core/Src/st7735s.o ./Core/Src/st7735s.su ./Core/Src/stm32f1xx_hal_msp.cyclo ./Core/Src/stm32f1xx_hal_msp.d ./Core/Src/stm32f1xx_hal_msp.o ./Core/Src/stm32f1xx_hal_msp.su ./Core/Src/stm32f1xx_it.cyclo ./Core/Src/stm32f1xx_it.d ./Core/Src/stm32f1xx_it.o ./Core/Src/stm32f1xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f1xx.cyclo ./Core/Src/system_stm32f1xx.d ./Core/Src/system_stm32f1xx.o ./Core/Src/system_stm32f1xx.su ./Core/Src/tim.cyclo ./Core/Src/tim.d ./Core/Src/tim.o ./Core/Src/tim.su ./Core/Src/timer3.cyclo ./Core/Src/timer3.d ./Core/Src/timer3.o ./Core/Src/timer3.su ./Core/Src/usart.cyclo ./Core/Src/usart.d ./Core/Src/usart.o ./Core/Src/usart.su ./Core/Src/w25q64.cyclo ./Core/Src/w25q64.d ./Core/Src/w25q64.o ./Core/Src/w25q64.su

.PHONY: clean-Core-2f-Src

