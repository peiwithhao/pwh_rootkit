obj-m += pwhrootkit.o
CURRENT_PATH := $(shell pwd)
KERNEL_VERSION := $(shell uname -r)
MAIN_DIR := /home/$(shell whoami)
KERNEL_SOURCE_DIR := $(MAIN_DIR)/Kernel/kernel_source/linux-6.7.4/

all:
	make -C $(KERNEL_SOURCE_DIR) M=$(CURRENT_PATH) modules
clean:
	make -C $(KERNEL_SOURCE_DIR) M=$(CURRENT_PATH) clean


