# TARGET = main.cpp
TARGET = oled_main.cpp
# TARGET = LiquidCrystal_main.cpp
# TARGET = WebClient_main.cpp
# TARGET = serial_OLED.cpp
# TARGET = consoleLog.cpp


ARDUINO   = /usr/local/share/arduino/hardware/arduino/cores/arduino
LIBRARIES = /usr/local/share/arduino/hardware/arduino/libraries

# DEVICE = atmega328
DEVICE = atmega328p
CLOCK = 16000000
PROGRAMMER = -c arduino -P /dev/tty.usbmodem1411
# PROGRAMMER = -c avrisp2 -P /dev/tty.usbmodem00065771
AVRDUDE = avrdude $(PROGRAMMER) -p $(DEVICE)

CC = @avr-gcc
CXX = @avr-g++
LINK = @avr-gcc

ENVS = -D "__PROG_TYPES_COMPAT__"
ENVS += -D "ARDUINO=101"

COMPILE_OPTS = $(ENVS)
# COMPILE_OPTS += -Wall
COMPILE_OPTS += -w
COMPILE_OPTS += -ffunction-sections
COMPILE_OPTS += -Os -DF_CPU=$(CLOCK) -mmcu=$(DEVICE)
COMPILE_OPTS += -I$(ARDUINO) -I$(LIBRARIES)

LINK_OPTS = -Wl,-gc-sections

CC_ONLY_OPTS = -std=gnu99
CXX_ONLY_OPTS = -std=c++0x
# CXX_ONLY_OPTS += -fpermissive

COMPILE = $(CC) $(CC_ONLY_OPTS) $(COMPILE_OPTS)
COMPILEXX = $(CXX) $(CXX_ONLY_OPTS) $(COMPILE_OPTS)
LINKER = $(LINK) $(CC_ONLY_OPTS) $(COMPILE_OPTS) $(LINK_OPTS)

FUSES = -U hfuse:w:0xdE:m -U efuse:w:0x05:m -U lfuse:w:0xFF:m

# symbolic targets:
all: build

build: clean sources cxxsources main main.elf main.hex

sources:
	#
	# Compiling main.c and core c files...
	$(COMPILE) -c $(ARDUINO)/wiring_digital.c -o tmp/wiring_digital.o
	$(COMPILE) -c $(ARDUINO)/wiring_analog.c -o tmp/wiring_analog.o
	$(COMPILE) -c $(ARDUINO)/wiring_pulse.c -o tmp/wiring_pulse.o
	$(COMPILE) -c $(ARDUINO)/wiring_shift.c -o tmp/wiring_shift.o
	$(COMPILE) -c $(ARDUINO)/hooks.c -o tmp/hooks.o
	$(COMPILE) -c $(ARDUINO)/wiring.c -o tmp/wiring.o
	$(COMPILE) -c $(ARDUINO)/WInterrupts.c -o tmp/WInterrupts.o
	#...done
	# Compiling Wire (.c) library...
	$(COMPILE) -c $(LIBRARIES)/Wire/utility/twi.c -o tmp/twi.o
	#...done
	# All .c files built successfully!

cxxsources:
	#
	# Compiling core .cpp files...
	$(COMPILEXX) -c $(ARDUINO)/main.cpp -o tmp/main.o
	$(COMPILEXX) -c $(ARDUINO)/WMath.cpp -o tmp/WMath.o
	$(COMPILEXX) -c $(ARDUINO)/Tone.cpp -o tmp/Tone.o
	$(COMPILEXX) -c $(ARDUINO)/IPAddress.cpp -o tmp/IPAddress.o
	$(COMPILEXX) -c $(ARDUINO)/new.cpp -o tmp/new.o
	$(COMPILEXX) -c $(ARDUINO)/USBCore.cpp -o tmp/USBCore.o
	$(COMPILEXX) -c $(ARDUINO)/Stream.cpp -o tmp/Stream.o
	$(COMPILEXX) -c $(ARDUINO)/CDC.cpp -o tmp/CDC.o
	$(COMPILEXX) -c $(ARDUINO)/HID.cpp -o tmp/HID.o
	$(COMPILEXX) -c $(ARDUINO)/HardwareSerial.cpp -o tmp/HardwareSerial.o
	$(COMPILEXX) -c $(ARDUINO)/WString.cpp -o tmp/WString.o
	$(COMPILEXX) -c $(ARDUINO)/Print.cpp -o tmp/Print.o
	#...done
	# Compiling Wire (.cpp) library...
	$(COMPILEXX) -c $(LIBRARIES)/Wire/Wire.cpp -o tmp/Wire.o
	#...done
	# Compiling SPI library...
	$(COMPILEXX) -c $(LIBRARIES)/SPI/SPI.cpp -o tmp/SPI.o
	#...done
	# Compiling Stepper library...
	$(COMPILEXX) -c $(LIBRARIES)/Stepper/src/Stepper.cpp -o tmp/Stepper.o
	#...done
	# Compiling LiquidCrystal library...
	$(COMPILEXX) -c $(LIBRARIES)/LiquidCrystal/src/LiquidCrystal.cpp -o tmp/LiquidCrystal.o
	#...done
	# Compiling Ethernet library...
	$(COMPILEXX) -c $(LIBRARIES)/Ethernet/src/Ethernet.cpp -o tmp/Ethernet.o
	$(COMPILEXX) -c $(LIBRARIES)/Ethernet/src/EthernetClient.cpp -o tmp/EthernetClient.o
	$(COMPILEXX) -c $(LIBRARIES)/Ethernet/src/EthernetServer.cpp -o tmp/EthernetServer.o
	$(COMPILEXX) -c $(LIBRARIES)/Ethernet/src/EthernetUdp.cpp -o tmp/EthernetUdp.o
	$(COMPILEXX) -c $(LIBRARIES)/Ethernet/src/Dns.cpp -o tmp/Dns.o
	$(COMPILEXX) -c $(LIBRARIES)/Ethernet/src/Dhcp.cpp -o tmp/Dhcp.o
	$(COMPILEXX) -c $(LIBRARIES)/Ethernet/arch/avr/utility/socket.cpp -o tmp/socket.o
	$(COMPILEXX) -c $(LIBRARIES)/Ethernet/arch/avr/utility/w5100.cpp -o tmp/w5100.o
	#...done
	# Compiling Servo library...
	$(COMPILEXX) -c $(LIBRARIES)/Servo/arch/avr/Servo.cpp -o tmp/Servo.o
	#...done
	# Compiling EEPROM library...
	$(COMPILEXX) -c $(LIBRARIES)/EEPROM/EEPROM.cpp -o tmp/EEPROM.o
	#...done
	# Compiling Adafruit SSD1306 OLED library (From Arduino/Libraries/TFT) ...
	$(COMPILEXX) -c $(LIBRARIES)/TFT/src/utility/Adafruit_SSD1306.cpp -o tmp/Adafruit_SSD1306.o
	$(COMPILEXX) -c $(LIBRARIES)/TFT/src/utility/Adafruit_GFX.cpp -o tmp/Adafruit_GFX.o
	#...done
	# All .cpp files built successfully!

main:
	#
	# Building $(TARGET)...
	$(COMPILEXX) -c $(TARGET) -o tmp/target.o
	#...done

main.elf:
	#
	# Building main.elf...
	$(LINKER) tmp/target.o \
		tmp/main.o \
		tmp/wiring.o \
		tmp/hooks.o \
		tmp/wiring_digital.o \
		tmp/wiring_analog.o \
		tmp/wiring_pulse.o \
		tmp/wiring_shift.o \
		tmp/WMath.o \
		tmp/Tone.o \
		tmp/WInterrupts.o \
		tmp/new.o \
		tmp/USBCore.o \
		tmp/CDC.o \
		tmp/HID.o \
		tmp/WString.o \
		tmp/Stream.o \
		tmp/Print.o \
		tmp/HardwareSerial.o \
		tmp/IPAddress.o \
		tmp/twi.o \
		tmp/Wire.o \
		tmp/SPI.o \
		tmp/Stepper.o \
		tmp/LiquidCrystal.o \
		tmp/Ethernet.o \
		tmp/EthernetServer.o \
		tmp/EthernetClient.o \
		tmp/EthernetUdp.o \
		tmp/Dns.o \
		tmp/Dhcp.o \
		tmp/socket.o \
		tmp/w5100.o \
		tmp/servo.o \
		tmp/EEPROM.o \
		tmp/Adafruit_SSD1306.o \
		tmp/Adafruit_GFX.o \
		-o main.elf
	#...done
	# main.elf built successfully!

main.hex:
	#
	# Building main.hex...
	@rm -f main.hex
	@avr-objcopy -j .text -j .data -O ihex main.elf main.hex
	@avr-size --format=avr --mcu=$(DEVICE) main.hex
	#...done
	# main.hex ready for upload!
	#

clean:
	#
	# Cleaning...
	@rm -f main.hex main.elf hfuse.hex efuse.hex lfuse.hex
	@touch tmp/avoid_error_from_empty_dir
	@rm tmp/*
	#...done.

flash: main main.elf main.hex
	$(AVRDUDE) -U flash:w:main.hex:i

setfuse:
	$(AVRDUDE) $(FUSES)

readfuse:
	$(AVRDUDE) -U hfuse:r:hfuse.hex:i -U lfuse:r:lfuse.hex:i -U efuse:r:efuse.hex:i
	cat hfuse.hex
	cat efuse.hex
	cat lfuse.hex
