################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/ST/STSELib/certificate/stse_certificate.c \
../Middlewares/ST/STSELib/certificate/stse_certificate_crypto.c \
../Middlewares/ST/STSELib/certificate/stse_certificate_prints.c \
../Middlewares/ST/STSELib/certificate/stse_certificate_subparsing.c 

OBJS += \
./Middlewares/ST/STSELib/certificate/stse_certificate.o \
./Middlewares/ST/STSELib/certificate/stse_certificate_crypto.o \
./Middlewares/ST/STSELib/certificate/stse_certificate_prints.o \
./Middlewares/ST/STSELib/certificate/stse_certificate_subparsing.o 

C_DEPS += \
./Middlewares/ST/STSELib/certificate/stse_certificate.d \
./Middlewares/ST/STSELib/certificate/stse_certificate_crypto.d \
./Middlewares/ST/STSELib/certificate/stse_certificate_prints.d \
./Middlewares/ST/STSELib/certificate/stse_certificate_subparsing.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/ST/STSELib/certificate/%.o Middlewares/ST/STSELib/certificate/%.su Middlewares/ST/STSELib/certificate/%.cyclo: ../Middlewares/ST/STSELib/certificate/%.c Middlewares/ST/STSELib/certificate/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../X-CUBE-STSE01/App -I../X-CUBE-STSE01/Target -I../Drivers/BSP/STM32F4xx_Nucleo -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/ST/STSELib/api/ -I../Middlewares/ST/STSELib/certificate/ -I../Middlewares/ST/STSELib/core/ -I../Middlewares/ST/STSELib/services/ -I../Middlewares/ST/STSELib/services/stsafea/ -I../Middlewares/ST/STSELib/services/stsafel/ -I../Middlewares/ST/STSELib -I../Middlewares/ST/STSELib/api -I../Middlewares/ST/STSELib/certificate -I../Middlewares/ST/STSELib/core -I../Middlewares/ST/STSELib/services/stsafea -I../Middlewares/ST/STSELib/services/stsafel -I../Drivers/BSP/ESE02A1 -I../Drivers/BSP/Components/STSAFEL010 -I../Middlewares/ST/STM32_Cryptographic/_htmresc/ -I../Middlewares/ST/STM32_Cryptographic/include/ -I../Middlewares/ST/STM32_Cryptographic/interface/ -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/ -I../Middlewares/ST/STM32_Cryptographic/lib/ -I../Middlewares/ST/STM32_Cryptographic/include/cipher/ -I../Middlewares/ST/STM32_Cryptographic/include/drbg/ -I../Middlewares/ST/STM32_Cryptographic/include/ecc/ -I../Middlewares/ST/STM32_Cryptographic/include/hash/ -I../Middlewares/ST/STM32_Cryptographic/include/mac/ -I../Middlewares/ST/STM32_Cryptographic/include/rsa/ -I../Middlewares/ST/STM32_Cryptographic/include/utils/ -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/include/ -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/src/ -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/include/cipher/ -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/include/drbg/ -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/include/ecc/ -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/include/hash/ -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/include/mac/ -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/include/membuf/ -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/include/rsa/ -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/src/cipher/ -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/src/drbg/ -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/src/ecc/ -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/src/hash/ -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/src/mac/ -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/src/membuf/ -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/src/rsa/ -I../Middlewares/ST/STM32_Cryptographic/include -I../Middlewares/ST/STM32_Cryptographic/include/cipher -I../Middlewares/ST/STM32_Cryptographic/include/drbg -I../Middlewares/ST/STM32_Cryptographic/include/ecc -I../Middlewares/ST/STM32_Cryptographic/include/hash -I../Middlewares/ST/STM32_Cryptographic/include/mac -I../Middlewares/ST/STM32_Cryptographic/include/rsa -I../Middlewares/ST/STM32_Cryptographic/include/utils -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/include -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/include/cipher -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/include/drbg -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/include/ecc -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/include/hash -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/include/mac -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/include/membuf -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/include/rsa -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/src/membuf -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-ST-2f-STSELib-2f-certificate

clean-Middlewares-2f-ST-2f-STSELib-2f-certificate:
	-$(RM) ./Middlewares/ST/STSELib/certificate/stse_certificate.cyclo ./Middlewares/ST/STSELib/certificate/stse_certificate.d ./Middlewares/ST/STSELib/certificate/stse_certificate.o ./Middlewares/ST/STSELib/certificate/stse_certificate.su ./Middlewares/ST/STSELib/certificate/stse_certificate_crypto.cyclo ./Middlewares/ST/STSELib/certificate/stse_certificate_crypto.d ./Middlewares/ST/STSELib/certificate/stse_certificate_crypto.o ./Middlewares/ST/STSELib/certificate/stse_certificate_crypto.su ./Middlewares/ST/STSELib/certificate/stse_certificate_prints.cyclo ./Middlewares/ST/STSELib/certificate/stse_certificate_prints.d ./Middlewares/ST/STSELib/certificate/stse_certificate_prints.o ./Middlewares/ST/STSELib/certificate/stse_certificate_prints.su ./Middlewares/ST/STSELib/certificate/stse_certificate_subparsing.cyclo ./Middlewares/ST/STSELib/certificate/stse_certificate_subparsing.d ./Middlewares/ST/STSELib/certificate/stse_certificate_subparsing.o ./Middlewares/ST/STSELib/certificate/stse_certificate_subparsing.su

.PHONY: clean-Middlewares-2f-ST-2f-STSELib-2f-certificate

