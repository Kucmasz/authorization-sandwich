################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/ST/STM32_Cryptographic/legacy_v3/src/cipher/legacy_v3_aes_cbc.c \
../Middlewares/ST/STM32_Cryptographic/legacy_v3/src/cipher/legacy_v3_aes_ccm.c \
../Middlewares/ST/STM32_Cryptographic/legacy_v3/src/cipher/legacy_v3_aes_cfb.c \
../Middlewares/ST/STM32_Cryptographic/legacy_v3/src/cipher/legacy_v3_aes_ctr.c \
../Middlewares/ST/STM32_Cryptographic/legacy_v3/src/cipher/legacy_v3_aes_ecb.c \
../Middlewares/ST/STM32_Cryptographic/legacy_v3/src/cipher/legacy_v3_aes_gcm.c \
../Middlewares/ST/STM32_Cryptographic/legacy_v3/src/cipher/legacy_v3_aes_keywrap.c \
../Middlewares/ST/STM32_Cryptographic/legacy_v3/src/cipher/legacy_v3_aes_ofb.c \
../Middlewares/ST/STM32_Cryptographic/legacy_v3/src/cipher/legacy_v3_aes_xts.c \
../Middlewares/ST/STM32_Cryptographic/legacy_v3/src/cipher/legacy_v3_chachapoly.c 

OBJS += \
./Middlewares/ST/STM32_Cryptographic/legacy_v3/src/cipher/legacy_v3_aes_cbc.o \
./Middlewares/ST/STM32_Cryptographic/legacy_v3/src/cipher/legacy_v3_aes_ccm.o \
./Middlewares/ST/STM32_Cryptographic/legacy_v3/src/cipher/legacy_v3_aes_cfb.o \
./Middlewares/ST/STM32_Cryptographic/legacy_v3/src/cipher/legacy_v3_aes_ctr.o \
./Middlewares/ST/STM32_Cryptographic/legacy_v3/src/cipher/legacy_v3_aes_ecb.o \
./Middlewares/ST/STM32_Cryptographic/legacy_v3/src/cipher/legacy_v3_aes_gcm.o \
./Middlewares/ST/STM32_Cryptographic/legacy_v3/src/cipher/legacy_v3_aes_keywrap.o \
./Middlewares/ST/STM32_Cryptographic/legacy_v3/src/cipher/legacy_v3_aes_ofb.o \
./Middlewares/ST/STM32_Cryptographic/legacy_v3/src/cipher/legacy_v3_aes_xts.o \
./Middlewares/ST/STM32_Cryptographic/legacy_v3/src/cipher/legacy_v3_chachapoly.o 

C_DEPS += \
./Middlewares/ST/STM32_Cryptographic/legacy_v3/src/cipher/legacy_v3_aes_cbc.d \
./Middlewares/ST/STM32_Cryptographic/legacy_v3/src/cipher/legacy_v3_aes_ccm.d \
./Middlewares/ST/STM32_Cryptographic/legacy_v3/src/cipher/legacy_v3_aes_cfb.d \
./Middlewares/ST/STM32_Cryptographic/legacy_v3/src/cipher/legacy_v3_aes_ctr.d \
./Middlewares/ST/STM32_Cryptographic/legacy_v3/src/cipher/legacy_v3_aes_ecb.d \
./Middlewares/ST/STM32_Cryptographic/legacy_v3/src/cipher/legacy_v3_aes_gcm.d \
./Middlewares/ST/STM32_Cryptographic/legacy_v3/src/cipher/legacy_v3_aes_keywrap.d \
./Middlewares/ST/STM32_Cryptographic/legacy_v3/src/cipher/legacy_v3_aes_ofb.d \
./Middlewares/ST/STM32_Cryptographic/legacy_v3/src/cipher/legacy_v3_aes_xts.d \
./Middlewares/ST/STM32_Cryptographic/legacy_v3/src/cipher/legacy_v3_chachapoly.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/ST/STM32_Cryptographic/legacy_v3/src/cipher/%.o Middlewares/ST/STM32_Cryptographic/legacy_v3/src/cipher/%.su Middlewares/ST/STM32_Cryptographic/legacy_v3/src/cipher/%.cyclo: ../Middlewares/ST/STM32_Cryptographic/legacy_v3/src/cipher/%.c Middlewares/ST/STM32_Cryptographic/legacy_v3/src/cipher/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../X-CUBE-STSE01/App -I../X-CUBE-STSE01/Target -I../Drivers/BSP/STM32F4xx_Nucleo -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/ST/STSELib/api/ -I../Middlewares/ST/STSELib/certificate/ -I../Middlewares/ST/STSELib/core/ -I../Middlewares/ST/STSELib/services/ -I../Middlewares/ST/STSELib/services/stsafea/ -I../Middlewares/ST/STSELib/services/stsafel/ -I../Middlewares/ST/STSELib -I../Middlewares/ST/STSELib/api -I../Middlewares/ST/STSELib/certificate -I../Middlewares/ST/STSELib/core -I../Middlewares/ST/STSELib/services/stsafea -I../Middlewares/ST/STSELib/services/stsafel -I../Drivers/BSP/ESE02A1 -I../Drivers/BSP/Components/STSAFEL010 -I../Middlewares/ST/STM32_Cryptographic/_htmresc/ -I../Middlewares/ST/STM32_Cryptographic/include/ -I../Middlewares/ST/STM32_Cryptographic/interface/ -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/ -I../Middlewares/ST/STM32_Cryptographic/lib/ -I../Middlewares/ST/STM32_Cryptographic/include/cipher/ -I../Middlewares/ST/STM32_Cryptographic/include/drbg/ -I../Middlewares/ST/STM32_Cryptographic/include/ecc/ -I../Middlewares/ST/STM32_Cryptographic/include/hash/ -I../Middlewares/ST/STM32_Cryptographic/include/mac/ -I../Middlewares/ST/STM32_Cryptographic/include/rsa/ -I../Middlewares/ST/STM32_Cryptographic/include/utils/ -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/include/ -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/src/ -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/include/cipher/ -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/include/drbg/ -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/include/ecc/ -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/include/hash/ -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/include/mac/ -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/include/membuf/ -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/include/rsa/ -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/src/cipher/ -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/src/drbg/ -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/src/ecc/ -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/src/hash/ -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/src/mac/ -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/src/membuf/ -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/src/rsa/ -I../Middlewares/ST/STM32_Cryptographic/include -I../Middlewares/ST/STM32_Cryptographic/include/cipher -I../Middlewares/ST/STM32_Cryptographic/include/drbg -I../Middlewares/ST/STM32_Cryptographic/include/ecc -I../Middlewares/ST/STM32_Cryptographic/include/hash -I../Middlewares/ST/STM32_Cryptographic/include/mac -I../Middlewares/ST/STM32_Cryptographic/include/rsa -I../Middlewares/ST/STM32_Cryptographic/include/utils -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/include -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/include/cipher -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/include/drbg -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/include/ecc -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/include/hash -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/include/mac -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/include/membuf -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/include/rsa -I../Middlewares/ST/STM32_Cryptographic/legacy_v3/src/membuf -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-ST-2f-STM32_Cryptographic-2f-legacy_v3-2f-src-2f-cipher

clean-Middlewares-2f-ST-2f-STM32_Cryptographic-2f-legacy_v3-2f-src-2f-cipher:
	-$(RM) ./Middlewares/ST/STM32_Cryptographic/legacy_v3/src/cipher/legacy_v3_aes_cbc.cyclo ./Middlewares/ST/STM32_Cryptographic/legacy_v3/src/cipher/legacy_v3_aes_cbc.d ./Middlewares/ST/STM32_Cryptographic/legacy_v3/src/cipher/legacy_v3_aes_cbc.o ./Middlewares/ST/STM32_Cryptographic/legacy_v3/src/cipher/legacy_v3_aes_cbc.su ./Middlewares/ST/STM32_Cryptographic/legacy_v3/src/cipher/legacy_v3_aes_ccm.cyclo ./Middlewares/ST/STM32_Cryptographic/legacy_v3/src/cipher/legacy_v3_aes_ccm.d ./Middlewares/ST/STM32_Cryptographic/legacy_v3/src/cipher/legacy_v3_aes_ccm.o ./Middlewares/ST/STM32_Cryptographic/legacy_v3/src/cipher/legacy_v3_aes_ccm.su ./Middlewares/ST/STM32_Cryptographic/legacy_v3/src/cipher/legacy_v3_aes_cfb.cyclo ./Middlewares/ST/STM32_Cryptographic/legacy_v3/src/cipher/legacy_v3_aes_cfb.d ./Middlewares/ST/STM32_Cryptographic/legacy_v3/src/cipher/legacy_v3_aes_cfb.o ./Middlewares/ST/STM32_Cryptographic/legacy_v3/src/cipher/legacy_v3_aes_cfb.su ./Middlewares/ST/STM32_Cryptographic/legacy_v3/src/cipher/legacy_v3_aes_ctr.cyclo ./Middlewares/ST/STM32_Cryptographic/legacy_v3/src/cipher/legacy_v3_aes_ctr.d ./Middlewares/ST/STM32_Cryptographic/legacy_v3/src/cipher/legacy_v3_aes_ctr.o ./Middlewares/ST/STM32_Cryptographic/legacy_v3/src/cipher/legacy_v3_aes_ctr.su ./Middlewares/ST/STM32_Cryptographic/legacy_v3/src/cipher/legacy_v3_aes_ecb.cyclo ./Middlewares/ST/STM32_Cryptographic/legacy_v3/src/cipher/legacy_v3_aes_ecb.d ./Middlewares/ST/STM32_Cryptographic/legacy_v3/src/cipher/legacy_v3_aes_ecb.o ./Middlewares/ST/STM32_Cryptographic/legacy_v3/src/cipher/legacy_v3_aes_ecb.su ./Middlewares/ST/STM32_Cryptographic/legacy_v3/src/cipher/legacy_v3_aes_gcm.cyclo ./Middlewares/ST/STM32_Cryptographic/legacy_v3/src/cipher/legacy_v3_aes_gcm.d ./Middlewares/ST/STM32_Cryptographic/legacy_v3/src/cipher/legacy_v3_aes_gcm.o ./Middlewares/ST/STM32_Cryptographic/legacy_v3/src/cipher/legacy_v3_aes_gcm.su ./Middlewares/ST/STM32_Cryptographic/legacy_v3/src/cipher/legacy_v3_aes_keywrap.cyclo ./Middlewares/ST/STM32_Cryptographic/legacy_v3/src/cipher/legacy_v3_aes_keywrap.d ./Middlewares/ST/STM32_Cryptographic/legacy_v3/src/cipher/legacy_v3_aes_keywrap.o ./Middlewares/ST/STM32_Cryptographic/legacy_v3/src/cipher/legacy_v3_aes_keywrap.su ./Middlewares/ST/STM32_Cryptographic/legacy_v3/src/cipher/legacy_v3_aes_ofb.cyclo ./Middlewares/ST/STM32_Cryptographic/legacy_v3/src/cipher/legacy_v3_aes_ofb.d ./Middlewares/ST/STM32_Cryptographic/legacy_v3/src/cipher/legacy_v3_aes_ofb.o ./Middlewares/ST/STM32_Cryptographic/legacy_v3/src/cipher/legacy_v3_aes_ofb.su ./Middlewares/ST/STM32_Cryptographic/legacy_v3/src/cipher/legacy_v3_aes_xts.cyclo ./Middlewares/ST/STM32_Cryptographic/legacy_v3/src/cipher/legacy_v3_aes_xts.d ./Middlewares/ST/STM32_Cryptographic/legacy_v3/src/cipher/legacy_v3_aes_xts.o ./Middlewares/ST/STM32_Cryptographic/legacy_v3/src/cipher/legacy_v3_aes_xts.su ./Middlewares/ST/STM32_Cryptographic/legacy_v3/src/cipher/legacy_v3_chachapoly.cyclo ./Middlewares/ST/STM32_Cryptographic/legacy_v3/src/cipher/legacy_v3_chachapoly.d ./Middlewares/ST/STM32_Cryptographic/legacy_v3/src/cipher/legacy_v3_chachapoly.o ./Middlewares/ST/STM32_Cryptographic/legacy_v3/src/cipher/legacy_v3_chachapoly.su

.PHONY: clean-Middlewares-2f-ST-2f-STM32_Cryptographic-2f-legacy_v3-2f-src-2f-cipher

