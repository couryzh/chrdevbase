**a very simple character device driver**

# driver
- check kernel version
  `uname -r`
  it output in my os like:
	5.4.0-67-generic
  this will determine the KDIR = /lib/modules/`` `uname -r` ``/build/ option in **Makefile**
- chrdevbase.ko
  - major device no
    major dev no. is 200, you can execute `cat /proc/devices` in shell
    to make sure 200 is not be used by other drivers, and modify it if neccessery
  - install it with `insmod chrdevbase.ko`
  	After installed, you can find it in `cat /proc/devices` 
  	execute `mknod /dev/chrdevbase c 200 0` in shell if there isnot exist
  	while c means character device
  	      200 means major device no.
  	      0   means minor device no.
  - uninstall it with `rmmod chrdevbase.ko`
  - printk
    the output of `printk` log in /var/log/kern.log in my **ubuntu** os

