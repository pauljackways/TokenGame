# File:   Makefile
# Author: M. P. Hayes, UCECE
# Date:   12 Sep 2010
# Descr:  Makefile for lab1-ex4

# Definitions.
CC = avr-gcc
CFLAGS = -mmcu=atmega32u2 -Os -Wall -Wstrict-prototypes -Wextra -g -I. -I../../drivers/avr
OBJCOPY = avr-objcopy
SIZE = avr-size
DEL = rm


# Default target.
all: game.out


# Compile: create object files from C source files.
game.o: game.c ../../drivers/avr/system.h button.h led.h attack.h startup.h choose.h display.h ../../drivers/avr/pio.h totem_nav.h navswitch.o
	$(CC) -c $(CFLAGS) $< -o $@

pio.o: ../../drivers/avr/pio.c ../../drivers/avr/pio.h ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

system.o: ../../drivers/avr/system.c ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

button.o: button.c ../../drivers/avr/pio.h ../../drivers/avr/system.h button.h
	$(CC) -c $(CFLAGS) $< -o $@

led.o: led.c ../../drivers/avr/pio.h ../../drivers/avr/system.h led.h
	$(CC) -c $(CFLAGS) $< -o $@

attack.o: attack.c ../../drivers/avr/system.h attack.h
	$(CC) -c $(CFLAGS) $< -o $@

startup.o: startup.c ../../drivers/avr/system.h startup.h
	$(CC) -c $(CFLAGS) $< -o $@

choose.o: choose.c ../../drivers/avr/system.h choose.h 
	$(CC) -c $(CFLAGS) $< -o $@

display.o: display.c ../../drivers/avr/pio.h ../../drivers/avr/system.h display.h
	$(CC) -c $(CFLAGS) $< -o $@

totem_nav.o: totem_nav.c ../../drivers/avr/system.h navswitch.h totem_nav.h
	$(CC) -c $(CFLAGS) $< -o $@

navswitch.o: navswitch.c ../../drivers/avr/delay.h ../../drivers/avr/pio.h ../../drivers/avr/system.h navswitch.h
	$(CC) -c $(CFLAGS) $< -o $@


# Link: create ELF output file from object files.
game.out: game.o pio.o system.o button.o led.o attack.o startup.o choose.o display.o pio.o totem_nav.o navswitch.o
	$(CC) $(CFLAGS) $^ -o $@ -lm
	$(SIZE) $@


# Target: clean project.
.PHONY: clean
clean:
	-$(DEL) *.o *.out *.hex


# Target: program project.
.PHONY: program
program: game.out
	$(OBJCOPY) -O ihex game.out game.hex
	dfu-programmer atmega32u2 erase; dfu-programmer atmega32u2 flash game.hex; dfu-programmer atmega32u2 start
