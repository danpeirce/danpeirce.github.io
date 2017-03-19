title: Utrasonic Ranger

# Ultrasonic Ranger

    by Dan Peirce B.Sc.

reformated from [dokuwiki](http://danpeirce.net46.net/dokuwiki/doku.php?id=ultrasonic_ranger) on July 20, 2013

  * <http://www3.telus.net/danpeirce/sensors/sonicRanger.pdf>
  * <http://www.maxbotix.com/documents/MB1010_Datasheet.pdf>

## Python Program

  * [ link to **why use python** ](python.html#why-use-python)

The ultrasonic ranging module sends asynchronous serial data in the form of a
"R" followed by three digits representing the range in inches followed by a
carriage return. In the following program the carriage return is ignored
(python looks for new line as a line delimiter; it does not use carriage
return which is unfortunately what is sent by the sonic ranger).

I also have C code (for a [ PIC18LF2620](hello33.html) rather than for a PC).  
See <https://our.kwantlen.ca/personal/danp/Shared%20Documents/range_with_compa
rator.zip> (requires login to obtain the zip file -- I can't post it here at
this time because it may become part of a class assignment).

    
    :::python    
    import serial
    import time
     
    ser = serial.Serial(2)  # com1 is (0) -- com3 is (2)
    print ser.portstr,      # prints the actual port name used
    print 'Python range2.py'
    print ' by Dan Peirce B.Sc.' 
    print ' of Kwantlen Polytechnic University'
     
     
    for j in range(1,15):  # just a python for loop (results in 14 iterations of the loop)
        ser.flushInput()   # The PC has a big buffer that could be full by now
        time.sleep(0.01)   # pause for 10 ms to allow some time for new data to arrive -- in hindsight I don't think this was needed
        s = ser.read(5)    # read the serial port in putting 5 characters into a string - I believe this blocks until 5chars have been received
        print s[:-1],      # print all but the last character of the string (the last character should be a carriage return)
        time.sleep(1)      # sleep for a second (don't want to update too fast as I want to have time to move the reflector)
    #note that in python indenting creates a block like { } in c.
     
    ser.close()
    
    
    COM3 Python range2.py
     by Dan Peirce B.Sc.
     of Kwantlen Polytechnic University
    R006 R006 R007 R009 R010 R011 R011 R012 R013 R013 R015 R017 R015 R020

## Example Using Python and Tkinter

This example is for a different device (a three axis accelerometer) but it is
quite easy to modify to be suitable for the MaxSonar module. It will produce a
plot of data.

  * <http://pagh.123abc.co.nz/?cat=4> \-- Accelerometer testing with Tkinter python GUI

I may well go back a make new versions of the PIC program to use with a
modified version of this python/tkinter program.

## Using matplotlib

A different solution to creating plots is making use of the library
matplotlib. This library was created to combine plotting capabilities similar
to Matlab with the Python programming language.

  * See [matplotlib](matplotlib.html)

