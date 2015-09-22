# Challenge 1

This is so trivial. You can see the complete tutorial to solve it in the webinar (which I didn't see until I finished all the challenges). The only thing I want to show here is that I solved this using objdump, I didn't have access to Windows when I downloaded the first challenge:

    objdump -p -s -d i_am_happy_you_are_to_playing_the_flareon_challenge.exe

I know its not easy to read it, and it didn't occur to me to use online disassembler, but with a bit of concentration we can immediatelly see that `push   $0x4020f2` refers to the string `"Let's start out easy\r\nEnter the password>"`. Address `$0x402158` will contain the result of `ReadFile`, and it will be compared with block at `0x402140` after xoring it with fixed key `0x7d`. So basically this is just XOR encryption, 24 characters (`"cmp    $0x18,%ecx"`).

    objdump -s --start-address=0x402140 --stop=0x402158 i_am_happy_you_are_to_playing_the_flareon_challenge.exe

And this one line of python is enough to solve it:

    print "".join([chr(ord(x) ^ 0x7d) for x in "1f08131304220e114d0d183d1b111c0f18501213531e1210".decode("hex")])
