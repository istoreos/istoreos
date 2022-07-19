#================================================================
# Build MIPS Images
#================================================================

#TOOLCHAIN_PATH	= /usr/local/mips-sde/bin
TOOLCHAIN_PATH	= /usr/local/rsdk-1.5.9/linux/newlib/bin

#CROSS_COMPILE	= $(TOOLCHAIN_PATH)/sde-
CROSS_COMPILE	= $(TOOLCHAIN_PATH)/rsdk-elf-

#//================================================================
CC				= $(CROSS_COMPILE)gcc
LD				= $(CROSS_COMPILE)ld
OBJCOPY			= $(CROSS_COMPILE)objcopy
OBJDUMP			= $(CROSS_COMPILE)objdump

#//================================================================
DST_DIR			= ..
LINK_SCRIPT		= image.ld
CC_FLAGS		= -EB
LD_FLAGS		= -T $(LINK_SCRIPT)
OBJCOPY_FLAGS	= -O binary
OBJDUMP_FLAGS	= -d

#//================================================================
all:	clean v_entry isr_video ros_bootvector a_entry exc_dispatch exc_redirect

v_entry:	v_entry.S
	@$(CC) $(CC_FLAGS) -c $< -o $@.o
	@$(LD) $(LD_FLAGS) -o $@.elf $@.o
	@$(OBJCOPY) $(OBJCOPY_FLAGS) $@.elf $(DST_DIR)/$@.img
	@$(OBJDUMP) $(OBJDUMP_FLAGS) $@.elf > $@.text
	@echo "Generate $(DST_DIR)/$@.img"

isr_video:	isr_video.S
	@$(CC) $(CC_FLAGS) -c $< -o $@.o
	@$(LD) $(LD_FLAGS) -o $@.elf $@.o
	@$(OBJCOPY) $(OBJCOPY_FLAGS) $@.elf $(DST_DIR)/$@.img
	@$(OBJDUMP) $(OBJDUMP_FLAGS) $@.elf > $@.text
	@echo "Generate $(DST_DIR)/$@.img"

exc_redirect:	exc_redirect.S
	@$(CC) $(CC_FLAGS) -c $< -o $@.o
	@$(LD) $(LD_FLAGS) -o $@.elf $@.o
	@$(OBJCOPY) $(OBJCOPY_FLAGS) $@.elf $(DST_DIR)/$@.img
	@$(OBJDUMP) $(OBJDUMP_FLAGS) $@.elf > $@.text
	@echo "Generate $(DST_DIR)/$@.img"

ros_bootvector:	ros_bootvector.S
	@$(CC) $(CC_FLAGS) -c $< -o $@.o
	@$(LD) $(LD_FLAGS) -o $@.elf $@.o
	@$(OBJCOPY) $(OBJCOPY_FLAGS) $@.elf $(DST_DIR)/$@.img
	@$(OBJDUMP) $(OBJDUMP_FLAGS) $@.elf > $@.text
	@echo "Generate $(DST_DIR)/$@.img"

a_entry:	a_entry.S
	@$(CC) $(CC_FLAGS) -c $< -o $@.o
	@$(LD) $(LD_FLAGS) -o $@.elf $@.o
	@$(OBJCOPY) $(OBJCOPY_FLAGS) $@.elf $(DST_DIR)/$@.img
	@$(OBJDUMP) $(OBJDUMP_FLAGS) $@.elf > $@.text
	@echo "Generate $(DST_DIR)/$@.img"

exc_dispatch:	exc_dispatch.S
	@$(CC) $(CC_FLAGS) -c $< -o $@.o
	@$(LD) $(LD_FLAGS) -o $@.elf $@.o
	@$(OBJCOPY) $(OBJCOPY_FLAGS) $@.elf $(DST_DIR)/$@.img
	@$(OBJDUMP) $(OBJDUMP_FLAGS) $@.elf > $@.text
	@echo "Generate $(DST_DIR)/$@.img"

clean:
	@rm -f $(DST_DIR)/*.img *~ *.elf *.text *.o
