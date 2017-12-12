% Raspberry Pi Desktop for PC and Mac
% Notes by Dan Peirce B.Sc.

<!---
use pandoc -s --toc -t html5 -c ../../pandocbd.css RPi-PC-desktop.md -o RPi-PC-desktop.html
-->

# Raspberry Pi Desktop for PC (and Mac)

The Raspberry Pi foundation has made available a Debian derived Linux distribution that 
has the same look and feel as Raspbian that runs on the ARM based Raspberry Pi but instead runs 
on a x86 based processor (PC or MAC). It can be run from a bootable flash drive or installed on the computers 
hard drive.

* [www.raspberrypi.org blog stretch pcs macs update](https://www.raspberrypi.org/blog/stretch-pcs-macs-raspbian-update/)
* [My early post to forum](https://www.raspberrypi.org/forums/viewtopic.php?f=116&t=198934&p=1244030#p1244030)

## Initial Testing of Raspberry Pi Desktop

I have the Raspberry Pi up and running on a PC desktop. I believe this was the easiest install 
of a Linux desktop I have done. Often I have used Linux on older machines and chosen a light desktop like 
LXDE which was not the default for the distribution. This typically resulted in hours tweaking and not getting
everything working just as it should. It seems with this version of Debian Stretch the RPi Foundation has done
the tweaking and gotten it all right.

I am still having an issue when I boot directly from a flash drive but perhaps loading a 
flash drive from the Linux environment rather than making it with the win7 utility will solve that issue. 

*[forum - desktop persistence not working](https://www.raspberrypi.org/forums/viewtopic.php?f=116&t=188113&p=1244020#p1244020)

This will have to be resolved as for most people in the department booting from a flash drive will be more convenient 
than overwriting the hard drive.

## GPIO Expander

Quoting from the Raspberry Pi Blog:

~~~~
Use the GPIO pins of a Raspberry Pi Zero while 
running Debian Stretch on a PC or Mac with our 
new GPIO expander software! With this tool, 
you can easily access a Pi Zero’s GPIO pins 
from your x86 laptop without using SSH, and 
you can also take advantage of your x86 
computer’s processing power in your physical 
computing projects.
~~~~

* [RPi Blog - GPIO Expander](https://www.raspberrypi.org/blog/gpio-expander/)
* [RPi Blog - UPDATES TO GPIO ZERO, THE PHYSICAL COMPUTING API Aug 2017](https://www.raspberrypi.org/blog/gpio-zero-update/)

This is something I plan to test.

### For Debugging - Log onto Zero

In a terminal on the PC desktop:

~~~~
screen /dev/ttyACM0 115200
Username: root
Password: raspberry
~~~~

One will get a "#" as a prompt. There will be a limited temporary file system on a RAM drive.

#### Mount microSD

A bootable microSD would need to be removed to get the Zero to boot from the USB port rather than booting
from the microSD.Once the boot is complete one can reinsert the microSD and mount it (it won't mount 
automatically).

First just to make sure the micro SD is detectable try:

~~~~
# blkid
/dev/mmcblk0p2: UUID="202638e1-4ce4-45df-9a00-ad725c2537bb"
/dev/mmcblk0p1: LABEL="boot" UUID="22E0-C711"
~~~~

I created a directory to be used as a mount point

~~~~
# mkdir /mnt/sd
~~~~

then mounted the microSD to that directory:

~~~~
# mount -t ext4 /dev/mmcblk0p2 /mnt/sd
~~~~

In my case I used a microSD already set up with Noobs on it. That is why it
had been formatted with the ext4 file system. The disadvantage of formatting with
ext4 is that only Linux systems can read it. FAT32 is more universal (but less
rich in features).

The file system loaded correctly indicating the USB boot for the RPi Zero had worked 
successfully. 

