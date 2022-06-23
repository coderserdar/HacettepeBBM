all: bintree

	gcc -o bintree main.c main.o

bintree:bintree.asm

	nasm -felf -o main.o bintree.asm

clean: bintree

	rm -rf *.o bintree