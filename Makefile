KERNELDIR ?= /lib/modules/$(shell uname -r)/build
target = wlkom
obj-m = wlkom.o

all:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean

load:
	@sudo insmod ./$(target).ko

unload:
	@sudo rmmod $(target)

adddev:
	@echo sudo mknod /dev/$(target) "<major>" 0

rmdev:
	@sudo $(RM) /dev/$(target)

.PHONY: all clean load unload deldev