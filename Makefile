MODULENAME = hw2
obj-m += $(MODULENAME).o
KVERSION := $(shell uname -r)
BUILDPATH := /lib/modules/$(KVERSION)/build
EXE = $(MODULENAME).ko


all: $(EXE) usr_prog

$(EXE) : $(MODULENAME).c
	$(MAKE) -C $(BUILDPATH) M=$(PWD) modules

usr_prog: usr_prog.c
	gcc -o usr_prog usr_prog.c

rm: $(EXE)
	rmmod ./$(EXE)
clean: 
	$(MAKE) -C $(BUILDPATH) M=$(PWD) clean
	rm usr_prog
