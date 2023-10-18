# File:   Makefile
# Author: Paul Jackways (pja117), Katelyn McCarthy Freeman (kmc313)
# Date:   18 Oct 2023
# Descr:  Makefile for game

# Definitions.
CC = avr-gcc
CFLAGS = -mmcu=atmega32u2 -Os -Wall -Wstrict-prototypes -Wextra -g -I. -I../../drivers/avr
OBJCOPY = avr-objcopy
SIZE = avr-size
DEL = rm


# Default target.
all: game.out


# Compile: create object files from C source files.
game.o: game.c ../../drivers/avr/system.h button.h led.h attack.h display.h ../../drivers/avr/pio.h totem_nav.h navswitch.h pacer.h ../../drivers/avr/timer.h ../../drivers/avr/timer0.h ../../drivers/avr/prescale.h  ../../drivers/avr/ir_uart.h ../../drivers/avr/usart1.h
	$(CC) -c $(CFLAGS) $< -o $@

pio.o: ../../drivers/avr/pio.c ../../drivers/avr/pio.h ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

system.o: ../../drivers/avr/system.c ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

button.o: button.c ../../drivers/avr/pio.h ../../drivers/avr/system.h button.h
	$(CC) -c $(CFLAGS) $< -o $@

led.o: led.c ../../drivers/avr/pio.h ../../drivers/avr/system.h led.h
	$(CC) -c $(CFLAGS) $< -o $@

attack.o: attack.c ../../drivers/avr/system.h ../../drivers/avr/ir_uart.h display.h pacer.h attack.h ../../drivers/avr/pio.h navswitch.h button.h led.h
	$(CC) -c $(CFLAGS) $< -o $@

display.o: display.c ../../drivers/avr/pio.h ../../drivers/avr/system.h display.h
	$(CC) -c $(CFLAGS) $< -o $@

totem_nav.o: totem_nav.c ../../drivers/avr/system.h navswitch.h totem_nav.h
	$(CC) -c $(CFLAGS) $< -o $@

navswitch.o: navswitch.c ../../drivers/avr/delay.h ../../drivers/avr/pio.h ../../drivers/avr/system.h navswitch.h
	$(CC) -c $(CFLAGS) $< -o $@

timer.o: ../../drivers/avr/timer.c ../../drivers/avr/system.h ../../drivers/avr/timer.h
	$(CC) -c $(CFLAGS) $< -o $@

pacer.o: pacer.c ../../drivers/avr/system.h ../../drivers/avr/timer.h pacer.h
	$(CC) -c $(CFLAGS) $< -o $@

usart1.o: ../../drivers/avr/usart1.c ../../drivers/avr/system.h ../../drivers/avr/usart1.h
	$(CC) -c $(CFLAGS) $< -o $@

prescale.o: ../../drivers/avr/prescale.c ../../drivers/avr/system.h ../../drivers/avr/prescale.h
	$(CC) -c $(CFLAGS) $< -o $@

timer0.o: ../../drivers/avr/timer0.c ../../drivers/avr/system.h ../../drivers/avr/bits.h ../../drivers/avr/prescale.h ../../drivers/avr/timer0.h
	$(CC) -c $(CFLAGS) $< -o $@

ir_uart.o: ../../drivers/avr/ir_uart.c ../../drivers/avr/system.h  ../../drivers/avr/usart1.h ../../drivers/avr/timer0.h ../../drivers/avr/pio.h ../../drivers/avr/delay.h ../../drivers/avr/ir_uart.h
	$(CC) -c $(CFLAGS) $< -o $@


# Link: create ELF output file from object files.
game.out: game.o pio.o system.o button.o led.o attack.o display.o totem_nav.o navswitch.o timer.o pacer.o usart1.o prescale.o timer0.o ir_uart.o
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
