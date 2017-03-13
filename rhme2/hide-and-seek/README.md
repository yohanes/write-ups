# Hide and Seek (Challenge 21, Others 400pts)

>> So you found the password [last time](http://rhme.riscure.com/challenge?id=6)? This time it got a little bit harder. Instead of hiding it in the VM, it is somewhere else on the device. Are you able to find it?

Looking at the link, it points to the FridgeJIT challenge, so this is the continuation of the challenge. My guess is we need to dump the RAM for this challenge. One thing I noticed since the previous challenge is this: There are 7 registers, but not all functions that handles the instructions masked the regiter number consistently. Some uses (regnumber&7), and other uses (regnumber&0xf), it means that we can write past the register array. One of the instruction is opcode 0xA (XOR).


The memory layout of the register looks like this:

    int32_t regs[6];
    uint32_t sp;
    uint32_t ip;
    uint8_t flag;
    uint16_t sp_base;

I wrote a simple assembler for this VM using python [asm.py](asm.py) and wrote this simple code to dump the RAM.


    xor flag,flag # flag is 0
    mov.h r1, 0007
    mov.l r1, 0000 # 
    xor flag, r1 # overwrite sp_base
    xor r1, r1 #r1 is now a counter
    mov.l r3, 1 #to increment counter
    loop:
       get r2, r1      # r2 = [sp_base + r1] 
       puts r2	       # dump
       add r1, r3      # increment 1
    jump4 loop


