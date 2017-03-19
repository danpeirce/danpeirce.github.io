title: Raspberry Pi SSH

### link back to raspberry_pi

link back to [raspberry_pi.html](raspberry_pi.html)  
link back to [git.html](git.html)

[TOC]

# Raspberry Pi SSH

The basic instruction needed to set up Secure Shell remote access to the
Raspberry Pi are given at  

  1. <http://elinux.org/RPi_Remote_Access>
  2. <http://elinux.org/RPi_Beginners#Create_a_new_user_with_sudo-privileges>

Working at home I have a router between the high speed modem and local LAN.
This allows me to reserve IP addresses for different devices and yet allows
them to obtain their IP address from the router through DHCP.

  * I assigned the Raspberry Pi to **192.168.0.109**   
![](rpi/network_connections_home.png)  

Notes  

    1. when this diagram was drawn I had not yet reconfigured /dev/ttyAMA0 for general use. Once this is done the PIC can be connected directly to the Raspberry Pi (see [ttyama0_configuration_reset](raspberry_pi.html#ttyama0-configuration-reset))

    2. The connection to the USB to Serial FTDI board is more reliable when the Raspberry Pi is connected to a USB hub and the USB to Serial FTDI board is downstream of the hub.

  * In that physics lab I don't have a local router and the Raspberry Pi gets assigned a IP address by DHCP. The Raspberry Pi is getting an IP of **10.213.1.85 (MAC is b8-27-eb-fc-b8-d1)** when connected in the Richmond physics lab. In the Surrey Physics lab it would get a different IP address. A different Raspberry Pi would have a different MAC address and so would get a different IP address. More on this at [logging_the_ip_address](raspberry_pi.html#logging-the-ip-address) .   
![](rpi/network_connections_r_lab.png)

In the raspbian distribution
[sshd](http://linux.about.com/od/commands/l/blcmdl8_sshd.htm) is running by
default.
 sshd is the program running on the Raspberry Pi that acts as a Secure
SHell server [daemon](http://www.linfo.org/daemon.html). PuTTY can be run as a
secure shell client on a windows PC.

## The settings for PuTTY

![](rpi/puttysession.png)

This resulted in a login that looked like this:

![](rpi/login.png)

The white on black looks like an old 1980's terminal. It can be made to look
more like a standard window by changing a setting. Add a check to "Use System
Colors". This make it easier on the eye's.

![](rpi/system_color_setting.png)

![](rpi/login_system_color.png)

## Remote Login from Android Tablet/Phone

The router I am using has four LAN ports as well as Wi-Fi. With Wi-Fi between
the Android and the router and a cat5 cable from the router to the Raspberry
Pi it is also possible to login to the Raspberry Pi from an Android
Tablet/Phone device.

I did a test using **connectbot** (see
<http://code.google.com/p/connectbot/>). It is easy to login but with my
Android I have no way to enter some key combinations unless an alternate
virtual keyboard is installed (the "[Hackers Keyboard"](https://play.google.co
m/store/apps/details?id=org.pocketworkstation.pckeyboard&hl=en) from the
Android market makes it possible to use the control key). This is not a
problem in the shell but in some applications like the pico editor there is no
way to enter the command functions (my tablet uses only a virtual keyboard).
Fortunately sFTP works great so files can simply be edited on the Android and
transferred to the Raspberry Pi using sFTP. Better still one can use a secure
shell and edit files on the Raspberry Pi remotely using
[Vim](http://www.vim.org) (Vim does not require the use of the control key and
it is possible to remap the Esc key to another key combination -- say the
combination jk).

I first logged in on a winXP desktop computer (IP 192.168.0.101) and second
logged in from an Android tablet (IP 192.168.0.108). The following box shows
the result of a **who** command run on the desktop.

  * [who](http://lowfatlinux.com/linux-users-who.html)
    
    
    danp@raspberrypi ~ $ who
    danp     pts/0        2012-08-02 19:56 (192.168.0.101)
    danp     pts/1        2012-08-02 20:03 (192.168.0.108)
    
    danp@raspberrypi ~ $

This underscores that the Raspberry Pi is a multi user system allowing
simultaneous logins of more than one user (in this case the same user logged
in from two different devices).

### Remote Login from an iPhone

I have not tested an iPhone because I don't have access to one. It should work
as well as the Android if a ssh client is installed.

  * <http://www.messagingnews.com/onmessage/ben-gross/iphone-ssh-clients-reviewed-issh-pterm-and-touchterm>

## sFTP

sFTP clients can be run on computers/tablets for file transfer. They connect
to the secure shell on the Raspberry Pi. For a windows sFTP client I used
[FileZilla](http://filezilla-project.org/) since I already had it installed on
my windows computer to access other sites.

![](rpi/filezilla_setup_rpi.png) ![](rpi/sftp.png)

On the Android tablet there also was a sFTP client installed. It is [ ES file]
(https://play.google.com/store/apps/details?id=com.estrongs.android.pop&hl=en)
manager which can be used both for local and remote file management.

### Headless Operation other Considerations

  * <http://www.penguintutor.com/linux/raspberrypi-headless>

If one is going to use the Raspberry Pi headless only it is possible to change
the memory split between the main system and video. I'll be coming back to
this.

