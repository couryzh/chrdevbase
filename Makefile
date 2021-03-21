obj-m := chrdevbase.o

KDIR = /lib/modules/5.4.0-67-generic/build/

all:
	$(MAKE) -C $(KDIR) M=$(PWD)

.PHONY: clean
clean:
	rm -f *.mod.c *.mod.o *.ko *.o *.tmp_versions


