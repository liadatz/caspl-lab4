all: exec

asm-libs: start.s
	nasm -f elf32 start.s -o start.o
	
c-libs: util.c main.c
	gcc -m32 -Wall -ansi -c -nostdlib -fno-stack-protector util.c -o util.o
	gcc -m32 -Wall -ansi -c -nostdlib -fno-stack-protector main.c -o main.o

exec: asm-libs c-libs
	ld -m elf_i386 start.o main.o util.o -o task0
	rm -f start.o main.o util.o
	
clean:
	rm -f *.o task0