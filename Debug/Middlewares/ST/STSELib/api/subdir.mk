################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/ST/STSELib/api/stse_aes.c \
../Middlewares/ST/STSELib/api/stse_asymmetric_keys_management.c \
../Middlewares/ST/STSELib/api/stse_data_storage.c \
../Middlewares/ST/STSELib/api/stse_device_authentication.c \
../Middlewares/ST/STSELib/api/stse_device_management.c \
../Middlewares/ST/STSELib/api/stse_ecc.c \
../Middlewares/ST/STSELib/api/stse_hash.c \
../Middlewares/ST/STSELib/api/stse_mac.c \
../Middlewares/ST/STSELib/api/stse_random.c \
../Middlewares/ST/STSELib/api/stse_symmetric_keys_management.c 

OBJS += \
./Middlewares/ST/STSELib/api/stse_aes.o \
./Middlewares/ST/STSELib/api/stse_asymmetric_keys_management.o \
./Middlewares/ST/STSELib/api/stse_data_storage.o \
./Middlewares/ST/STSELib/api/stse_device_authentication.o \
./Middlewares/ST/STSELib/api/stse_device_management.o \
./Middlewares/ST/STSELib/api/stse_ecc.o \
./Middlewares/ST/STSELib/api/stse_hash.o \
./Middlewares/ST/STSELib/api/stse_mac.o \
./Middlewares/ST/STSELib/api/stse_random.o \
./Middlewares/ST/STSELib/api/stse_symmetric_keys_management.o 

C_DEPS += \
./Middlewares/ST/STSELib/api/stse_aes.d \
./Middlewares/ST/STSELib/api/stse_asymmetric_keys_management.d \
./Middlewares/ST/STSELib/api/stse_data_storage.d \
./Middlewares/ST/STSELib/api/stse_device_authentication.d \
./Middlewares/ST/STSELib/api/stse_device_management.d \
./Middlewares/ST/STSELib/api/stse_ecc.d \
./Middlewares/ST/STSELib/api/stse_hash.d \
./Middlewares/ST/STSELib/api/stse_mac.d \
./Middlewares/ST/STSELib/api/stse_random.d \
./Middlewares/ST/STSELib/api/stse_symmetric_keys_management.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/ST/STSELib/api/%.o Middlewares/ST/STSELib/api/%.su Middlewares/ST/STSELib/api/%.cyclo: ../Middlewares/ST/STSELib/api/%.c Middlewares/ST/STSELib/api/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../X-CUBE-STSE01/App -I../X-CUBE-STSE01/Target -I../Drivers/BSP/STM32F4xx_Nucleo -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/ST/STSELib/api/ -I../Middlewares/ST/STSELib/certificate/ -I../Middlewares/ST/STSELib/core/ -I../Middlewares/ST/STSELib/services/ -I../Middlewares/ST/STSELib/services/stsafea/ -I../Middlewares/ST/STSELib/services/stsafel/ -I../Middlewares/ST/STSELib -I../Middlewares/ST/STSELib/api -I../Middlewares/ST/STSELib/certificate -I../Middlewares/ST/STSELib/core -I../Middlewares/ST/STSELib/services/stsafea -I../Middlewares/ST/STSELib/services/stsafel -I../Drivers/BSP/ESE02A1 -I../Drivers/BSP/Components/STSAFEL010 -I../Middlewares/ST/STM32_Cryptographic/_htmresc/ -I../Middlewares/ST/STM32_Cryptographic/include/ -I../Middlewares/ST/STM32_Cryptographic/interface/ -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/ -I../Middlewares/ST/STM32_Cryptographic/lib/ -I../Middlewares/ST/STM32_Cryptographic/include/cipher/ -I../Middlewares/ST/STM32_Cryptographic/include/drbg/ -I../Middlewares/ST/STM32_Cryptographic/include/ecc/ -I../Middlewares/ST/STM32_Cryptographic/include/hash/ -I../Middlewares/ST/STM32_Cryptographic/include/mac/ -I../Middlewares/ST/STM32_Cryptographic/include/rsa/ -I../Middlewares/ST/STM32_Cryptographic/include/utils/ -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/include/ -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/src/ -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/include/cipher/ -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/include/drbg/ -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/include/ecc/ -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/include/hash/ -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/include/mac/ -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/include/membuf/ -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/include/rsa/ -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/src/cipher/ -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/src/drbg/ -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/src/ecc/ -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/src/hash/ -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/src/mac/ -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/src/membuf/ -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/src/rsa/ -I../Middlewares/ST/STM32_Cryptographic/include -I../Middlewares/ST/STM32_Cryptographic/include/cipher -I../Middlewares/ST/STM32_Cryptographic/include/drbg -I../Middlewares/ST/STM32_Cryptographic/include/ecc -I../Middlewares/ST/STM32_Cryptographic/include/hash -I../Middlewares/ST/STM32_Cryptographic/include/mac -I../Middlewares/ST/STM32_Cryptographic/include/rsa -I../Middlewares/ST/STM32_Cryptographic/include/utils -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/include -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/include/cipher -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/include/drbg -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/include/ecc -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/include/hash -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/include/mac -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/include/membuf -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/include/rsa -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/src/membuf -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-ST-2f-STSELib-2f-api

clean-Middlewares-2f-ST-2f-STSELib-2f-api:
	-$(RM) ./Middlewares/ST/STSELib/api/stse_aes.cyclo ./Middlewares/ST/STSELib/api/stse_aes.d ./Middlewares/ST/STSELib/api/stse_aes.o ./Middlewares/ST/STSELib/api/stse_aes.su ./Middlewares/ST/STSELib/api/stse_asymmetric_keys_management.cyclo ./Middlewares/ST/STSELib/api/stse_asymmetric_keys_management.d ./Middlewares/ST/STSELib/api/stse_asymmetric_keys_management.o ./Middlewares/ST/STSELib/api/stse_asymmetric_keys_management.su ./Middlewares/ST/STSELib/api/stse_data_storage.cyclo ./Middlewares/ST/STSELib/api/stse_data_storage.d ./Middlewares/ST/STSELib/api/stse_data_storage.o ./Middlewares/ST/STSELib/api/stse_data_storage.su ./Middlewares/ST/STSELib/api/stse_device_authentication.cyclo ./Middlewares/ST/STSELib/api/stse_device_authentication.d ./Middlewares/ST/STSELib/api/stse_device_authentication.o ./Middlewares/ST/STSELib/api/stse_device_authentication.su ./Middlewares/ST/STSELib/api/stse_device_management.cyclo ./Middlewares/ST/STSELib/api/stse_device_management.d ./Middlewares/ST/STSELib/api/stse_device_management.o ./Middlewares/ST/STSELib/api/stse_device_management.su ./Middlewares/ST/STSELib/api/stse_ecc.cyclo ./Middlewares/ST/STSELib/api/stse_ecc.d ./Middlewares/ST/STSELib/api/stse_ecc.o ./Middlewares/ST/STSELib/api/stse_ecc.su ./Middlewares/ST/STSELib/api/stse_hash.cyclo ./Middlewares/ST/STSELib/api/stse_hash.d ./Middlewares/ST/STSELib/api/stse_hash.o ./Middlewares/ST/STSELib/api/stse_hash.su ./Middlewares/ST/STSELib/api/stse_mac.cyclo ./Middlewares/ST/STSELib/api/stse_mac.d ./Middlewares/ST/STSELib/api/stse_mac.o ./Middlewares/ST/STSELib/api/stse_mac.su ./Middlewares/ST/STSELib/api/stse_random.cyclo ./Middlewares/ST/STSELib/api/stse_random.d ./Middlewares/ST/STSELib/api/stse_random.o ./Middlewares/ST/STSELib/api/stse_random.su ./Middlewares/ST/STSELib/api/stse_symmetric_keys_management.cyclo ./Middlewares/ST/STSELib/api/stse_symmetric_keys_management.d ./Middlewares/ST/STSELib/api/stse_symmetric_keys_management.o ./Middlewares/ST/STSELib/api/stse_symmetric_keys_management.su

.PHONY: clean-Middlewares-2f-ST-2f-STSELib-2f-api

