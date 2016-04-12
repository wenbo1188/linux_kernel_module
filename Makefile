obj-m := my_module.o my_module_ver_2.o my_module_ver_3.o
KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

all:

	make -C $(KDIR) M=$(PWD) modules

clean:
	
	rm *.o *.ko *.mod.c Module.symvers modules.order -f
