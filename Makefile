
ifneq ($(KERNELRELEASE),)
include Kbuild
else
# normal makefile
KDIR ?= /lib/modules/`uname -r`/build

ccflags-y += -I$(src)/inc

default:
	$(MAKE) -C $(KDIR) M=$$PWD
clean:
	$(MAKE) -C $(KDIR) M=$$PWD clean
endif
