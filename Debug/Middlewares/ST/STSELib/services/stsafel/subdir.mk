################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/ST/STSELib/services/stsafel/stsafel_commands.c \
../Middlewares/ST/STSELib/services/stsafel/stsafel_data_partition.c \
../Middlewares/ST/STSELib/services/stsafel/stsafel_device_info.c \
../Middlewares/ST/STSELib/services/stsafel/stsafel_ecc.c \
../Middlewares/ST/STSELib/services/stsafel/stsafel_echo.c \
../Middlewares/ST/STSELib/services/stsafel/stsafel_frame_transfer.c \
../Middlewares/ST/STSELib/services/stsafel/stsafel_low_power.c \
../Middlewares/ST/STSELib/services/stsafel/stsafel_reset.c \
../Middlewares/ST/STSELib/services/stsafel/stsafel_timings.c 

OBJS += \
./Middlewares/ST/STSELib/services/stsafel/stsafel_commands.o \
./Middlewares/ST/STSELib/services/stsafel/stsafel_data_partition.o \
./Middlewares/ST/STSELib/services/stsafel/stsafel_device_info.o \
./Middlewares/ST/STSELib/services/stsafel/stsafel_ecc.o \
./Middlewares/ST/STSELib/services/stsafel/stsafel_echo.o \
./Middlewares/ST/STSELib/services/stsafel/stsafel_frame_transfer.o \
./Middlewares/ST/STSELib/services/stsafel/stsafel_low_power.o \
./Middlewares/ST/STSELib/services/stsafel/stsafel_reset.o \
./Middlewares/ST/STSELib/services/stsafel/stsafel_timings.o 

C_DEPS += \
./Middlewares/ST/STSELib/services/stsafel/stsafel_commands.d \
./Middlewares/ST/STSELib/services/stsafel/stsafel_data_partition.d \
./Middlewares/ST/STSELib/services/stsafel/stsafel_device_info.d \
./Middlewares/ST/STSELib/services/stsafel/stsafel_ecc.d \
./Middlewares/ST/STSELib/services/stsafel/stsafel_echo.d \
./Middlewares/ST/STSELib/services/stsafel/stsafel_frame_transfer.d \
./Middlewares/ST/STSELib/services/stsafel/stsafel_low_power.d \
./Middlewares/ST/STSELib/services/stsafel/stsafel_reset.d \
./Middlewares/ST/STSELib/services/stsafel/stsafel_timings.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/ST/STSELib/services/stsafel/%.o Middlewares/ST/STSELib/services/stsafel/%.su Middlewares/ST/STSELib/services/stsafel/%.cyclo: ../Middlewares/ST/STSELib/services/stsafel/%.c Middlewares/ST/STSELib/services/stsafel/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../X-CUBE-STSE01/App -I../X-CUBE-STSE01/Target -I../Drivers/BSP/STM32F4xx_Nucleo -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/ST/STSELib/api/ -I../Middlewares/ST/STSELib/certificate/ -I../Middlewares/ST/STSELib/core/ -I../Middlewares/ST/STSELib/services/ -I../Middlewares/ST/STSELib/services/stsafea/ -I../Middlewares/ST/STSELib/services/stsafel/ -I../Middlewares/ST/STSELib -I../Middlewares/ST/STSELib/api -I../Middlewares/ST/STSELib/certificate -I../Middlewares/ST/STSELib/core -I../Middlewares/ST/STSELib/services/stsafea -I../Middlewares/ST/STSELib/services/stsafel -I../Drivers/BSP/ESE02A1 -I../Drivers/BSP/Components/STSAFEL010 -I../Middlewares/ST/STM32_Cryptographic/_htmresc/ -I../Middlewares/ST/STM32_Cryptographic/include/ -I../Middlewares/ST/STM32_Cryptographic/interface/ -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/ -I../Middlewares/ST/STM32_Cryptographic/lib/ -I../Middlewares/ST/STM32_Cryptographic/include/cipher/ -I../Middlewares/ST/STM32_Cryptographic/include/drbg/ -I../Middlewares/ST/STM32_Cryptographic/include/ecc/ -I../Middlewares/ST/STM32_Cryptographic/include/hash/ -I../Middlewares/ST/STM32_Cryptographic/include/mac/ -I../Middlewares/ST/STM32_Cryptographic/include/rsa/ -I../Middlewares/ST/STM32_Cryptographic/include/utils/ -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/include/ -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/src/ -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/include/cipher/ -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/include/drbg/ -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/include/ecc/ -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/include/hash/ -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/include/mac/ -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/include/membuf/ -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/include/rsa/ -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/src/cipher/ -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/src/drbg/ -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/src/ecc/ -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/src/hash/ -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/src/mac/ -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/src/membuf/ -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/src/rsa/ -I../Middlewares/ST/STM32_Cryptographic/include -I../Middlewares/ST/STM32_Cryptographic/include/cipher -I../Middlewares/ST/STM32_Cryptographic/include/drbg -I../Middlewares/ST/STM32_Cryptographic/include/ecc -I../Middlewares/ST/STM32_Cryptographic/include/hash -I../Middlewares/ST/STM32_Cryptographic/include/mac -I../Middlewares/ST/STM32_Cryptographic/include/rsa -I../Middlewares/ST/STM32_Cryptographic/include/utils -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/include -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/include/cipher -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/include/drbg -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/include/ecc -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/include/hash -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/include/mac -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/include/membuf -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/include/rsa -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/src/membuf -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-ST-2f-STSELib-2f-services-2f-stsafel

clean-Middlewares-2f-ST-2f-STSELib-2f-services-2f-stsafel:
	-$(RM) ./Middlewares/ST/STSELib/services/stsafel/stsafel_commands.cyclo ./Middlewares/ST/STSELib/services/stsafel/stsafel_commands.d ./Middlewares/ST/STSELib/services/stsafel/stsafel_commands.o ./Middlewares/ST/STSELib/services/stsafel/stsafel_commands.su ./Middlewares/ST/STSELib/services/stsafel/stsafel_data_partition.cyclo ./Middlewares/ST/STSELib/services/stsafel/stsafel_data_partition.d ./Middlewares/ST/STSELib/services/stsafel/stsafel_data_partition.o ./Middlewares/ST/STSELib/services/stsafel/stsafel_data_partition.su ./Middlewares/ST/STSELib/services/stsafel/stsafel_device_info.cyclo ./Middlewares/ST/STSELib/services/stsafel/stsafel_device_info.d ./Middlewares/ST/STSELib/services/stsafel/stsafel_device_info.o ./Middlewares/ST/STSELib/services/stsafel/stsafel_device_info.su ./Middlewares/ST/STSELib/services/stsafel/stsafel_ecc.cyclo ./Middlewares/ST/STSELib/services/stsafel/stsafel_ecc.d ./Middlewares/ST/STSELib/services/stsafel/stsafel_ecc.o ./Middlewares/ST/STSELib/services/stsafel/stsafel_ecc.su ./Middlewares/ST/STSELib/services/stsafel/stsafel_echo.cyclo ./Middlewares/ST/STSELib/services/stsafel/stsafel_echo.d ./Middlewares/ST/STSELib/services/stsafel/stsafel_echo.o ./Middlewares/ST/STSELib/services/stsafel/stsafel_echo.su ./Middlewares/ST/STSELib/services/stsafel/stsafel_frame_transfer.cyclo ./Middlewares/ST/STSELib/services/stsafel/stsafel_frame_transfer.d ./Middlewares/ST/STSELib/services/stsafel/stsafel_frame_transfer.o ./Middlewares/ST/STSELib/services/stsafel/stsafel_frame_transfer.su ./Middlewares/ST/STSELib/services/stsafel/stsafel_low_power.cyclo ./Middlewares/ST/STSELib/services/stsafel/stsafel_low_power.d ./Middlewares/ST/STSELib/services/stsafel/stsafel_low_power.o ./Middlewares/ST/STSELib/services/stsafel/stsafel_low_power.su ./Middlewares/ST/STSELib/services/stsafel/stsafel_reset.cyclo ./Middlewares/ST/STSELib/services/stsafel/stsafel_reset.d ./Middlewares/ST/STSELib/services/stsafel/stsafel_reset.o ./Middlewares/ST/STSELib/services/stsafel/stsafel_reset.su ./Middlewares/ST/STSELib/services/stsafel/stsafel_timings.cyclo ./Middlewares/ST/STSELib/services/stsafel/stsafel_timings.d ./Middlewares/ST/STSELib/services/stsafel/stsafel_timings.o ./Middlewares/ST/STSELib/services/stsafel/stsafel_timings.su

.PHONY: clean-Middlewares-2f-ST-2f-STSELib-2f-services-2f-stsafel

