################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/STM32F4xx_Nucleo/stm32f4xx_nucleo.c 

OBJS += \
./Drivers/BSP/STM32F4xx_Nucleo/stm32f4xx_nucleo.o 

C_DEPS += \
./Drivers/BSP/STM32F4xx_Nucleo/stm32f4xx_nucleo.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/STM32F4xx_Nucleo/%.o Drivers/BSP/STM32F4xx_Nucleo/%.su Drivers/BSP/STM32F4xx_Nucleo/%.cyclo: ../Drivers/BSP/STM32F4xx_Nucleo/%.c Drivers/BSP/STM32F4xx_Nucleo/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../X-CUBE-STSE01/App -I../X-CUBE-STSE01/Target -I../Drivers/BSP/STM32F4xx_Nucleo -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/ST/STSELib/api/ -I../Middlewares/ST/STSELib/certificate/ -I../Middlewares/ST/STSELib/core/ -I../Middlewares/ST/STSELib/services/ -I../Middlewares/ST/STSELib/services/stsafea/ -I../Middlewares/ST/STSELib/services/stsafel/ -I../Middlewares/ST/STSELib -I../Middlewares/ST/STSELib/api -I../Middlewares/ST/STSELib/certificate -I../Middlewares/ST/STSELib/core -I../Middlewares/ST/STSELib/services/stsafea -I../Middlewares/ST/STSELib/services/stsafel -I../Drivers/BSP/ESE02A1 -I../Drivers/BSP/Components/STSAFEL010 -I../Middlewares/ST/STM32_Cryptographic/_htmresc/ -I../Middlewares/ST/STM32_Cryptographic/include/ -I../Middlewares/ST/STM32_Cryptographic/interface/ -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/ -I../Middlewares/ST/STM32_Cryptographic/lib/ -I../Middlewares/ST/STM32_Cryptographic/include/cipher/ -I../Middlewares/ST/STM32_Cryptographic/include/drbg/ -I../Middlewares/ST/STM32_Cryptographic/include/ecc/ -I../Middlewares/ST/STM32_Cryptographic/include/hash/ -I../Middlewares/ST/STM32_Cryptographic/include/mac/ -I../Middlewares/ST/STM32_Cryptographic/include/rsa/ -I../Middlewares/ST/STM32_Cryptographic/include/utils/ -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/include/ -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/src/ -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/include/cipher/ -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/include/drbg/ -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/include/ecc/ -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/include/hash/ -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/include/mac/ -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/include/membuf/ -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/include/rsa/ -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/src/cipher/ -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/src/drbg/ -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/src/ecc/ -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/src/hash/ -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/src/mac/ -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/src/membuf/ -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/src/rsa/ -I../Middlewares/ST/STM32_Cryptographic/include -I../Middlewares/ST/STM32_Cryptographic/include/cipher -I../Middlewares/ST/STM32_Cryptographic/include/drbg -I../Middlewares/ST/STM32_Cryptographic/include/ecc -I../Middlewares/ST/STM32_Cryptographic/include/hash -I../Middlewares/ST/STM32_Cryptographic/include/mac -I../Middlewares/ST/STM32_Cryptographic/include/rsa -I../Middlewares/ST/STM32_Cryptographic/include/utils -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/include -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/include/cipher -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/include/drbg -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/include/ecc -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/include/hash -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/include/mac -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/include/membuf -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/include/rsa -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/src/membuf -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-STM32F4xx_Nucleo

clean-Drivers-2f-BSP-2f-STM32F4xx_Nucleo:
	-$(RM) ./Drivers/BSP/STM32F4xx_Nucleo/stm32f4xx_nucleo.cyclo ./Drivers/BSP/STM32F4xx_Nucleo/stm32f4xx_nucleo.d ./Drivers/BSP/STM32F4xx_Nucleo/stm32f4xx_nucleo.o ./Drivers/BSP/STM32F4xx_Nucleo/stm32f4xx_nucleo.su

.PHONY: clean-Drivers-2f-BSP-2f-STM32F4xx_Nucleo

