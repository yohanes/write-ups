# Challenge 2

This is also a small and easy challenge, and I just want to show how I used `objdump` + `nasm` to solve the problem without knowing the exact algorithm. I looked at the encryption part a little bit and I don't remember exactly the bits on the x86 flags i.e: I don't know which flags are set by `sahf` instruction, and I don't want to spend time to check and implement it. Still on Linux, I used objdump to cut the encryption part. Added this header:

    ---
    BITS 32
    global  func


     section .text      
    func:     
    -----

And changed the addresses to labels.

    nasm -f elf func.asm
    gcc -m32 flare.c func.o

And wrote this short code:

```C
#include <stdio.h>

extern int func(char *s1, char *s2, int len);

int main()
{
	char *a1 = "\xaf\xaa\xad\xeb\xae\xaa\xec\xa4\xba\xaf\xae"
		   "\xaa\x8a\xc0\xa7\xb0\xbc\x9a\xba\xa5\xa5\xba"
		   "\xaf\xb8\x9d\xb8\xf9\xae\x9d\xab\xb4\xbc\xb6"
		   "\xb3\x90\x9a\xa8"; //edi (compare)
	char inp[] = "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
		     "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
		     "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
		     "\x00\x00\x00\x00\x00\x00\x00"; //esi (input)
	int i = 0;
	int ch = 0;
	int count = 0x25;

	for (i=0; i < 37; i++) {
		for (ch=0; ch < 255; ch++) {
			inp[i] = ch;                        
			int n = func(a1, inp, 0x25);
			int idx = (n & 0xff00)>>8;
			if (idx!=count) {
				printf("%c", ch);
				count = idx;
				break;
			}
		}
	}
	printf("\n");

}
```

So in this case: I don't need to know how the algorithm works, just by understanding a little bit of the main loop, I can just brute force it.
