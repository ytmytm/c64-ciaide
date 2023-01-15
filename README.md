# CIA-IDE - ATA IDE interface for C64/128

Maciej Witkowiak
YTM/Elysium
ytm@elysium.pl
12.11.1999-14.08.2001


## ABOUT

This file contains complete solution for building IDE interface for
C64 or C128. I used here the most basic approach to interfacing IDE
with C64. There are also other interfaces that connect IDE device
directly to C64/128 CPU data/address bus but all of them failed for
me. One was not tested. Below are links to other projects on this
topic:

http://home.hccnet.nl/g.baltissen/index.htm
http://home.freeuk.net/c.ward/6502/

These are links to some documents:
P. Faasse's 8255 IDE interface - a good introduction to IDE interface
basics and programming. My interface is based on it. You SHOULD READ
this document BEFORE continuing. You MUST be familiar with it before
actually building anything described here.
(This file is named 8255-ide.txt and is distributed together with this
document, anyway I can't remember where did I find it)

Full ATA-2 specification. Might be useful for more advanced software.
(This is included too, for completeness)

Some schematics, might be useful
ftp://ftp.elysium.pl/docs/schematics/



## DISCLAIMER

I take no responsibility for any damage, data loss or any other
disaster you might encounter while building and/or using this
interface. It worked for me and should work for any other smart
monkey.



## NAMING CONVENTION

74'139 means 74LS139 or 74HC139 or 74HCT139. CIA means 6526 IC, CIA#3 means the
additional 6526 that you are about to add to your computer.


## THE POWER

You'll have to find a power source capable of +5V and +12V. It's up to you to
build or buy such a thing. C128D owners are lucky - original heavy duty power
supply is just OK.

```
/----\
|1234|	- this is IDE HDD power connector looking on HDD from back
------

1 - red    +5V
2 - black  GND
3 - black  GND
4 - yellow +12V
```

All IDE drives I've ever seen have power connector on the right side and
pin 1 of it is connected by red wire - this is +5V. On the left side there's
data cable and the rightmost wire is also red so there's no confusion - you
always connect red-to-red.



## THE INTERFACE (COMMON PART)

Basically the interface consits of port IC (it may be 8255 or CIA 6526 or
any other port IC) with at least 16 data lines and its wiring to C64/128
I/O space. Port's data lines are hooked directly to IDE 40pin socket.

Parts needed:
- 6526 or 8255 - port IC
- 40pin wire wrap socket
- some wires (wire wrap preferred)
- 10K, 3K3, 3K3 resistors
- 180 Ohm resistor, LED

depended on computer type and chosen interface address you will also need
a 74'139 and/or 2*74'04.



## CIA 8BIT INTERFACE (C64)

Description is for C64, differences with C128 are described in next part.

You need a CIA 6526 IC. Bend up pins 2-18, 23, 24, 39, 40 and solder the rest
to one of two CIAs that are already on the board. Now you must interface your
3rd CIA to system bus. There is a fast way - simply connect pin 23 (/CS signal)
to /IO1 or /IO2 on Expansion Port (pins 7 and 10 respectively). This way the
3rd CIA will be seen at $DExx or $DFxx memory pages. This is the easiest and
the worst way. By doing this you will sooner or later encounter serious problems
with cartridges. This is why I don't recommend it for anything more but testing
if the CIA#3 really works.

The best way to interface CIA#3 is to build a simple address decoder. If you
are willing to expand your C= it will be useful sooner or later. You don't
need to build full interface, only VIC part will be enough.

Get VIC (U7) chip out of the socket and bend pin 10 up. Do the same with SID
(U9) and its pin 8. Connect two wires to those bended pins. Connect also
another two wires to the corresponding pins on the board - in sockets. You may
try to trace the tracks and find more comfortable place to solder. If not
then the solder side of the board will be the safest choice. 
When you'll get those 4 signals connect everything as described below:

```
VIC pin #10 (board) -> IC pin 15
VIC pin #10 (chip)  -> IC pin 12
SID pin #8  (board) -> IC pin 1
SID pin #8  (chip)  -> IC pin 4

    from board - SID /CS 1   U   16 VCC (+5V)
                      A8 2       15 VIC /CS - from board
                      A9 3       14 A8
SID /CS on chip <- /D400 4       13 A9
                   /D500 5       12 /D000 -> VIC /CS - on chip
                   /D600 6       11 /D100
                   /D700 7       10 /D200
                     GND 8       9  /D300 -> CIA#3 /CS - pin 23
                          74'139
```

You will also have to connect pins 2+14 and 3+13 within 74'139. Those lines - A8
and A9 can be taken from CPU (U6) - pins 15 and 16 (respectively)

As you see you get 5 I/O page signals - for $D100, $D200, $D300, $D500,
$D600 and $D700. Pages $D5, $D6 or $D7 are generally a good place for
connecting second SID - you just solder one SID on another, without
pins 1-4 and 8. Then you solder two capacitors to pins 1-2 and 3-4
and /CS line from our address decoder to pin 8. If you want to have
a stereo SID then don't solder pins 27 together and build a copy of
amplifier from the board. You might also not solder pins 23 and 24
because these are POTX and POTY and might be used to mesaure resistance.

I used /D300 for my CIA#3 because it was the safest choice for me.
I recommend you doing the same.

So now, when you have two 16 bit ports usable you can wire the IDE socket to
CIA#3. I used port A for control and port B for data port. Below is the list
of connections.

```
    CIA#3          IDE
(9) PA7-------------A0 (35)
(8) PA6-------------A1 (33)
(7) PA5-------------A2 (36)
(6) PA4------------/WR (23)
(5) PA3------------/RD (25)
(4) PA2-----------/CS1 (38)
(3) PA1-----------/CS0 (37)
(2) PA0 not connected, free for use

(17) PB7-------------D7 (3)
(16) PB6-------------D6 (5)
(15) PB5-------------D5 (7)
(14) PB4-------------D4 (9)
(13) PB3-------------D3 (11)
(12) PB2-------------D2 (13)
(11) PB1-------------D1 (15)
(10) PB0-------------D0 (17)

(34) /RESET------/RESET (1)

GND------------GND (2,19,22,24,26,30,40 - one or all of them)
```

There are two more things to do:
- connect resistors as shown below, my interface worked fine without
  it, but ATA-3 specs say that this is needed
```
  DMARQ (21)--|3K3|--GND
  IORDY (27)--|3K3|--GND
  CSEL  (28)--|10K|--+5V
```

- connect /ACT (39) signal from IDE socket through 180 Ohm resistor and LED to +5V
  This is how LEDs are wired in IBM PC compatibles. Mount LED in a visible place of
  your computer case and write "HDD" under it.

Congratulations! The interface is complete and ready to use.



## CIA 8BIT INTERFACE (C128)

* 2023 update: see also this project https://github.com/ytmytm/c128-u3-replacement *

In C128 address decoding can be done easier.

Instead of using /IO1, or /IO2, or making internal decoder (which is generally
A Good Thing (tm)) /CS for CIA#3 can be taken from U3 (74'138), pin 12 - this is
unused and indicates I/O page $D7xx.

If you are going to build address decoder take VIC (U21) pin 13 instead of 10 for
/VICCS-chip. You do not have to search on board for /VICCS signal - it is easy
accessible on U11 pin 42. SID stuff remains the same (it is U5) with
similar exception - /SIDCS board signal can be found at U3 pin 15.

For A8/A9 lines you will need to reach Expansion Port or ROMs because of MMU
interference in this part of the bus.



## CIA 16 BIT VERSION

A place to solder upper 8 bits of data is needed. The most obvious choice is
to use CIA#1 or CIA#2 ports. CIA#2 port B seems to be the best - it is not
used by system. CIA#2 port A is used for disk drive communication and cannot
be used. CIA#1 ports A and B are utilized for keyboard scanning. I tried to
use port A for upper 8 bit transfer, but I went into lots of trouble with
keyboard etc. (routines worked from GEOS, but not from BASIC). More problems
arrive when trying to utilize 512 byte sectors in 256 byte world of C=
disk drives. Wasting a half of disk drive might sound bad, but all in all
20MB of my 40MB Conner is still a lot.

Pins D8..D15 in IDE socket have even numbers 4, 6, 8... 18 (respectively),
you already know pin numbers of CIA ports A and B.



## 8255 INTERFACE

This part is only about interfacing 8255 with C64/128. The rest is exactly
the same as in P. Faasse's article.

The project described here comes for Commodore&Amiga 12/94 magazine. I have
built it on my C128 and partially failed (or succeeded, it depends :). Simply
I couldn't set the ports into output mode. I don't know why. I don't even
know if this will work on C64. Don't blame if you will waste whole day building
it for nothing, as I did :).

You need a 8255 and two 74'04 inverters. One inverter is needed for IDE
interfacing and the second is needed for interfacing 8255 to C= system bus.
Address decoding is realized in the very same way as in CIA version. The select
signal will be called /CS later.

Here is the list of connections: |> means that the line goes through inverter.

```

C64/128	bus                       8255
                               +---------
D0\                       / 34 |D0
.------------------------------|.
.------------------------------|.
D7/                       \ 27 |D7
                               |
R/W--------+----------------36 |/WR
           |                   |
           +----1-|>-2-------5 |/RD
                               |
A0------3-|>-4---5-|>-6------9 |A0
A1------9-|>-8--11-|>-10-----8 |A1
                               |
/RESET----------13-|>-12----35 |RESET  
                               |
/CS--------------------------6 |/CS
                               |
+5V---+---------------------26 |+5V
GND---|-+--------------------7 |GND
      | |                      +----------
      | +-7 (74'04 GND)
      +--14 (74'04 +5V)
```

Control lines on the left side (except /CS which comes from the address decoder) are
easily accessible in Expansion Port or directly from CPU chip. See pinouts section
for more.

Port pins from 8255 should be connected as in P. Faasse's article: port A through
inverter for control, port B for lower 8 bits, port C for upper 8 bits.



## IRQ/NMI

IDE device (be it hard disk drive or CD-ROM) can issue interrupt request upon
completing the command. I didn't even try to do it because I see very low
usage of this.
Chris Ward on his IDE schematic has it included but with notice that it is
untested.



## ABOUT PROGRAMMING IDE

See example files included in archive together with this document.
Always check errors and status flags before doing anything.



## PINOUTS

IDE connector
(see P. Faasse's article for full description of pins, information here should be
enough to solder wires according to the list)

(This is view on front of IDE cable plug or back of IDE cable socket)

```
1        U         39 odd-numbered pins
....................
.........o..........
2                  40 even-numbered pins
```

as you see pin 20 is missing - this should be the key for you. There is also
another key - a notch in socket/plug which prevents even more from misconnecting.
Note that on every IDE device the socket is oriented as above (notch at the top and
missing pin at the bottom), regardless of its orientation to drive board.

```
CIA 6526

VSS 1     U     40 CNT
PA0 2           39 SP
PA1 3           38 A0
PA2 4           37 A1
PA3 5           36 A2
PA4 6           35 A3
PA5 7           34 /RESET
PA6 8           33 D0
PA7 9           32 D1
PB0 10          31 D2
PB1 11          30 D3
PB2 12          29 D4
PB3 13          28 D5
PB4 14          27 D6
PB5 15          26 D7
PB6 16          25 phi2
PB7 17          24 /FLAG
/PC 18          23 /CS
TOD 19          22 R/W
VCC 20          21 /IRQ

8255

PA3 1     U     40 PA4
PA2 2           39 PA5
PA1 3           38 PA6
PA0 4           37 PA7
/RD 5           36 /WR
/CS 6           35 RESET
GND 7           34 D0
 A1 8           33 D1
 A0 9           32 D2
PC7 10          31 D3
PC6 11          30 D4
PC5 12          29 D5
PC4 13          28 D6
PC0 14          27 D7
PC1 15          26 +5V
PC2 16          25 PB7
PC3 17          24 PB6
PB0 18          23 PB5
PB1 19          22 PB4
PB2 20          21 PB3

Expansion Port (looking from back of C64/128)

22....................1
 ZYXWVUTSRPNMLKJHFEDCBA

 1 GND                  A GND
 2 +5V                  B /ROMH
 3 +5V                  C /RESET
 4 /IRQ                 D /NMI
 5 R/W                  E phi2
 6 dot clock            F A15
 7 /IO1                 H A14
 8 /GAME                ...
 9 /EXROM               X A1
10 /IO2                 Y A0
11 /ROML                Z GND
12 BA
13 /DMA
14 D7
15 D6
...
20 D1
21 D0
22 GND

```

