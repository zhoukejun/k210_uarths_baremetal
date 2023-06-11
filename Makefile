
CROSS_COMPILE = riscv64-unknown-elf-

NAME		:= k210_uarths_baremetal

INCLUDEDIRS	+= ./
SOURCECODEDIRS	+= ./

AS		:= $(CROSS_COMPILE)gcc -x assembler-with-cpp -nostdlib
CC		:= $(CROSS_COMPILE)gcc
CXX		:= $(CROSS_COMPILE)g++
LD		:= $(CROSS_COMPILE)ld
AR		:= $(CROSS_COMPILE)ar
OC		:= $(CROSS_COMPILE)objcopy
OD		:= $(CROSS_COMPILE)objdump

MKDIR		:= mkdir -p
RM		:= rm -fr


ASFLAGS		:= -g -ggdb -Wall -O0 -mcmodel=medany -mabi=lp64d -march=rv64imfd -nostdlib -nostartfiles
CFLAGS		:= -g -ggdb -Wall -O0 -mcmodel=medany -mabi=lp64d -march=rv64imfd -nostdlib -nostartfiles -lm


LDFLAGS         := -T kendryte.ld  -nostartfiles -static -lm 

ARFLAGS		:= -rcs
OCFLAGS		:= -v -O binary
ODFLAGS		:=
MCFLAGS		:= -march=rv64imac -mabi=lp64 -mcmodel=medlow -fno-stack-protector

OUT		:= build/output
NAME		:= $(patsubst %, $(OUT)/%, $(NAME))
INCDIRS		:= $(patsubst %, -I %, $(INCLUDEDIRS))
SRCDIRS		:= $(patsubst %, %, $(SOURCECODEDIRS))
OBJDIRS		:= $(patsubst %, build/%, $(SRCDIRS))

SFILES		:= $(foreach dir, $(SRCDIRS), $(wildcard $(dir)/*.S))
CFILES		:= $(foreach dir, $(SRCDIRS), $(wildcard $(dir)/*.c))

SDEPS		:= $(patsubst %, build/%, $(SFILES:.S=.o.d))
CDEPS		:= $(patsubst %, build/%, $(CFILES:.c=.o.d))
DEPS		:= $(SDEPS) $(CDEPS)

SOBJS		:= $(patsubst %, build/%, $(SFILES:.S=.o))
COBJS		:= $(patsubst %, build/%, $(CFILES:.c=.o))
OBJS		:= $(SOBJS) $(COBJS)

.PHONY: all clean
all: $(NAME)

$(NAME): $(OBJS)
	@echo [LD] linking $@.elf
	@$(CC) $(LDFLAGS) -Wl,--cref,-Map=$@.map $^ -o $@.elf
	@echo [OC] Objcopying $@.bin
	@$(OC) $(OCFLAGS) $@.elf $@.bin
	@$(OD) -s -d $@.elf > $@.txt

$(SOBJS): build/%.o : %.S
	@echo [AS] $<
	@$(AS) $(ASFLAGS) -MD -MP -MF $@.d $(INCDIRS) -c $< -o $@

$(COBJS): build/%.o : %.c
	@echo [CC] $<
	@$(CC) $(CFLAGS) -MD -MP -MF $@.di $(INCDIRS) -c $< -o $@

clean:
	@$(RM) build $(OUT)

#
# Include the dependency files, should be place the last of makefile
#
sinclude $(shell $(MKDIR) $(OBJDIRS) $(OUT)) $(DEPS)
