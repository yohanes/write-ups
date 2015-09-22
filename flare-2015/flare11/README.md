# Challenge 11

Note: This write up is not as complete as I want it to be. May be I will update it someday.

Reading the easy part of the code: this app tries to decrypt a resource file to "secret.jpg". Like the challenge #4, it reads a single argument from command line, but this time brute force doesn't work. Even given the correct parameter, the program just hangs.

I tried to extract the encryption code so I can just call it, but there are too many functions being called. I tried reimplementing it, but its too complicated.

For the first part: finding the correct parameter, I just patched the binary, so it will exit with esi as the return value (`call exit(esi)`) after the first MD5 comparation. When `esi` is less than 0, it means I got the correct parameter.

Here is the patch:

    fc CryptoGraph.exe CryptoGraph-patched.exe
    Comparing files CryptoGraph.exe and CRYPTOGRAPH-PATCHED.EXE
    00000B29: 85 56
    00000B2A: FF E8
    00000B2B: 74 2E
    00000B2C: 09 4F
    00000B2D: 57 00
    00000B2E: E8 00

For the second part, I finally understood that the loop is mean to create decryption key for the decryption. I also saw a bit counting algorithm being used. I have a theory that you don't need the full 32 iteration to generate the bytes necessary to decrypt the resource inside the file.

First I need to be able to control the loop count, and also the return value of the bit counting mechanism. Then I wrote a python brute forcer. In another window I executed: "file *jpg", until I got:

    c-9.exe.jpg:  JPEG image data, JFIF standard 1.01, resolution (DPI), density 72x72, segment length 16, baseline, precision 8, 416x416, frames 3

The patch for the second part:

    fc CryptoGraph.exe CryptoGraph2.exe
    Comparing files CryptoGraph.exe and CRYPTOGRAPH2.EXE
    00000CC2: 20 02
    000011A6: FF 90
    000011A7: 75 90
    000011A8: 10 90
    000011AC: FF 90
    000011AD: 75 90
    000011AE: C0 90
    000011AF: E8 B8
    000011B0: AC 02
    000011B1: FD 00
    000011B2: FF 00
    000011B3: FF 00
