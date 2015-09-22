# Challenge 4

Using `strings`, I can see that this file is packed using UPX (you can see the string `UPX0`, `UPX1`), so I decided to postpone this problem until I got an access to a Windows machine. I tried to decompress it using `upx` command line, but it doesn't run in Windows 10. I thought that this must have used a modified compressor.

Anyway, I just run this inside OllyDbg. The interesting thing is: it reads from a command line, and converts the string from command line it to single byte int. 256 is very small key space, so I just brute force this without knowing what exactly this file does.

    for /l %x in (0, 1, 255) do youPecks.exe %x >> result.txt

And you can see the answer in one of the lines. Reading others writeup, it seems that this is time dependant.
