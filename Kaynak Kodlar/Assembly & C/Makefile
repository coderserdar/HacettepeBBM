all: main

main: asmlib
	gcc -o main pretoin.c asmlib.o
	
asmlib: asmlib.asm
	nasm -felf -o asmlib.o asmlib.asm

clean:
	rm *.o
