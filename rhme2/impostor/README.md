#Impostor (Chal 4, 300pts)

>> We have found this binary in an abandoned building. The police suspect someone set the building on fire by accident but we KNOW it was arson. Someone was trying to hide a secret plan of attack against the Republic of Wadiya. We think the binary contains the key to a safe that we were able to recover. Reverse the binary and help us find the secret key. You can be the hero we know you are!
>> But beware, not everything is what it seems! Wadiyan soldiers are masters of disguise so we might have an impostor on the run.

>> Good luck and 👍👍

While reversing this challenge, I quickly realized that this is a Virtual Machine. The virtual machine is quite complicated, and I almost gave up. I mentioned to my friend that this VM is quite *crazy*, and he said that may be it was based on some existing VM code on the internet. I then realized that the instruction set seems to be familiar, the three operands remined me of the ARM Thumb instruction set.  tried using [Online disassembler](https://www.onlinedisassembler.com/odaweb/) to test out if I was correct, and it seems that the disassembly result makes sense. So I stopped doing AVR reversing and started doing ARM thumb reversing.

Next step was to figure out what the code does. This is a good time to try out the [Unicorn Engine](http://www.unicorn-engine.org/) to help simulate the thumb instruction. But there is a slight problem: the `bkpt` (breakpoint) instruction. This instruction does nothing for the Unicorn Engine, but after looking at the specific opcode, this is used to copy the user input to the ARM code.

    .data:00000000 46 78                            mov     r0, pc
    .data:00000002 38 04                            subs    r0, #4
    .data:00000004 46 82                            mov     sl, r0
    .data:00000006 f8 01 f0 00                      bl      0x0000000c
    .data:0000000a 00 00                            movs    r0, r0
     
    #first part: just copy data
    .data:0000000c b5 80                            push    {r7, lr}
    .data:0000000e b0 a4                            sub     sp, #144        ; 0x90
    .data:00000010 af 00                            add     r7, sp, #0
    .data:00000012 23 18                            movs    r3, #24
    .data:00000014 18 fb                            adds    r3, r7, r3
    .data:00000016 4a 88                            ldr     r2, [pc, #544]  ; (0x00000238)
    .data:00000018 60 1a                            str     r2, [r3, #0]
    .data:0000001a 23 18                            movs    r3, #24
    .data:0000001c 18 fb                            adds    r3, r7, r3
    .data:0000001e 4a 87                            ldr     r2, [pc, #540]  ; (0x0000023c)
    .data:00000020 60 5a                            str     r2, [r3, #4]
    .data:00000022 23 18                            movs    r3, #24
    .data:00000024 18 fb                            adds    r3, r7, r3
    .data:00000026 4a 86                            ldr     r2, [pc, #536]  ; (0x00000240)
    .data:00000028 60 9a                            str     r2, [r3, #8]
    .data:0000002a 23 18                            movs    r3, #24
    .data:0000002c 18 fb                            adds    r3, r7, r3
    .data:0000002e 4a 85                            ldr     r2, [pc, #532]  ; (0x00000244)
    .data:00000030 60 da                            str     r2, [r3, #12]
    .data:00000032 23 20                            movs    r3, #32
    .data:00000034 67 fb                            str     r3, [r7, #124]  ; 0x7c
    .data:00000036 4b 84                            ldr     r3, [pc, #528]  ; (0x00000248)
    .data:00000038 67 bb                            str     r3, [r7, #120]  ; 0x78
    .data:0000003a 4b 84                            ldr     r3, [pc, #528]  ; (0x0000024c)
    .data:0000003c 67 7b                            str     r3, [r7, #116]  ; 0x74
    .data:0000003e 4b 84                            ldr     r3, [pc, #528]  ; (0x00000250)
    .data:00000040 67 3b                            str     r3, [r7, #112]  ; 0x70
    .data:00000042 4b 84                            ldr     r3, [pc, #528]  ; (0x00000254)
    .data:00000044 66 fb                            str     r3, [r7, #108]  ; 0x6c
    .data:00000046 23 81                            movs    r3, #129        ; 0x81
    .data:00000048 18 fb                            adds    r3, r7, r3
    .data:0000004a 22 01                            movs    r2, #1 ;r2 = 1
    .data:0000004c 70 1a                            strb    r2, [r3, #0]
    .data:0000004e be 01                            bkpt    0x0001 ; -> read to R0
    .data:00000050 1c 02                            adds    r2, r0, #0 ; r2 + char1
    .data:00000052 23 28                            movs    r3, #40 ; 0x28
    .data:00000054 18 fb                            adds    r3, r7, r3 ; r3 = r7 + r3
    .data:00000056 60 1a                            str     r2, [r3, #0]
    .data:00000058 be 02                            bkpt    0x0002

Reversing it further shows that this is a known encryption algorithm XTEA, but it uses different delta constant from the one used in [Wikipedia](https://en.wikipedia.org/wiki/XTEA), instead of the common 0x9E3779B9 it used 0xab64e218.

The final password is `4rM_c0rT3xM0_4vR`


