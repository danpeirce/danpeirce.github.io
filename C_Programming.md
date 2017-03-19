title:The C Programming Language 

#  The C Programming Language and the Microchip PIC18FXXXX [MCU's](http://www3.telus.net/danpeirce/c_18/mcu_ubiquitous.html)

by Dan Peirce B.Sc.

rev January 9, 2008

[TOC]

## C and Embedded MCU's
[Microcontrollers are ubiquitous in our word today.](http://www3.telus.net/danpeirce/c_18/mcu_ubiquitous.html)
 
They are single IC microcomputer systems that are embedded as controllers in an endless
number of products.

The C programming language is used extensivly in for embeded systems
programming. [Microchip's
PIC](http://www.microchip.com/stellent/idcplg?IdcService=SS_GET_PAGE&nodeId=74
)[(history-link)](http://www.electronic-engineering.ch/microchip/faq/faq.html#
from_IO_handling)[MCU](http://en.wikipedia.org/wiki/Microcontroller)'s are one
possible target system. Programs for the PIC18FXXXX devices can be compiled
with Microchip's [MPLAB C18 compiler](http://www.microchip.com/stellent/idcplg
?IdcService=SS_GET_PAGE&nodeId=1406&dDocName=en010014). MPLAB C18 is an ansi C
compiler. It follows the standard with a few notable exceptions. One exception
is that recursion is not allowed. This is because of the limited resources of
the MCU. Another exception is with regard to stdio.h and the printf()
function. The printf() function does not support printing floats or long
variables. The MCU lacks a file system so functions meant to operate on files
are not supported in MPLAB C18.

## C, Unix, GNU and Linux

C originated as a language in which the unix kernel could be rewritten. This
was a significant development in computing as operating system kernels had
always been written in assembly. Using a higher level language allowed unix to
be easily ported to computes with different hardware. It also made possible
the eventual development of the GNU/[Linux](http://www.gnu.org/gnu/linux-and-
gnu.html) operating system which is a unix like operating system that runs on
an Intel CPU. The C compiler for unix was called cc and the compiler for
[GNU](http://www.gnu.org/)/Linux is
[gcc](http://www.gnu.org/software/gcc/gcc.html) (also see
<http://en.wikipedia.org/wiki/GNU_Compiler_Collection>). By the way GNU means
GNU's Not Unix. GCC has also been ported to run under windows in
[MinGW](http://en.wikipedia.org/wiki/MinGW). An windows IDE - GCC combination
is available in [Dev-C++](http://en.wikipedia.org/wiki/Dev-C%2B%2B).

### C for Small Systems
The characteristics that make C a good language for systems programming also
make it a good language for embedded systems. Very small simple MCU's are
often still programmed in [assembly
language](http://en.wikipedia.org/wiki/Assembly_language). MCU's with more
program memory can be programmed more quickly with a higher level language and
the language used most typically is C. In one viewpoint (Ravi Sethi
Programming Languages Concepts and Constructs [ISBN
0-201-10365-6](http://www.amazon.com/Programming-Languages-Constructs-Ravi-Set
hi/dp/0201503727/ref=sr_1_3/002-2110039-1339214?ie=UTF8&s=books&qid=1176106446
&sr=1-3)) a higher level language is "an extension of the underlying machine
and a program is an extension of  the programming language. In this view, the
language rebuilds the machine to provide more convenient facilities, and the
program further rebuilds the language to provide facilities closer to the
problem to be solved." C itself is a small language with only [29 keywords](ht
tp://www.imada.sdu.dk/%7Esvalle/courses/dm14-2005/mirror/c/section3_20.html).
C also comes with standard libraries that add many standard functions. A
programmer can write additional functions that can be grouped together in a
separate contemplation unit (c file) and can then be included in multiple
projects.

On a PC the standard output is the monitor. On a PIC MCU, programmed in C
usingMPLAB C18, the standard output is the USART. The USART must be configured
using the OpenUSART() function declaried in usart.h.

### Access to Specific Memory Addresses

C allows access to specific memory addresses. This feature allows one to
access a PIC18FXXXX special purpose registers which are used for interfacing
to the input output ports of the MCU. This direct access to IO ports will be
new to students in APSC1299. A simple assigment can be used to change the
status of a pin on the MCU. For example the PIC18F4525 pin designated RD0 (pin
19) can be read as follows:


    :::c
    char  a_value;

    a_value = PORTDbits.RD0;

PORTDbits.RD0 is declaired in the header file <p18f4525.h>.

That pin can be programmed as an output pin or an input pin. It is
reprogrammed as an output pin by using the TRISD special purpose register and
making an assigment as follows:

    :::c
    TRISDbits.TRISD0 =  0;

Once programed as an output the voltage on pin 19 can be set to either zero
voltes "0" or the supply voltage "1".

    :::c
    PORTDbits.RD0 = 0;   // set to zero volts

or
  
    :::c
    PORTDbits.RD0 = 1;   // set output to supply voltage Vdd

## Developments in Programming Languages Leading to C

See [The Development of the C programming Language](http://cm.bell-labs.com/cm/cs/who/dmr/chist.html)  

* [Fortran](http://en.wikipedia.org/wiki/FORTRAN)_"(IBM Mathematical **For**mula
**Tran**slating System_)"  
"Originally developed by
[IBM](http://en.wikipedia.org/wiki/International_Business_Machines) in the
[1950s](http://en.wikipedia.org/wiki/1950s) for scientific and engineering
applications..."
Writing programs in assembler was laborious and time intensive. FORTRAN
reduced the burden. Originally used on "[Main
Frame](http://en.wikipedia.org/wiki/Main_frame)" computers.

* [ALGOL 60](http://en.wikipedia.org/wiki/ALGOL)(ALGOrithmic Language)  
used mostly by computer scientists  but gave rise to a number of languages
including pascal and those listed below. "ALGOL 60 had no I/O facilities"

* [CPL (**Combined Programming Language**)](http://en.wikipedia.org/wiki/Combined_Programming_Language)  
A combined effort this language was large and complex  

* [BCPL  (Basic Combined Programming Language)](http://en.wikipedia.org/wiki/BCPL)  
Intended for writing compilers. Features of CPL that made compilation
difficult were removed making it a more "basic" language.  

* [B](http://en.wikipedia.org/wiki/B_programming_language)  (sort of a stripped
down BCPL --  stripped down so that could be used on
[minicomputers](http://en.wikipedia.org/wiki/Minicomputer)) \--Note that
minicoupters (obsolete) were smaller than mainframe computers and had very
limited resources compared to todays desktop computers.  

* [C](http://en.wikipedia.org/wiki/C_%28programming_language%29)first was "newB"
developed at Bell labs so that the Unix operating system could be rewritten in
a higher level language -- Unix had been written in assembly only.

"By 1973, the C language had become powerful enough that most of the [Unix](ht
tp://en.wikipedia.org/wiki/Unix)[kernel](http://en.wikipedia.org/wiki/Kernel_%
28computers%29), originally written in
[PDP-11](http://en.wikipedia.org/wiki/PDP-11/20) assembly language, was
rewritten in C. This was one of the first operating system kernels implemented
in a language other than assembly."

The GNU C compiler  (pronounced new C compiler -- see <http://gcc.gnu.org/>)
is used in the Linux operating system.  
see <http://en.wikipedia.org/wiki/GNU_Compiler_Collection#Overview>

GCC is now available withing an IDE for windows.  
See <http://www.bloodshed.net/devcpp.html>

see <http://en.wikipedia.org/wiki/C_%28programming_language%29#Usage>  
'C's primary use is for "[system
programming](http://en.wikipedia.org/wiki/System_programming)", including
implementing [operating
systems](http://en.wikipedia.org/wiki/Operating_system) and [embedded
system](http://en.wikipedia.org/wiki/Embedded_system) applications, due to a
combination of desirable characteristics such as code portability and
efficiency, ability to access specific hardware addresses, ability to "pun"
types to match externally imposed data access requirements, and low
[runtime](http://en.wikipedia.org/wiki/Runtime) demand on system resources.'

* C++ an incremental step beyond C (C++ is object oriented)

C is an imperative programming language

see

<http://en.wikipedia.org/wiki/Imperative_programming>  
<http://en.wikipedia.org/wiki/Declarative_programming>  
<http://en.wikipedia.org/wiki/Functional_programming>  
<http://en.wikipedia.org/wiki/Logic_programming>

