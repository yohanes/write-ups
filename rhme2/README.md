# RHME 2

I didn't have CHIP Whisperer and only solved most things that doesn't require special hardware. 

## Introduction and Notes

This is mostly for myself so that I would remember how to do AVR reversing again in the future, but hopefully it is clear enough for others to learn.

### Tools used

Main tools that I used for solving the challenges are:

* avr-gcc and avr-binutils (especially avr-objdump)
* vim
* simulavr (using [this fork](https://github.com/Traumflug/simulavr) )
* platformio
* sigrok

Documentations 

* [AVR Instruction Set Manual](http://www.atmel.com/images/Atmel-0856-AVR-Instruction-Set-Manual.pdf)
* [Atmega 328 datasheet](http://www.atmel.com/Images/Atmel-42735-8-bit-AVR-Microcontroller-ATmega328-328P_Datasheet.pdf)

As for the hardware:

* My own arduino nano for testing
* cypress development board as logic analyzer (CY7C68013A)

### Setup

The purpose of my setup was so I could solve the challenges remotely. So I plugged the RHME Arduino Nano to my Raspberry Pi 2 (RPI2). During some challenges I attached another Nano for testing some undocumented behavior (e.g: what happens if you try to read past the flash size? would it wrap around?). During other challenges, I attached the cypress logic analyzer with sigrok-cli to access it.

It turns out this setup quite useful: once in a while we can't reprogram the board unless we replug it, using  RPI2, I can just shutdown the USB power and start it again. If that didn't work, I just rebooted the RPI2 remotely.

### Tools notes

Except for Reversing challenges, we are given only *encrypted* hex files which we can not reverse. For the reversing tasks we are also given the corresponding ELF file. When we are given an ELF file, we can convert it into hex so we can write it to our own arduino. Here are some useful commands


Convert ELF to HEX

   objcopy -O ihex input.elf output.hex

Disassemble ELF:

   avr-objdump -d -s file.elf


Unfortunately for the FridgeJIT challenge, there is a jump to the bootloader that makes it not possible to run the code in our own Arduino.


## Logic Analyzer notes

I used  [EZ-USB FX2LP CY7C68013A development board ](https://www.aliexpress.com/item/Free-ship-IEZ-USB-FX2LP-CY7C68013A-USB-core-board-development-board-USB-logic-analyzer-I2C-serial/976713163.html) with sigrok. The price for the board is less than 5 USD (including shipping). If you never used Aliexpress before, you can use [this link](http://s.aliexpress.com/26JfMJ7J) to get 5 USD coupon that can be used for minimum 6 USD purchase (so if you buy something for 6 USD, you only need to pay 1 USD).

To use this board, connect PB0-PB7 and PD0-PD7 for 16-channel sampling. I did not use any protection circuit when connecting this to Arduino board, but you [may need them](https://sigrok.org/wiki/Circuits_for_barebone_boards) when connecting this board to other circuits.

### Reversing Notes

In desktop app, we will usually find basic calls to `printf` or `getc` as our starting point and start tracing back from ther. Since I/Os are done using serial port, we will try to find the most basic instruction sequence that accessed the serial port/UART. Instruction that called the basic `putc` is `puts`. Comparing this with `avr-gcc` output, we can conclude that the challenges were written using gcc and they used the included standard C library. 

From the documentation to read or write to serial port we will need to access USART I/O Data Register 0 (UDR0). This is located at offset `C6`. Here is a piece of code that reads `C6` (from [Jumpy](jumpy)) challenge:

    2ba:   86 ec           ldi     r24, 0xC6       ; 198
    2bc:   90 e0           ldi     r25, 0x00       ; 0
    2be:   fc 01           movw    r30, r24
    2c0:   80 81           ld      r24, Z

And a piece of code that writes to `C6`

    ea:   86 ec           ldi     r24, 0xC6       ; 198
    ec:   90 e0           ldi     r25, 0x00       ; 0
    ee:   29 81           ldd     r18, Y+1        ; 0x01
    f0:   fc 01           movw    r30, r24
    f2:   20 83           st      Z, r18

After we identify the basic instructions, we will see that calls to this functions are passed with strange address, which doesn't seem to contain printable ASCII characters. We need to go to the initial instructions, to see that there is a copy instruction from Flash to RAM. This is mostly done for simplicity reason: AVR uses separate data and instruction bus, and also has different address space for data and program. To make it easy for compiler, data are moved to RAM for easy access.  This part confuses me a bit at the beginning, which makes me switch from radare to vim, since the binary is small enough, and I can just copy paste and relabel the RAM addresses.


## Solved Tasks

### Reversing

I solved all the reversing tasks as it doesn't require any special hardware. 

* [Jumpy](jumpy)
* [Impostor](impostor)
* [FridgeJIT](fridge-jit)

### Exploitation

Most of the exploitation tasks are a bit disappointing, mostly trial and error to exploit format string bugs, except for the Weird Machine.

* [Animals](animals)
* [Casino](casino)
* [Photo Manager](photo-manager)
* [Weird Machine](weird-machine)

### Crypto

Crypto tasks requires intelligent guessing

* [Key Server](key-server)
* [Secure Filesystem](secure-filesystem)
* [Secure Filesystem v1.92r1](secure-filesystem-v1.92r1)

### Others

* [Whac the mole](whack-the-mole)
* [Secret Sauce](secret-sauce)
* [Hide & seek] (hide-and-seek)

