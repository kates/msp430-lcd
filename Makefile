#MCU = msp430g2553
MCU = msp430g2452

clean:
	rm -f main.elf main.lst lcd.o

all: clean flash
	
flash: compile
	mspdebug rf2500 "prog main.elf"

lcd:
	msp430-gcc -Os -Wall -mmcu=$(MCU) -c lcd.c

compile: lcd
	msp430-gcc -Os -Wall -mmcu=$(MCU) -o main.elf main.c lcd.o
	msp430-objdump -DS main.elf > main.lst
	msp430-objdump -h main.elf
	msp430-size main.elf
	
.PHONY: all
