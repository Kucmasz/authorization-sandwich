################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include X-CUBE-STSE01/Target/subdir.mk
-include X-CUBE-STSE01/App/subdir.mk
-include Middlewares/ST/STSELib/services/stsafel/subdir.mk
-include Middlewares/ST/STSELib/services/stsafea/subdir.mk
-include Middlewares/ST/STSELib/core/subdir.mk
-include Middlewares/ST/STSELib/certificate/subdir.mk
-include Middlewares/ST/STSELib/api/subdir.mk
-include Middlewares/ST/STM32_Cryptographic/legacy_v3/src/rsa/subdir.mk
-include Middlewares/ST/STM32_Cryptographic/legacy_v3/src/membuf/subdir.mk
-include Middlewares/ST/STM32_Cryptographic/legacy_v3/src/mac/subdir.mk
-include Middlewares/ST/STM32_Cryptographic/legacy_v3/src/hash/subdir.mk
-include Middlewares/ST/STM32_Cryptographic/legacy_v3/src/ecc/subdir.mk
-include Middlewares/ST/STM32_Cryptographic/legacy_v3/src/drbg/subdir.mk
-include Middlewares/ST/STM32_Cryptographic/legacy_v3/src/cipher/subdir.mk
-include Middlewares/ST/STM32_Cryptographic/interface/subdir.mk
-include Drivers/STM32F4xx_HAL_Driver/Src/subdir.mk
-include Drivers/BSP/STM32F4xx_Nucleo/subdir.mk
-include Drivers/BSP/ESE02A1/subdir.mk
-include Drivers/BSP/Components/STSAFEL010/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := authorization-sandwich
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
authorization-sandwich.elf \

MAP_FILES += \
authorization-sandwich.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
authorization-sandwich.list \


# All Target
all: main-build

# Main-build Target
main-build: authorization-sandwich.elf secondary-outputs

# Tool invocations
authorization-sandwich.elf authorization-sandwich.map: $(OBJS) $(USER_OBJS) /home/tomasz/Projects/X-NUCLEO-ESE02A1/authorization-sandwich/STM32F401RETX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "authorization-sandwich.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"/home/tomasz/Projects/X-NUCLEO-ESE02A1/authorization-sandwich/STM32F401RETX_FLASH.ld" --specs=nosys.specs -Wl,-Map="authorization-sandwich.map" -Wl,--gc-sections -static -L../Middlewares/ST/STM32_Cryptographic/lib --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

authorization-sandwich.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "authorization-sandwich.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) authorization-sandwich.elf authorization-sandwich.list authorization-sandwich.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
