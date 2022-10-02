################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL := cmd.exe
RM := rm -rf

USER_OBJS :=

LIBS := 
PROJ := 

O_SRCS := 
C_SRCS := 
S_SRCS := 
S_UPPER_SRCS := 
OBJ_SRCS := 
ASM_SRCS := 
PREPROCESSING_SRCS := 
OBJS := 
OBJS_AS_ARGS := 
C_DEPS := 
C_DEPS_AS_ARGS := 
EXECUTABLES := 
OUTPUT_FILE_PATH :=
OUTPUT_FILE_PATH_AS_ARGS :=
AVR_APP_PATH :=$$$AVR_APP_PATH$$$
QUOTE := "
ADDITIONAL_DEPENDENCIES:=
OUTPUT_FILE_DEP:=
LIB_DEP:=
LINKER_SCRIPT_DEP:=

# Every subdirectory with source files must be described here
SUBDIRS := 


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
../AD9833.c \
../main.c \
../SPI.c


PREPROCESSING_SRCS += 


ASM_SRCS += 


OBJS +=  \
AD9833.o \
main.o \
SPI.o

OBJS_AS_ARGS +=  \
AD9833.o \
main.o \
SPI.o

C_DEPS +=  \
AD9833.d \
main.d \
SPI.d

C_DEPS_AS_ARGS +=  \
AD9833.d \
main.d \
SPI.d

OUTPUT_FILE_PATH +=signalgeneratordebug.elf

OUTPUT_FILE_PATH_AS_ARGS +=signalgeneratordebug.elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

LIB_DEP+= 

LINKER_SCRIPT_DEP+= 


# AVR32/GNU C Compiler
./AD9833.o: .././AD9833.c
	@echo Building file: $<
	@echo Invoking: XC8 C Compiler : 2.31
	$(QUOTE)D:\Program\Microchip\xc8\v2.31\bin\xc8-cc.exe$(QUOTE)  -mcpu=ATmega328P  -mdfp="D:\Program\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.6.364\xc8"  -c -x c -funsigned-char -funsigned-bitfields -mext=cci -D__ATmega328P__ -DDEBUG  -Og -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	

./main.o: .././main.c
	@echo Building file: $<
	@echo Invoking: XC8 C Compiler : 2.31
	$(QUOTE)D:\Program\Microchip\xc8\v2.31\bin\xc8-cc.exe$(QUOTE)  -mcpu=ATmega328P  -mdfp="D:\Program\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.6.364\xc8"  -c -x c -funsigned-char -funsigned-bitfields -mext=cci -D__ATmega328P__ -DDEBUG  -Og -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	

./SPI.o: .././SPI.c
	@echo Building file: $<
	@echo Invoking: XC8 C Compiler : 2.31
	$(QUOTE)D:\Program\Microchip\xc8\v2.31\bin\xc8-cc.exe$(QUOTE)  -mcpu=ATmega328P  -mdfp="D:\Program\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.6.364\xc8"  -c -x c -funsigned-char -funsigned-bitfields -mext=cci -D__ATmega328P__ -DDEBUG  -Og -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	




# AVR32/GNU Preprocessing Assembler



# AVR32/GNU Assembler




ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: $(OUTPUT_FILE_PATH) $(ADDITIONAL_DEPENDENCIES)

$(OUTPUT_FILE_PATH): $(OBJS) $(USER_OBJS) $(OUTPUT_FILE_DEP) $(LIB_DEP) $(LINKER_SCRIPT_DEP)
	@echo Building target: $@
	@echo Invoking:  XC8 C Linker : 2.31
	$(QUOTE)D:\Program\Microchip\xc8\v2.31\bin\xc8-cc.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -mcpu=ATmega328P  -mdfp="D:\Program\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.6.364\xc8"  -Wl,-Map="signalgeneratordebug.map" -funsigned-char -funsigned-bitfields -Wl,--start-group -Wl,-lm  -Wl,--end-group -Wl,--gc-sections -Og -ffunction-sections -fdata-sections -fpack-struct -fshort-enums --memorysummary,memoryfile.xml  
	@echo Finished building target: $@
	"D:\Program\Microchip\xc8\v2.31\bin\avr-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures  "signalgeneratordebug.elf" "signalgeneratordebug.hex"
	"D:\Program\Microchip\xc8\v2.31\bin\avr-objcopy.exe" -j .eeprom --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0 --no-change-warnings -O ihex "signalgeneratordebug.elf" "signalgeneratordebug.eep" || exit 0
	"D:\Program\Microchip\xc8\v2.31\bin\avr-objdump.exe" -h -S "signalgeneratordebug.elf" > "signalgeneratordebug.lss"
	
	





# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS) $(EXECUTABLES)  
	-$(RM) $(C_DEPS_AS_ARGS)   
	rm -rf "signalgeneratordebug.elf" "signalgeneratordebug.hex" "signalgeneratordebug.eep" "signalgeneratordebug.map" "signalgeneratordebug.usersignatures" "signalgeneratordebug.a"  "signalgeneratordebug.lss"
	