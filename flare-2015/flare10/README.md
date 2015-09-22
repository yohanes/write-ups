# Challenge 10

This file is an `AutoIt.exe`. It can be extracted using: Exe2Aut.exe. The autoit script doesn't do anything meaningful except for installing the driver and calling IOCTL, so I went to look at the driver. The driver contains many functions, mostly junk, except for parts where it writes a byte to certain memory location.

I am still not sure how to separate the junk instructions, so I just wander around the code to see if there are something that is clear and doesn't contain junk. One thing pops up: a number that is used as constant to TEA encryption algorithm. The input for the algorithm is a memory location, and a fixed key.

I am too lazy to setup an environment to debug the code, so I just used Ida's xref function to trace one by one the bytes written to the memory location that is decrypted. I traced the first 8 bytes, tried to decrypt it, and got a plaintext `uncondit`, it looks right, so I just continued to the next bytes, until I got the string: `unconditional_conditions@flare-o`, and just stops there.


