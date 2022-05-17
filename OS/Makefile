obj-m += simple_hello_module.o
obj-m += pcb_get_module.o
obj-m += syscall_module.o
PWD := $(CURDIR)
all: 
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean: 
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
