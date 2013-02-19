#
#             LUFA Library
#     Copyright (C) Dean Camera, 2012.
#
#  dean [at] fourwalledcubicle [dot] com
#           www.lufa-lib.org
#
# --------------------------------------
#         LUFA Project Makefile.
# --------------------------------------
ARCH         = AVR8
BOARD        = TEENSY2
F_CPU        = 16000000
F_USB        = $(F_CPU)
OPTIMIZATION = s
TARGET       = adnw
SRCDIR       = ./src


# List C source files here. (C dependencies are automatically generated.)
SRC =   $(LUFA_SRC_USB)          \
	$(LUFA_SRC_USBCLASS)         \
	$(SRCDIR)/Keyboard.c         \
	$(SRCDIR)/dbg.c              \
	$(SRCDIR)/Descriptors.c      \
	$(SRCDIR)/keyboard_class.c   \
	$(SRCDIR)/keymap.c           \
	$(SRCDIR)/analog.c           \
	$(SRCDIR)/macro.c            \
	$(SRCDIR)/command.c          \
	$(SRCDIR)/mousekey.c         \
	$(SRCDIR)/jump_bootloader.c  \

LUFA_PATH    = LUFA/LUFA
CC_FLAGS     = -DUSE_LUFA_CONFIG_HEADER -IConfig/
CC_FLAGS    += -DDEBUG_OUTPUT
CC_FLAGS	+= -DKB_HW=$(KB_HW) -D$(KB_HW)
LD_FLAGS     =

# -----------------------------------------------------------
# Keyboard selection below: HYPERNANO, BLUECUBE or MALTRON_KW
# -----------------------------------------------------------
KB_HW		 = MALTRON_KW

##################################################################
#
# Should not need to change anything below ...
#
##################################################################

ifneq (,$(findstring MALTRON_KW,$(CC_FLAGS)))
CC_FLAGS    += # -DMACOS -DQWERTY
MCU          = at90usb1286 
else
CC_FLAGS    += -DPS2MOUSE -DMOUSE_HAS_SCROLL_WHEELS
MCU          = atmega32u4
endif

ifneq (,$(findstring DEBUG_OUTPUT,$(CC_FLAGS)))
	SRC += $(SRCDIR)/hhstdio.c
endif

ifneq (,$(findstring PS2MOUSE,$(CC_FLAGS)))
	SRC += $(SRCDIR)/ps2mouse.c
	SRC += $(SRCDIR)/trackpoint.c
endif

FW_VERSION := $(shell git describe --tags --always)-$(shell git log --pretty=format:%cd --date=short -n1)-$(shell git describe --tags --always --all | sed s:heads/::| tr " " "_")
ifeq ('',$(FW_VERSION))
FW_VERSION := unknown_version-$(shell date +%Y%m%d)
endif

CC_FLAGS    += -DFW_VERSION=\"$(FW_VERSION)\"

# Default target
all: lufacheck macrocheck


# test macro existance
macrocheck:
	@if test -f $(SRCDIR)/_private_macros.h; then \
	    echo "*** Macro definition found ";  \
	else \
	    echo -e "\n\n\n*** ERROR: $(SRCDIR)/_private_macros.h NOT found. \n*** Please copy template and edit as wanted:\n\n    cp $(SRCDIR)/_private_macros.h.template $(SRCDIR)/_private_macros.h\n\n"; \
	    false; \
	fi

# check that LUFA is there
lufacheck:
	@if test -d LUFA/LUFA ; then \
		echo "*** LUFA found.";\
	else \
		echo -e "*** ERROR: LUFA/LUFA missing - see README for install instructions.\n***        Try to checkout LUFA source with\n***            git submodule init && git submodule update\n\n"; false;\
	fi

ifneq (,$(findstring DEBUG_OUTPUT,$(CC_FLAGS)))
	@echo "*** DEBUG is defined" ; 
else
	@echo "*** DEBUG is NOT defined";
endif


# check whether scrollwheel support is requested and complete
ifneq (,$(findstring MOUSE_HAS_SCROLL_WHEELS,$(CC_FLAGS)))
	@echo "*** SCROLLWHEEL defined"; \
	if [ `grep -c "Vertical" LUFA/LUFA/Drivers/USB/Class/Common/HIDClassCommon.h` -eq 1 ] ; then \
	    echo "*** and LUFA seems patched, ok"; \
	else \
	    echo "*** ERROR: but LUFA not patched for it - run "; \
	    echo -e "*** patch -Np1 -i LUFA-scrollwheel.patch \n*** to fix \n" ; \
	    false; \
	fi
else
	@echo "*** SCROLLWHEEL not defined"
endif


# Include LUFA build script makefiles
# lines begin with "-" so if not found, the lufacheck above prints message 
-include $(LUFA_PATH)/Build/lufa_core.mk
-include $(LUFA_PATH)/Build/lufa_sources.mk
-include $(LUFA_PATH)/Build/lufa_build.mk
-include $(LUFA_PATH)/Build/lufa_cppcheck.mk
-include $(LUFA_PATH)/Build/lufa_doxygen.mk
-include $(LUFA_PATH)/Build/lufa_dfu.mk
-include $(LUFA_PATH)/Build/lufa_hid.mk
-include $(LUFA_PATH)/Build/lufa_avrdude.mk
-include $(LUFA_PATH)/Build/lufa_atprogram.mk
