title: Python Language

[TOC]
### Computer Language

    "...the purpose of a higher-level programming language 
    is usually to provide some mediation between the way a 
    programmer would like to provide instructions and the 
    way a machine needs to have them."

* from [http://repository.upenn.edu/cgi/viewcontent.cgi?article=1330&amp;context=cis_reports](http://repository.upenn.edu/cgi/viewcontent.cgi?article=1330&amp;context=cis_reports "http://repository.upenn.edu/cgi/viewcontent.cgi?article=1330&amp;context=cis_reports")

# Python

It seems like Python has come a long way in recent years and has been a hotbed of development.

* [http://www.scipy.org/Topical_Software](http://www.scipy.org/Topical_Software "http://www.scipy.org/Topical_Software")

It is avalible for most operating systems.

* [http://www.python.org/](http://www.python.org/ "http://www.python.org/")

It is also possible use python on line without an install

* [http://www.sagemath.org/](http://www.sagemath.org/ "http://www.sagemath.org/")
* [sage](sage.html)

Other links:

* [http://www.youtube.com/watch?v=ugqu10JV7dk](http://www.youtube.com/watch?v=ugqu10JV7dk "http://www.youtube.com/watch?v=ugqu10JV7dk"). -- History of Python told by Guido van Rossum. He points out many ideas borrowed from an earlier language called ABC.
* [http://www.cs.ubc.ca/wccce/Program03/papers/Toby.html](http://www.cs.ubc.ca/wccce/Program03/papers/Toby.html "http://www.cs.ubc.ca/wccce/Program03/papers/Toby.html")  -- much of the comparison to java could also be applied to C.
* [http://www.youtube.com/watch?v=72RKMMyLxS8](http://www.youtube.com/watch?v=72RKMMyLxS8 "http://www.youtube.com/watch?v=72RKMMyLxS8").  -- seems to have an error. He says Python is typeless but as can be seen in the UBC link Python variables are dynamically typed. The error is just in terminology since he goes on to reveal how to determine the type assigned to a variable. 

## Why use Python?

* [http://www.math.harvard.edu/computing/python/index.html](http://www.math.harvard.edu/computing/python/index.html "http://www.math.harvard.edu/computing/python/index.html")
* [http://stackoverflow.com/questions/585815/how-useful-is-python](http://stackoverflow.com/questions/585815/how-useful-is-python "http://stackoverflow.com/questions/585815/how-useful-is-python")
* [http://msenux.redwoods.edu/math/python/index.php](http://msenux.redwoods.edu/math/python/index.php "http://msenux.redwoods.edu/math/python/index.php")
        * "Students in mathematics, science, and engineering need to develop some sort of computer literacy to accompany their work in their area of interest. There is no denying that many current developments in mathematics, science, and engineering are driven by modern software written to facilitate study in each of these areas."

* * *

*  There is an easy to use pre-compiled binary serial package for python. 
*  There is a GUI package in  the normal Python install binary. With  Perl tk is not included but must be added (big download and big compile).   

## Why Use a Scripting Language at all?

Put it a different way: when to use C and when to use a scripting language? 

I suggest looking at [http://gribblelab.org/CBootcamp/1_Why_Program_In_C.html#sec-3](http://gribblelab.org/CBootcamp/1_Why_Program_In_C.html#sec-3 "http://gribblelab.org/CBootcamp/1_Why_Program_In_C.html#sec-3")

1.Rapid development. 

2.One would think that there would be a lot of free c language libraries for common tasks  like using the serial port. What one finds is actually available are free Perl and Python modules. These are generally written in c but utilized using the scripting language.. This leads to quick efficient modules for common tasks and scripting  for those things that  are custom for the current project. 

3.In general the scripting language handles the interface to the  underlying operating system. The programmer does not need to learn the API each operating system that the script could be used with.

## A Free Python Book

* [http://www.greenteapress.com/thinkpython/](http://www.greenteapress.com/thinkpython/ "http://www.greenteapress.com/thinkpython/") -- access to downloadabble zip files (for LaTeX and HTML) and...  [http://www.greenteapress.com/thinkpython/thinkpython.html](http://www.greenteapress.com/thinkpython/thinkpython.html "http://www.greenteapress.com/thinkpython/thinkpython.html")  -- This is the online HTML version
* [http://www.greenteapress.com/thinkpython/thinkpython.pdf](http://www.greenteapress.com/thinkpython/thinkpython.pdf "http://www.greenteapress.com/thinkpython/thinkpython.pdf")   -- the book in PDF format

## Example

* [ultrasonic_ranger](ultrasonic_ranger)

## plotting with matplotlib

Find an introduction to matplotlib at [http://matplotlib.sourceforge.net/users/intro.html](http://matplotlib.sourceforge.net/users/intro.html "http://matplotlib.sourceforge.net/users/intro.html")

More at [matplotlib](matplotlib.html)

## Controlling GPIB, RS232, and USB instruments

* [http://pyvisa.sourceforge.net/](http://pyvisa.sourceforge.net/ "http://pyvisa.sourceforge.net/")

We have a USB instrument: the TBS1022 from Tektronix.

The programmers manual for this instrument can be found at:

* [http://www.tek.com/basic-oscilloscopes/tds1000-0-manual/tbs1000-tds200-tds1000-2000-tds1000b-2000b-tds1000c-edu-tds2000](http://www.tek.com/basic-oscilloscopes/tds1000-0-manual/tbs1000-tds200-tds1000-2000-tds1000b-2000b-tds1000c-edu-tds2000 "http://www.tek.com/basic-oscilloscopes/tds1000-0-manual/tbs1000-tds200-tds1000-2000-tds1000b-2000b-tds1000c-edu-tds2000")

Note that the same manual covers both the TBS1022 and the TDS1002B. We actually have some of both of these.

At the  [http://pyvisa.sourceforge.net/](http://pyvisa.sourceforge.net/ "http://pyvisa.sourceforge.net/") link some very simple code is given for talking to a digital multimeter

    :::python
    import visa
    keithley = visa.instrumen("GPIB::12")

    print keithley.ask("*IDN?")

We should also be able to talk to our scopes with this type of code. Something to try out. Found an example using usb at [http://www1.tek.com/forum/viewtopic.php?f=5&amp;t=5221](http://www1.tek.com/forum/viewtopic.php?f=5&amp;t=5221 "http://www1.tek.com/forum/viewtopic.php?f=5&amp;t=5221")

From that example can see the following (note the instrument name):

    :::python
    import visa
    import numpy as np
    from struct import unpack
    import pylab
 
    scope = visa.instrument('USB0::0x0699::0x0401::No_Serial::INSTR')

In another example the python script first reads the intrument name from the attached instruments:
[http://www.home.agilent.com/owc_discussions/thread.jspa?messageID=106272&amp;tstart=0](http://www.home.agilent.com/owc_discussions/thread.jspa?messageID=106272&amp;tstart=0 "http://www.home.agilent.com/owc_discussions/thread.jspa?messageID=106272&amp;tstart=0")

"Example 01 (directly with PyVisa):"

    :::python
    import visa import pylab
 
    # Get instrument VISAname
    visaInstrList = visa.get_instruments_list()
    myScope = visaInstrList[0]+'::INSTR'
 
    scope = visa.instrument(myScope)

So I tried this out in a IDLE session.

    :::python
    Python 2.7.5 (default, May 15 2013, 22:43:36) [MSC v.1500 32 bit (Intel)] on win32
    Type "copyright", "credits" or "license()" for more information.
    >>> import visa
    >>> visaInstrList = visa.get_instruments_list()
    >>> myScope = visaInstrList
    >>> myScope
    ['USB0::0x0699::0x03AE::C011174', 'COM1', 'COM3', 'LPT1', 'ASRL11']
    >>> myScope = visaInstrList[0]+'::INSTR'
    >>> scope = visa.instrument(myScope)
    >>> scope.ask("*IDN?")
    'TEKTRONIX,TBS 1022,C011174,CF:91.1CT FV:v26.01'
    >>> scope.write('CH1:VOLTS 2.0')
    >>> scope.write('TRIG:MAIN:LEVEL 2.4')
    >>> scope.write('HOR:MAIN:SCALE 100E-6')

It appears to work! The TBS 1022 responded to the last three commands as expected (meaning that the vertical scale of channel one was set to 2 volts/div, the trigger level was set to 2.4 volts and the horizontal scale was set to 100 micro-seconds/div).

I also tried setting and reading both the time and date.

    :::python
    >>> scope.write('DATE "2013-06-18"')
    >>> scope.write('TIME "18:37:00"')
    >>> scope.ask('date?')
    '"2013-06-18"'
    >>> scope.ask('time?')
    '"18:38:23"'

Using ethernet

* [http://alexforencich.com/wiki/en/python-vxi11/readme](http://alexforencich.com/wiki/en/python-vxi11/readme "http://alexforencich.com/wiki/en/python-vxi11/readme")
* [http://optics.eee.nottingham.ac.uk/vxi11/](http://optics.eee.nottingham.ac.uk/vxi11/ "http://optics.eee.nottingham.ac.uk/vxi11/")
* [http://www.tmworld.com/electronics-news/4378802/Linux-controls-instruments-through-Ethernet](http://www.tmworld.com/electronics-news/4378802/Linux-controls-instruments-through-Ethernet "http://www.tmworld.com/electronics-news/4378802/Linux-controls-instruments-through-Ethernet")

Using USB

* [http://www.ni.com/gettingstarted/setuphardware/instrumentcontrol/usbconnect.htm](http://www.ni.com/gettingstarted/setuphardware/instrumentcontrol/usbconnect.htm "http://www.ni.com/gettingstarted/setuphardware/instrumentcontrol/usbconnect.htm")
 

Python control of equipment

* [http://gael-varoquaux.info/physics/agile_computer_control_of_a_complex_experiment.pdf](http://gael-varoquaux.info/physics/agile_computer_control_of_a_complex_experiment.pdf "http://gael-varoquaux.info/physics/agile_computer_control_of_a_complex_experiment.pdf")

## Python Socket Communication

* [python_TCP_sockets](python_tcp_sockets.html)

## Python in Education

* [http://www.python.org/community/sigs/current/edu-sig/](http://www.python.org/community/sigs/current/edu-sig/ "http://www.python.org/community/sigs/current/edu-sig/")

## Internal Representation of Integers

I looked this up since I was interested.

* [http://www.laurentluce.com/posts/python-integer-objects-implementation/](http://www.laurentluce.com/posts/python-integer-objects-implementation/ "http://www.laurentluce.com/posts/python-integer-objects-implementation/")

## General Stuff to look at

* [http://wiki.python.org/moin/TcpCommunication](http://wiki.python.org/moin/TcpCommunication "http://wiki.python.org/moin/TcpCommunication")
* [http://www.pythonware.com/library/tkinter/introduction/hello-tkinter.htm](http://www.pythonware.com/library/tkinter/introduction/hello-tkinter.htm "http://www.pythonware.com/library/tkinter/introduction/hello-tkinter.htm")
* [http://www.python.org/doc/essays/cp4e.html](http://www.python.org/doc/essays/cp4e.html "http://www.python.org/doc/essays/cp4e.html")
* [http://reviewsindepth.com/2011/04/why-everyone-should-learn-to-program/](http://reviewsindepth.com/2011/04/why-everyone-should-learn-to-program/ "http://reviewsindepth.com/2011/04/why-everyone-should-learn-to-program/")
* [http://arstechnica.com/apple/2012/07/steve-jobs-on-programming-craftsmanship-software-and-the-web/](http://arstechnica.com/apple/2012/07/steve-jobs-on-programming-craftsmanship-software-and-the-web/ "http://arstechnica.com/apple/2012/07/steve-jobs-on-programming-craftsmanship-software-and-the-web/")

## Learning Python Links

* [https://developers.google.com/edu/python/](https://developers.google.com/edu/python/ "https://developers.google.com/edu/python/")

