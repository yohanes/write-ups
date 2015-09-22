flare5 : flare5.c enc.o
	gcc -m32 flare5.c enc.o -o flare5

flare5test : flare5test.c enc.o
	gcc -m32 flare5test.c enc.o -o flare5test

enc.o: enc.asm
	nasm -f elf enc.asm
