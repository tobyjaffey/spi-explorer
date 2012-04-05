TARGET=spi

CC=msp430-gcc
SIZE=msp430-size
STRIP=msp430-strip

CFLAGS=-Os -Wall -g -mmcu=msp430x2013 -ffunction-sections -fdata-sections -fno-inline-small-functions

LDFLAGS = -Wl,-Map=$(TARGET).map,--cref
LDFLAGS += -Wl,--relax
LDFLAGS += -Wl,--gc-sections

OBJS=main.o uart.o cpu.o console.o parse.o shell.o spi.o

all: $(TARGET).elf

$(TARGET).elf: $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET).elf $(OBJS) $(LDFLAGS)
	$(STRIP) $(TARGET).elf
	$(SIZE) --format=sysv $(TARGET).elf

program: $(TARGET).elf
	mspdebug rf2500 "prog $(TARGET).elf"

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -rf $(TARGET).elf $(OBJS) $(TARGET).map
