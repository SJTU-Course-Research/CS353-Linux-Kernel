#
# Makefile for the linux RomFS filesystem routines.
#

#obj-$(CONFIG_ROMFS_FS) += romfs.o
obj-m := romfs.o
romfs-y := storage.o super.o
KDIR := /lib/modules/$(shell uname -r)/build
EXTRA_FLAGS := -I(PWD)
PWD := $(shell pwd)
all:
	make -C $(KDIR) M=$(PWD) modules
clean:
	rm *.o *.ko *.mod.c Module.symvers modules.order -f
#ifneq ($(CONFIG_MMU),y)
#romfs-$(CONFIG_ROMFS_ON_MTD) += mmap-nommu.o
#endif

