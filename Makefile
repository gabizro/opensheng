TARGET = opensheng

TOOLCHAIN = /usr
AS = $(TOOLCHAIN)/bin/arm-none-eabi-as
LD = $(TOOLCHAIN)/bin/arm-none-eabi-ld
CC = $(TOOLCHAIN)/bin/arm-none-eabi-gcc
OC = $(TOOLCHAIN)/bin/arm-none-eabi-objcopy
OD = $(TOOLCHAIN)/bin/arm-none-eabi-objdump
OS = $(TOOLCHAIN)/bin/arm-none-eabi-size

ASFLAGS += -mcpu=cortex-m0 
ASFLAGS += -mthumb

CFLAGS += -mcpu=cortex-m0 
CFLAGS += -mthumb 
CFLAGS += -g 
CFLAGS += -O0 
CFLAGS += -fno-common

CFLAGS += -I./inc
CFLAGS += -I./src

LSCRIPT = ./ld/dp32g030.ld
LFLAGS += -T$(LSCRIPT)

OBJS = asm/startup_dp32g030.o src/main.o inc/dp32g030_rcc.o inc/dp32g030_gpio.o

all: $(TARGET).bin

$(TARGET).bin: $(TARGET).elf
	$(OC) -O binary $< $@

$(TARGET).elf: $(OBJS)
	@echo
	@echo Linking: $@
	$(LD) $(LFLAGS) -o $@ $^
	$(OD) -h -S $(TARGET).elf  > $(TARGET).lst

main.o: src/main.c
	@echo
	@echo Compiling: $<
	$(CC) -c $(CFLAGS) -I. src/main.c -o src/main.o

%.o: inc/%.c
	@echo
	@echo Compiling: $<
	$(CC) -c $(CFLAGS) -I. $< -o inc/$@

%.o: asm/%.S
	@echo
	@echo Assembling: $<
	$(AS) $(ASFLAGS) -o asm/$@ $< -alh=asm/$*.lst

clean:
	@echo
	@echo Cleaning:
	$(RM) $(OBJS)
	$(RM) *.o 
	$(RM) src/*.o
	$(RM) inc/*.o
	$(RM) *.elf
	$(RM) *.lst
