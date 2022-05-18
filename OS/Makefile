obj-m += module_simple_hello.o
obj-m += module_pcb_get.o
obj-m += module_syscall.o
obj-m += rwbuf.o
PWD := $(CURDIR)
all: 
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean: 
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
