# An Arduino compatible CLI environment

## Setup

Get the arduino libraries in place (slightly modified for this purpose):

    git clone avr-arduino-cli
    cd avr-arduino-cli
    cp -r arduino /usr/local/share/

Sort out your prefered build tools, eg:

    brew tap larsimmisch/avr
    brew install avr-libc
    brew install avrdude --with-usb


## Writing your AVR project

As you would a normal Arduino project but save as a ```.cpp``` extension instead of ```.ino```, and take care with the headers. Always start with :

    #include <Arduino.h>

Then adjust the path for any libraries which are usually held in a parent folder of the same name, eg:

    #include <Wire/Wire.h>
    #include <SPI/SPI.h>

But sometimes are kept within a ```src``` sub folder of that parent folder, eg:

    #include <LiquidCrystal/src/LiquidCrystal.h>
    #include <Ethernet/src/Ethernet.h>

Careful with 3rd party libraries, eg:

    #include <TFT/src/utility/Adafruit_GFX.h>
    #include <TFT/src/utility/Adafruit_SSD1306.h>

By putting your standard Arduino functions:

    void setup(){
    }

and

    void loop(){
    }

at the end of the file, it saves having to prototype the functions and therefore far quicker to lift example Arduino sketches as they've been written.

#### Remember : The Arduino IDE was adding ```#include<Arduino.h>``` at the beginning, and also the prototypes for you!

As with the Arduino IDE, this build process then automatically adds :

    int main(void)
    {
        init();

        setup();

        for (;;) {
            loop();
            if (serialEventRun) serialEventRun();
        }

        return 0;
    }

which will excecute your code.


## Build

Edit the ```Makefile```

    TARGET=your_project.cpp
    # Update DEVICE to the chip you are using. Arduino Uno based on atmega328p
    # Update PROGRAMMER to the ISP programmer you are using to flash the chip.
    # Update CLOCK if the cystal is set to different speed, OR if using internal clock for the project.

then build with:

    make

You will see all the libraries getting built and linked into a ```.elf``` and then a ```.hex``` file for your selected chip, which can then by flashed with:

    make flash

Or in one go:

    make readfuses clean all flash

Now we can get some proper work done with a [decent text editor](http://www.sublimetext.com/), version control and using [as many chips as we need](http://www.hobbytronics.co.uk/atmega328?keyword=atmega) rather than buying an Arduino each time.

:-)


