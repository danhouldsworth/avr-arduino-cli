#Project AVR program

## Installation

From source:

* Download latest source tarball
* Or clone it from GitHub: git clone git://github.com/amperka/ino.git
* Do make install to perform installation under /usr/local

## Objective
* Gain the ability to develope Arduino outside of the IDE - hence speeding learning and resuable code.
* Better understanding of embedded microcontrollers Bootloader, Fuses, Ports, Flash, Eeprom - useful for Arducopter and custom projects
* Speed up ability to make custom embedded devices outside of Arduino board. Easier to make modular devices that could be open source hacked
* DECISION - Will move away ARDUINO library dependancy. PROS - will force deeper understanding, and eventually will lead to much more simplicity of projects. CONS - will be uncompatible with ARDUINO libraries without always modifiying if at all. REVERSE DECISION!!

## Milestones
* Communicate with ATmega via serial UART - *DONE*
* Set up build tools (make, gcc, avrdude) tailored for the ATmega - *DONE*
* Get sample fuses, bootloaders, program files to upload - *DONE* (*Booterloader?*)
* Get template Makefile so can compile, burn, debug(!), download(!) - *DONE*
* Test avrdude with USB->UART device - ***TBC***
* Test configure Makefile with correct USB->UART device - ***TBC***
* `avr-project Demo` - *DONE*
* edit accordingly with appropriate headers - *DONE*
* `make` [configure Makefile ATmega code first] - *DONE*
* `make flash` [configure Makefile avrdude programmer first] - *DONE*
* `make fuse` [configure Makefile fuse settings first] - *DONE*

### Program
* Plug in Arduino Uno programmer and detect. - *DONE*
* Use `ls /dev/tty.usb*` out of interest and then set Makefilee to PROGRAMMER = -c arduino - *DONE*
* Plug in Pololu programmer and detect. - *DONE*
* Use `ls /dev/tty.usb*` to get the port number for `AVRDUDE` - *DONE*
* Test upload of a basic blink - *DONE*
* Experiment with main.c and check effect - *DONE*
* Change DDRD to DDR4 - *DONE* (LED only works on pin 4) *DONE*
* Test upload of a SPI display - *DONE*

### Questions
* Vdd vs Vbus? On programmer, can only connect if powered by Vbus (or by USB from same device - which is the same). Is the voltage too different? - *VDD is input, and will diconnect if differs from Vbus*
* Is this uploading a bootloader? Does it work on blank chip? - *No* A bootloader is loaded using flash also / instead, which then allows for subsequent semi-temporary uploads of applications via UART to partitioned flash.

*

### Fuses (see 6)
* Confirm correct fuses. - *DONE* **Optiboot/Makefile shows atmega328 >> HFUSE = DE, LFUSE = FF, EFUSE = 05 **
* Read the fuses and compare. - *TBC*
* Experiment with internal clock rather than external (basic blink code only) - *TBC*
* Experiment using internal clock with 3rd party devices such as SPI display, RFID reader, LCD display - *TBC*

### Bootloader *EDIT* - as ISP upload is so fast and easy, I no longer need a bootloader to upload via UART. *ABORT*
* Test upload of a standard Optiboot - *TBC*
* Modify Optiboot to do, say, 10 flashes on reset. Compile, build, burn - *TBC*
* Test can still upload a variety of sketches - *TBC*

### Debug
* Test download of basic blink and compare
* Add comments and see if can see in dissassemble

### Hardware
* Make breadboard device than can quickly plug in programmer - *DONE*


# Resources :
1. http://www.ladyada.net/learn/avr/avrdude.html
2. http://www.engbedded.com/fusecalc/ (no 16MHz..??)
3. https://creative.adobe.com/join/starter
4. http://www.nongnu.org/avr-libc/
5. file:///usr/local/CrossPack-AVR/manual/gettingstarted.html
6. See /usr/local/CrossPack-AVR/avr/include/avr/iom328p.h
7. https://github.com/amperka/ino
8. http://inotool.org/
