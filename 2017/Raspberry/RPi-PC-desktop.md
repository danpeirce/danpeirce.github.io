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

The ISO image was loaded onto the flash drive using **rufus-2.18p.exe** on a windows 7 computer. To ensure the 
persistence option will work it is important to choose the **dd** (entire disk image) option rather than the 
**ISO** (file by file) option. 

Very nice the way it all works without needed to do a lot of configuration.

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

In a terminal on the PC desktop after the RPi Zero (USB OTG port not PWR port) has been attached to the PC USB port.
This connection will also provide power. 

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

## New PC applications - PiServer

There is a section in [https://www.raspberrypi.org/blog/stretch-pcs-macs-raspbian-update/](https://www.raspberrypi.org/blog/stretch-pcs-macs-raspbian-update/)
called *New PC applications* and it talks about **PiServer**. If PiServer is run on the RPi PC desktop, 
PiServer enables up to three Raspberry Pi 3s to do a network boot (over Ethernet). 

I expect the following advantages over booting from a microSD:

* The microSD cards can easily be corrupted if the Raspberry Pi 3 if it looses power unexpectedly. 
  This would not affect the operating system if a network boot is used. One could pull power on 
  the Raspberry Pi 3 without worry.
* It will likely make the setup of headless operation and control of the Raspberry Pi 3 from a PC more 
  straightforward.

Quoted from link given above:

~~~~
We have included a couple of new applications in the PC version. One is called PiServer — this allows 
you to set up an operating system, such as Raspbian, on the PC which can then be shared by a number 
of Pi clients networked to it. It is intended to make it easy for classrooms to have multiple Pis all 
running exactly the same software, and for the teacher to have control over how the software is 
installed and used. PiServer is quite a clever piece of software, and it’ll be covered in more detail 
in another blog post in December.
~~~~

I will be watching for the new blog post. Raspberry Pi 3s are available from many sources. Raspberry Pi Zeros 
are not as easy to get in quantity or in a reasonable time. 

## Debian Stretch Comments from zdnet.com

* [raspberry-pi-hands-on-with-raspbian-stretch-plus-debian-stretch-pi-desktop-for-pc-and-mac](http://www.zdnet.com/article/raspberry-pi-hands-on-with-raspbian-stretch-plus-debian-stretch-pi-desktop-for-pc-and-mac/)

