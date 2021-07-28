ifneq ($(KERNELRELEASE),)
	obj-m := hello-world.o
else
	KERNELDIR ?= /lib/modules/$(shell uname -r)/build
	PWD  := $(shell pwd)
default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
endif

clean:
	rm -f *.o *~ core .depend .*.cmd *.ko *.mod*
	rm -f Module.markers Module.symvers modules.order
	rm -rf .tmp_versions Modules.symvers
