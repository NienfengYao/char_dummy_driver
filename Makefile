DRIVER_NAME = dummydrv
obj-m := $(DRIVER_NAME).o

all: kernel_module writer

kernel_module: $(DRIVER_NAME).c
	make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) modules

writer: writer.c
	$(CC) -Wall -o writer writer.c -lrt

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) clean
	rm -f writer

check: all
	lsmod | grep dummydrv || $(MAKE) install_driver
	sudo ./writer

install_driver: $(DRIVER_BIN)
	sudo insmod $(DRIVER_NAME).ko
	sudo mknod /dev/$(DRIVER_NAME) c 255 0

uninstall_driver:
	sudo rmmod $(DRIVER_NAME)
	sudo rm /dev/$(DRIVER_NAME)
