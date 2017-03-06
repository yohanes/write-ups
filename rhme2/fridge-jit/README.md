#Fridge JIT (Challenge 6, Reverse Engineering 400pts)

## Problem Description

A senior technical manager of a fridge manufacturer demanded the ability to update the firmware in their new product line (we need to monitor and control the temperature, right?) of all deployed devices over the air and without user interaction. This way, the manufacturer could improve the user experience by providing firmware updates, even when the fridge is 1 or 2 years old.

It turned out that the CPU that comes with the fridges does not allow self-upgrading the firmware, so the developers built a VM for the fridge software which at that time was just a few lines of code. Incidentally, half of the development and test team was fired 2 months after releasing the new product line.

A crafty customer has been able to reverse engineer the software and programmed the fridge with different software. His goal was to build a digital safe, but the guy claims not being able to make the application small enough to fit inside the VM. However, to be sure we ask you to check whether this is correct.

Are you able to crack the password? We have been able to extract the full firmware image of a slightly different fridge and a memory dump of their fridge. We hope this is enough...

*Note: The flag is in a different format than usually...*

## Solution

This is a straightforward VM, and in this level we don't need to pay attention to each opcode detail (but we will need it on the next part).

If ROM contains valid signature, the VM will load it, otherwise it will load hex formated input from serial. We can not fully run the VM using simulavr because it jumps to an address in the bootloader and we don't know what is being set there. I could have guessed what is being set, and where do we jump back from bootloader, but decided to just create a disassembler for the VM.

The password checks are done using integer representation, for example, the first 4 characters is checked like this:

    0192 OP: 06 (ROM: 06) GET  R4, [sp+R0]
    0194 OP: 0d (ROM: 0d) COMP  R2 # complement/NOT
    0196 OP: 10 (ROM: 10) ROL  R4, R2
    0198 OP: 05 (ROM: 05) MOV.H  R1, 3d67 (=g)
    019c OP: 04 (ROM: 04) MOV.L  R1, 82a5 (.¥)
    01a0 OP: 0a (ROM: 0a) XOR  R4, R1
    01a2 OP: 05 (ROM: 05) MOV.H  R1, 5dd5 (]Õ)
    01a6 OP: 04 (ROM: 04) MOV.L  R1, 3c4f (<O)
    01aa OP: 16 (ROM: 16) CMP  R1, R4
    01ac OP: 13 (ROM: 13) RET

And we can get the first 4 letters by XORing both numbers and shifting right by 1.

It turns out that the password is the flag (`Y0u_G0T_1t_r1ght!`).

