























.build/uno/EEPROM/EEPROM.o : /Applications/Arduino.app/Contents/Resources/Java/libraries/EEPROM/EEPROM.cpp
	@echo EEPROM/EEPROM.cpp
	@mkdir -p .build/uno/EEPROM
	@/Applications/Arduino.app/Contents/Resources/Java/hardware/tools/avr/bin/avr-g++ -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=105 -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino -ffunction-sections -fdata-sections -g -Os -w -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/variants/standard -I/Applications/Arduino.app/Contents/Resources/Java/libraries/EEPROM -Ilib/LiquidCrystal -Ilib/Wire -Ilib/Wire/utility -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino/avr-libc -fno-exceptions  -o $@ -c /Applications/Arduino.app/Contents/Resources/Java/libraries/EEPROM/EEPROM.cpp
include .build/uno/EEPROM/EEPROM.d



.build/uno/EEPROM/libEEPROM.a : .build/uno/EEPROM/EEPROM.o
	@echo Linking libEEPROM.a
	@/Applications/Arduino.app/Contents/Resources/Java/hardware/tools/avr/bin/avr-ar rcs $@ $^












.build/uno/LiquidCrystal/Adafruit_MCP23008.o : lib/LiquidCrystal/Adafruit_MCP23008.cpp
	@echo LiquidCrystal/Adafruit_MCP23008.cpp
	@mkdir -p .build/uno/LiquidCrystal
	@/Applications/Arduino.app/Contents/Resources/Java/hardware/tools/avr/bin/avr-g++ -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=105 -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino -ffunction-sections -fdata-sections -g -Os -w -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/variants/standard -I/Applications/Arduino.app/Contents/Resources/Java/libraries/EEPROM -Ilib/LiquidCrystal -Ilib/Wire -Ilib/Wire/utility -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino/avr-libc -fno-exceptions  -o $@ -c lib/LiquidCrystal/Adafruit_MCP23008.cpp
include .build/uno/LiquidCrystal/Adafruit_MCP23008.d

.build/uno/LiquidCrystal/LiquidCrystal.o : lib/LiquidCrystal/LiquidCrystal.cpp
	@echo LiquidCrystal/LiquidCrystal.cpp
	@mkdir -p .build/uno/LiquidCrystal
	@/Applications/Arduino.app/Contents/Resources/Java/hardware/tools/avr/bin/avr-g++ -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=105 -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino -ffunction-sections -fdata-sections -g -Os -w -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/variants/standard -I/Applications/Arduino.app/Contents/Resources/Java/libraries/EEPROM -Ilib/LiquidCrystal -Ilib/Wire -Ilib/Wire/utility -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino/avr-libc -fno-exceptions  -o $@ -c lib/LiquidCrystal/LiquidCrystal.cpp
include .build/uno/LiquidCrystal/LiquidCrystal.d



.build/uno/LiquidCrystal/libLiquidCrystal.a : .build/uno/LiquidCrystal/Adafruit_MCP23008.o .build/uno/LiquidCrystal/LiquidCrystal.o
	@echo Linking libLiquidCrystal.a
	@/Applications/Arduino.app/Contents/Resources/Java/hardware/tools/avr/bin/avr-ar rcs $@ $^







.build/uno/Wire/utility/twi.o : lib/Wire/utility/twi.c
	@echo Wire/utility/twi.c
	@mkdir -p .build/uno/Wire/utility
	@/Applications/Arduino.app/Contents/Resources/Java/hardware/tools/avr/bin/avr-gcc -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=105 -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino -ffunction-sections -fdata-sections -g -Os -w -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/variants/standard -I/Applications/Arduino.app/Contents/Resources/Java/libraries/EEPROM -Ilib/LiquidCrystal -Ilib/Wire -Ilib/Wire/utility -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino/avr-libc   -o $@ -c lib/Wire/utility/twi.c
include .build/uno/Wire/utility/twi.d






.build/uno/Wire/Wire.o : lib/Wire/Wire.cpp
	@echo Wire/Wire.cpp
	@mkdir -p .build/uno/Wire
	@/Applications/Arduino.app/Contents/Resources/Java/hardware/tools/avr/bin/avr-g++ -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=105 -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino -ffunction-sections -fdata-sections -g -Os -w -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/variants/standard -I/Applications/Arduino.app/Contents/Resources/Java/libraries/EEPROM -Ilib/LiquidCrystal -Ilib/Wire -Ilib/Wire/utility -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino/avr-libc -fno-exceptions  -o $@ -c lib/Wire/Wire.cpp
include .build/uno/Wire/Wire.d



.build/uno/Wire/libWire.a : .build/uno/Wire/utility/twi.o .build/uno/Wire/Wire.o
	@echo Linking libWire.a
	@/Applications/Arduino.app/Contents/Resources/Java/hardware/tools/avr/bin/avr-ar rcs $@ $^







.build/uno/arduino/avr-libc/malloc.o : /Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino/avr-libc/malloc.c
	@echo arduino/avr-libc/malloc.c
	@mkdir -p .build/uno/arduino/avr-libc
	@/Applications/Arduino.app/Contents/Resources/Java/hardware/tools/avr/bin/avr-gcc -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=105 -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino -ffunction-sections -fdata-sections -g -Os -w -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/variants/standard -I/Applications/Arduino.app/Contents/Resources/Java/libraries/EEPROM -Ilib/LiquidCrystal -Ilib/Wire -Ilib/Wire/utility -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino/avr-libc   -o $@ -c /Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino/avr-libc/malloc.c
include .build/uno/arduino/avr-libc/malloc.d

.build/uno/arduino/avr-libc/realloc.o : /Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino/avr-libc/realloc.c
	@echo arduino/avr-libc/realloc.c
	@mkdir -p .build/uno/arduino/avr-libc
	@/Applications/Arduino.app/Contents/Resources/Java/hardware/tools/avr/bin/avr-gcc -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=105 -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino -ffunction-sections -fdata-sections -g -Os -w -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/variants/standard -I/Applications/Arduino.app/Contents/Resources/Java/libraries/EEPROM -Ilib/LiquidCrystal -Ilib/Wire -Ilib/Wire/utility -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino/avr-libc   -o $@ -c /Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino/avr-libc/realloc.c
include .build/uno/arduino/avr-libc/realloc.d

.build/uno/arduino/WInterrupts.o : /Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino/WInterrupts.c
	@echo arduino/WInterrupts.c
	@mkdir -p .build/uno/arduino
	@/Applications/Arduino.app/Contents/Resources/Java/hardware/tools/avr/bin/avr-gcc -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=105 -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino -ffunction-sections -fdata-sections -g -Os -w -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/variants/standard -I/Applications/Arduino.app/Contents/Resources/Java/libraries/EEPROM -Ilib/LiquidCrystal -Ilib/Wire -Ilib/Wire/utility -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino/avr-libc   -o $@ -c /Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino/WInterrupts.c
include .build/uno/arduino/WInterrupts.d

.build/uno/arduino/wiring.o : /Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino/wiring.c
	@echo arduino/wiring.c
	@mkdir -p .build/uno/arduino
	@/Applications/Arduino.app/Contents/Resources/Java/hardware/tools/avr/bin/avr-gcc -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=105 -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino -ffunction-sections -fdata-sections -g -Os -w -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/variants/standard -I/Applications/Arduino.app/Contents/Resources/Java/libraries/EEPROM -Ilib/LiquidCrystal -Ilib/Wire -Ilib/Wire/utility -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino/avr-libc   -o $@ -c /Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino/wiring.c
include .build/uno/arduino/wiring.d

.build/uno/arduino/wiring_analog.o : /Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino/wiring_analog.c
	@echo arduino/wiring_analog.c
	@mkdir -p .build/uno/arduino
	@/Applications/Arduino.app/Contents/Resources/Java/hardware/tools/avr/bin/avr-gcc -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=105 -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino -ffunction-sections -fdata-sections -g -Os -w -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/variants/standard -I/Applications/Arduino.app/Contents/Resources/Java/libraries/EEPROM -Ilib/LiquidCrystal -Ilib/Wire -Ilib/Wire/utility -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino/avr-libc   -o $@ -c /Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino/wiring_analog.c
include .build/uno/arduino/wiring_analog.d

.build/uno/arduino/wiring_digital.o : /Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino/wiring_digital.c
	@echo arduino/wiring_digital.c
	@mkdir -p .build/uno/arduino
	@/Applications/Arduino.app/Contents/Resources/Java/hardware/tools/avr/bin/avr-gcc -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=105 -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino -ffunction-sections -fdata-sections -g -Os -w -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/variants/standard -I/Applications/Arduino.app/Contents/Resources/Java/libraries/EEPROM -Ilib/LiquidCrystal -Ilib/Wire -Ilib/Wire/utility -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino/avr-libc   -o $@ -c /Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino/wiring_digital.c
include .build/uno/arduino/wiring_digital.d

.build/uno/arduino/wiring_pulse.o : /Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino/wiring_pulse.c
	@echo arduino/wiring_pulse.c
	@mkdir -p .build/uno/arduino
	@/Applications/Arduino.app/Contents/Resources/Java/hardware/tools/avr/bin/avr-gcc -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=105 -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino -ffunction-sections -fdata-sections -g -Os -w -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/variants/standard -I/Applications/Arduino.app/Contents/Resources/Java/libraries/EEPROM -Ilib/LiquidCrystal -Ilib/Wire -Ilib/Wire/utility -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino/avr-libc   -o $@ -c /Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino/wiring_pulse.c
include .build/uno/arduino/wiring_pulse.d

.build/uno/arduino/wiring_shift.o : /Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino/wiring_shift.c
	@echo arduino/wiring_shift.c
	@mkdir -p .build/uno/arduino
	@/Applications/Arduino.app/Contents/Resources/Java/hardware/tools/avr/bin/avr-gcc -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=105 -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino -ffunction-sections -fdata-sections -g -Os -w -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/variants/standard -I/Applications/Arduino.app/Contents/Resources/Java/libraries/EEPROM -Ilib/LiquidCrystal -Ilib/Wire -Ilib/Wire/utility -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino/avr-libc   -o $@ -c /Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino/wiring_shift.c
include .build/uno/arduino/wiring_shift.d






.build/uno/arduino/CDC.o : /Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino/CDC.cpp
	@echo arduino/CDC.cpp
	@mkdir -p .build/uno/arduino
	@/Applications/Arduino.app/Contents/Resources/Java/hardware/tools/avr/bin/avr-g++ -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=105 -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino -ffunction-sections -fdata-sections -g -Os -w -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/variants/standard -I/Applications/Arduino.app/Contents/Resources/Java/libraries/EEPROM -Ilib/LiquidCrystal -Ilib/Wire -Ilib/Wire/utility -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino/avr-libc -fno-exceptions  -o $@ -c /Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino/CDC.cpp
include .build/uno/arduino/CDC.d

.build/uno/arduino/HardwareSerial.o : /Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino/HardwareSerial.cpp
	@echo arduino/HardwareSerial.cpp
	@mkdir -p .build/uno/arduino
	@/Applications/Arduino.app/Contents/Resources/Java/hardware/tools/avr/bin/avr-g++ -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=105 -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino -ffunction-sections -fdata-sections -g -Os -w -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/variants/standard -I/Applications/Arduino.app/Contents/Resources/Java/libraries/EEPROM -Ilib/LiquidCrystal -Ilib/Wire -Ilib/Wire/utility -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino/avr-libc -fno-exceptions  -o $@ -c /Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino/HardwareSerial.cpp
include .build/uno/arduino/HardwareSerial.d

.build/uno/arduino/HID.o : /Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino/HID.cpp
	@echo arduino/HID.cpp
	@mkdir -p .build/uno/arduino
	@/Applications/Arduino.app/Contents/Resources/Java/hardware/tools/avr/bin/avr-g++ -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=105 -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino -ffunction-sections -fdata-sections -g -Os -w -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/variants/standard -I/Applications/Arduino.app/Contents/Resources/Java/libraries/EEPROM -Ilib/LiquidCrystal -Ilib/Wire -Ilib/Wire/utility -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino/avr-libc -fno-exceptions  -o $@ -c /Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino/HID.cpp
include .build/uno/arduino/HID.d

.build/uno/arduino/IPAddress.o : /Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino/IPAddress.cpp
	@echo arduino/IPAddress.cpp
	@mkdir -p .build/uno/arduino
	@/Applications/Arduino.app/Contents/Resources/Java/hardware/tools/avr/bin/avr-g++ -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=105 -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino -ffunction-sections -fdata-sections -g -Os -w -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/variants/standard -I/Applications/Arduino.app/Contents/Resources/Java/libraries/EEPROM -Ilib/LiquidCrystal -Ilib/Wire -Ilib/Wire/utility -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino/avr-libc -fno-exceptions  -o $@ -c /Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino/IPAddress.cpp
include .build/uno/arduino/IPAddress.d

.build/uno/arduino/main.o : /Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino/main.cpp
	@echo arduino/main.cpp
	@mkdir -p .build/uno/arduino
	@/Applications/Arduino.app/Contents/Resources/Java/hardware/tools/avr/bin/avr-g++ -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=105 -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino -ffunction-sections -fdata-sections -g -Os -w -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/variants/standard -I/Applications/Arduino.app/Contents/Resources/Java/libraries/EEPROM -Ilib/LiquidCrystal -Ilib/Wire -Ilib/Wire/utility -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino/avr-libc -fno-exceptions  -o $@ -c /Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino/main.cpp
include .build/uno/arduino/main.d

.build/uno/arduino/new.o : /Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino/new.cpp
	@echo arduino/new.cpp
	@mkdir -p .build/uno/arduino
	@/Applications/Arduino.app/Contents/Resources/Java/hardware/tools/avr/bin/avr-g++ -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=105 -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino -ffunction-sections -fdata-sections -g -Os -w -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/variants/standard -I/Applications/Arduino.app/Contents/Resources/Java/libraries/EEPROM -Ilib/LiquidCrystal -Ilib/Wire -Ilib/Wire/utility -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino/avr-libc -fno-exceptions  -o $@ -c /Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino/new.cpp
include .build/uno/arduino/new.d

.build/uno/arduino/Print.o : /Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino/Print.cpp
	@echo arduino/Print.cpp
	@mkdir -p .build/uno/arduino
	@/Applications/Arduino.app/Contents/Resources/Java/hardware/tools/avr/bin/avr-g++ -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=105 -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino -ffunction-sections -fdata-sections -g -Os -w -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/variants/standard -I/Applications/Arduino.app/Contents/Resources/Java/libraries/EEPROM -Ilib/LiquidCrystal -Ilib/Wire -Ilib/Wire/utility -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino/avr-libc -fno-exceptions  -o $@ -c /Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino/Print.cpp
include .build/uno/arduino/Print.d

.build/uno/arduino/Stream.o : /Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino/Stream.cpp
	@echo arduino/Stream.cpp
	@mkdir -p .build/uno/arduino
	@/Applications/Arduino.app/Contents/Resources/Java/hardware/tools/avr/bin/avr-g++ -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=105 -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino -ffunction-sections -fdata-sections -g -Os -w -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/variants/standard -I/Applications/Arduino.app/Contents/Resources/Java/libraries/EEPROM -Ilib/LiquidCrystal -Ilib/Wire -Ilib/Wire/utility -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino/avr-libc -fno-exceptions  -o $@ -c /Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino/Stream.cpp
include .build/uno/arduino/Stream.d

.build/uno/arduino/Tone.o : /Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino/Tone.cpp
	@echo arduino/Tone.cpp
	@mkdir -p .build/uno/arduino
	@/Applications/Arduino.app/Contents/Resources/Java/hardware/tools/avr/bin/avr-g++ -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=105 -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino -ffunction-sections -fdata-sections -g -Os -w -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/variants/standard -I/Applications/Arduino.app/Contents/Resources/Java/libraries/EEPROM -Ilib/LiquidCrystal -Ilib/Wire -Ilib/Wire/utility -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino/avr-libc -fno-exceptions  -o $@ -c /Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino/Tone.cpp
include .build/uno/arduino/Tone.d

.build/uno/arduino/USBCore.o : /Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino/USBCore.cpp
	@echo arduino/USBCore.cpp
	@mkdir -p .build/uno/arduino
	@/Applications/Arduino.app/Contents/Resources/Java/hardware/tools/avr/bin/avr-g++ -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=105 -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino -ffunction-sections -fdata-sections -g -Os -w -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/variants/standard -I/Applications/Arduino.app/Contents/Resources/Java/libraries/EEPROM -Ilib/LiquidCrystal -Ilib/Wire -Ilib/Wire/utility -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino/avr-libc -fno-exceptions  -o $@ -c /Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino/USBCore.cpp
include .build/uno/arduino/USBCore.d

.build/uno/arduino/WMath.o : /Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino/WMath.cpp
	@echo arduino/WMath.cpp
	@mkdir -p .build/uno/arduino
	@/Applications/Arduino.app/Contents/Resources/Java/hardware/tools/avr/bin/avr-g++ -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=105 -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino -ffunction-sections -fdata-sections -g -Os -w -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/variants/standard -I/Applications/Arduino.app/Contents/Resources/Java/libraries/EEPROM -Ilib/LiquidCrystal -Ilib/Wire -Ilib/Wire/utility -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino/avr-libc -fno-exceptions  -o $@ -c /Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino/WMath.cpp
include .build/uno/arduino/WMath.d

.build/uno/arduino/WString.o : /Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino/WString.cpp
	@echo arduino/WString.cpp
	@mkdir -p .build/uno/arduino
	@/Applications/Arduino.app/Contents/Resources/Java/hardware/tools/avr/bin/avr-g++ -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=105 -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino -ffunction-sections -fdata-sections -g -Os -w -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/variants/standard -I/Applications/Arduino.app/Contents/Resources/Java/libraries/EEPROM -Ilib/LiquidCrystal -Ilib/Wire -Ilib/Wire/utility -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino/avr-libc -fno-exceptions  -o $@ -c /Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino/WString.cpp
include .build/uno/arduino/WString.d



.build/uno/arduino/libarduino.a : .build/uno/arduino/avr-libc/malloc.o .build/uno/arduino/avr-libc/realloc.o .build/uno/arduino/WInterrupts.o .build/uno/arduino/wiring.o .build/uno/arduino/wiring_analog.o .build/uno/arduino/wiring_digital.o .build/uno/arduino/wiring_pulse.o .build/uno/arduino/wiring_shift.o .build/uno/arduino/CDC.o .build/uno/arduino/HardwareSerial.o .build/uno/arduino/HID.o .build/uno/arduino/IPAddress.o .build/uno/arduino/main.o .build/uno/arduino/new.o .build/uno/arduino/Print.o .build/uno/arduino/Stream.o .build/uno/arduino/Tone.o .build/uno/arduino/USBCore.o .build/uno/arduino/WMath.o .build/uno/arduino/WString.o
	@echo Linking libarduino.a
	@/Applications/Arduino.app/Contents/Resources/Java/hardware/tools/avr/bin/avr-ar rcs $@ $^















.build/uno/src/BackEase.o : src/BackEase.cpp
	@echo src/BackEase.cpp
	@mkdir -p .build/uno/src
	@/Applications/Arduino.app/Contents/Resources/Java/hardware/tools/avr/bin/avr-g++ -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=105 -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino -ffunction-sections -fdata-sections -g -Os -w -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/variants/standard -I/Applications/Arduino.app/Contents/Resources/Java/libraries/EEPROM -Ilib/LiquidCrystal -Ilib/Wire -Ilib/Wire/utility -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino/avr-libc -fno-exceptions  -o $@ -c src/BackEase.cpp
include .build/uno/src/BackEase.d

.build/uno/src/BounceEase.o : src/BounceEase.cpp
	@echo src/BounceEase.cpp
	@mkdir -p .build/uno/src
	@/Applications/Arduino.app/Contents/Resources/Java/hardware/tools/avr/bin/avr-g++ -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=105 -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino -ffunction-sections -fdata-sections -g -Os -w -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/variants/standard -I/Applications/Arduino.app/Contents/Resources/Java/libraries/EEPROM -Ilib/LiquidCrystal -Ilib/Wire -Ilib/Wire/utility -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino/avr-libc -fno-exceptions  -o $@ -c src/BounceEase.cpp
include .build/uno/src/BounceEase.d

.build/uno/src/CircularEase.o : src/CircularEase.cpp
	@echo src/CircularEase.cpp
	@mkdir -p .build/uno/src
	@/Applications/Arduino.app/Contents/Resources/Java/hardware/tools/avr/bin/avr-g++ -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=105 -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino -ffunction-sections -fdata-sections -g -Os -w -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/variants/standard -I/Applications/Arduino.app/Contents/Resources/Java/libraries/EEPROM -Ilib/LiquidCrystal -Ilib/Wire -Ilib/Wire/utility -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino/avr-libc -fno-exceptions  -o $@ -c src/CircularEase.cpp
include .build/uno/src/CircularEase.d

.build/uno/src/compat.o : src/compat.cpp
	@echo src/compat.cpp
	@mkdir -p .build/uno/src
	@/Applications/Arduino.app/Contents/Resources/Java/hardware/tools/avr/bin/avr-g++ -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=105 -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino -ffunction-sections -fdata-sections -g -Os -w -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/variants/standard -I/Applications/Arduino.app/Contents/Resources/Java/libraries/EEPROM -Ilib/LiquidCrystal -Ilib/Wire -Ilib/Wire/utility -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino/avr-libc -fno-exceptions  -o $@ -c src/compat.cpp
include .build/uno/src/compat.d

.build/uno/src/CubicEase.o : src/CubicEase.cpp
	@echo src/CubicEase.cpp
	@mkdir -p .build/uno/src
	@/Applications/Arduino.app/Contents/Resources/Java/hardware/tools/avr/bin/avr-g++ -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=105 -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino -ffunction-sections -fdata-sections -g -Os -w -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/variants/standard -I/Applications/Arduino.app/Contents/Resources/Java/libraries/EEPROM -Ilib/LiquidCrystal -Ilib/Wire -Ilib/Wire/utility -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino/avr-libc -fno-exceptions  -o $@ -c src/CubicEase.cpp
include .build/uno/src/CubicEase.d

.build/uno/src/EasingBase.o : src/EasingBase.cpp
	@echo src/EasingBase.cpp
	@mkdir -p .build/uno/src
	@/Applications/Arduino.app/Contents/Resources/Java/hardware/tools/avr/bin/avr-g++ -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=105 -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino -ffunction-sections -fdata-sections -g -Os -w -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/variants/standard -I/Applications/Arduino.app/Contents/Resources/Java/libraries/EEPROM -Ilib/LiquidCrystal -Ilib/Wire -Ilib/Wire/utility -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino/avr-libc -fno-exceptions  -o $@ -c src/EasingBase.cpp
include .build/uno/src/EasingBase.d

.build/uno/src/ElasticEase.o : src/ElasticEase.cpp
	@echo src/ElasticEase.cpp
	@mkdir -p .build/uno/src
	@/Applications/Arduino.app/Contents/Resources/Java/hardware/tools/avr/bin/avr-g++ -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=105 -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino -ffunction-sections -fdata-sections -g -Os -w -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/variants/standard -I/Applications/Arduino.app/Contents/Resources/Java/libraries/EEPROM -Ilib/LiquidCrystal -Ilib/Wire -Ilib/Wire/utility -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino/avr-libc -fno-exceptions  -o $@ -c src/ElasticEase.cpp
include .build/uno/src/ElasticEase.d

.build/uno/src/ExponentialEase.o : src/ExponentialEase.cpp
	@echo src/ExponentialEase.cpp
	@mkdir -p .build/uno/src
	@/Applications/Arduino.app/Contents/Resources/Java/hardware/tools/avr/bin/avr-g++ -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=105 -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino -ffunction-sections -fdata-sections -g -Os -w -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/variants/standard -I/Applications/Arduino.app/Contents/Resources/Java/libraries/EEPROM -Ilib/LiquidCrystal -Ilib/Wire -Ilib/Wire/utility -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino/avr-libc -fno-exceptions  -o $@ -c src/ExponentialEase.cpp
include .build/uno/src/ExponentialEase.d

.build/uno/src/LinearEase.o : src/LinearEase.cpp
	@echo src/LinearEase.cpp
	@mkdir -p .build/uno/src
	@/Applications/Arduino.app/Contents/Resources/Java/hardware/tools/avr/bin/avr-g++ -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=105 -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino -ffunction-sections -fdata-sections -g -Os -w -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/variants/standard -I/Applications/Arduino.app/Contents/Resources/Java/libraries/EEPROM -Ilib/LiquidCrystal -Ilib/Wire -Ilib/Wire/utility -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino/avr-libc -fno-exceptions  -o $@ -c src/LinearEase.cpp
include .build/uno/src/LinearEase.d

.build/uno/src/QuadraticEase.o : src/QuadraticEase.cpp
	@echo src/QuadraticEase.cpp
	@mkdir -p .build/uno/src
	@/Applications/Arduino.app/Contents/Resources/Java/hardware/tools/avr/bin/avr-g++ -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=105 -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino -ffunction-sections -fdata-sections -g -Os -w -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/variants/standard -I/Applications/Arduino.app/Contents/Resources/Java/libraries/EEPROM -Ilib/LiquidCrystal -Ilib/Wire -Ilib/Wire/utility -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino/avr-libc -fno-exceptions  -o $@ -c src/QuadraticEase.cpp
include .build/uno/src/QuadraticEase.d

.build/uno/src/QuarticEase.o : src/QuarticEase.cpp
	@echo src/QuarticEase.cpp
	@mkdir -p .build/uno/src
	@/Applications/Arduino.app/Contents/Resources/Java/hardware/tools/avr/bin/avr-g++ -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=105 -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino -ffunction-sections -fdata-sections -g -Os -w -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/variants/standard -I/Applications/Arduino.app/Contents/Resources/Java/libraries/EEPROM -Ilib/LiquidCrystal -Ilib/Wire -Ilib/Wire/utility -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino/avr-libc -fno-exceptions  -o $@ -c src/QuarticEase.cpp
include .build/uno/src/QuarticEase.d

.build/uno/src/QuinticEase.o : src/QuinticEase.cpp
	@echo src/QuinticEase.cpp
	@mkdir -p .build/uno/src
	@/Applications/Arduino.app/Contents/Resources/Java/hardware/tools/avr/bin/avr-g++ -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=105 -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino -ffunction-sections -fdata-sections -g -Os -w -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/variants/standard -I/Applications/Arduino.app/Contents/Resources/Java/libraries/EEPROM -Ilib/LiquidCrystal -Ilib/Wire -Ilib/Wire/utility -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino/avr-libc -fno-exceptions  -o $@ -c src/QuinticEase.cpp
include .build/uno/src/QuinticEase.d

.build/uno/src/SineEase.o : src/SineEase.cpp
	@echo src/SineEase.cpp
	@mkdir -p .build/uno/src
	@/Applications/Arduino.app/Contents/Resources/Java/hardware/tools/avr/bin/avr-g++ -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=105 -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino -ffunction-sections -fdata-sections -g -Os -w -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/variants/standard -I/Applications/Arduino.app/Contents/Resources/Java/libraries/EEPROM -Ilib/LiquidCrystal -Ilib/Wire -Ilib/Wire/utility -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino/avr-libc -fno-exceptions  -o $@ -c src/SineEase.cpp
include .build/uno/src/SineEase.d

.build/uno/src/sketch.o : .build/uno/src/sketch.cpp
	@echo src/sketch.cpp
	@mkdir -p .build/uno/src
	@/Applications/Arduino.app/Contents/Resources/Java/hardware/tools/avr/bin/avr-g++ -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=105 -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino -ffunction-sections -fdata-sections -g -Os -w -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/variants/standard -I/Applications/Arduino.app/Contents/Resources/Java/libraries/EEPROM -Ilib/LiquidCrystal -Ilib/Wire -Ilib/Wire/utility -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino -I/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino/avr-libc -fno-exceptions -iquote src  -o $@ -c .build/uno/src/sketch.cpp
include .build/uno/src/sketch.d







.build/uno/firmware.elf : .build/uno/src/BackEase.o .build/uno/src/BounceEase.o .build/uno/src/CircularEase.o .build/uno/src/compat.o .build/uno/src/CubicEase.o .build/uno/src/EasingBase.o .build/uno/src/ElasticEase.o .build/uno/src/ExponentialEase.o .build/uno/src/LinearEase.o .build/uno/src/QuadraticEase.o .build/uno/src/QuarticEase.o .build/uno/src/QuinticEase.o .build/uno/src/SineEase.o .build/uno/src/sketch.o .build/uno/EEPROM/libEEPROM.a .build/uno/LiquidCrystal/libLiquidCrystal.a .build/uno/Wire/libWire.a .build/uno/arduino/libarduino.a
	@echo Linking firmware.elf
	@/Applications/Arduino.app/Contents/Resources/Java/hardware/tools/avr/bin/avr-gcc -mmcu=atmega328p -Wl,-Os -Wl,--gc-sections -o $@ $^ -lm


.build/uno/firmware.hex : .build/uno/firmware.elf
	@echo Converting to firmware.hex
	@/Applications/Arduino.app/Contents/Resources/Java/hardware/tools/avr/bin/avr-objcopy -O ihex -R .eeprom $^ $@

include .build/uno/src/dependencies.d .build/uno/arduino/dependencies.d .build/uno/EEPROM/dependencies.d .build/uno/LiquidCrystal/dependencies.d .build/uno/Wire/dependencies.d

all : .build/uno/firmware.hex
	@true

