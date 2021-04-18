all: exec

asm-libs: start.s
	nasm -f elf32 start.s -o start.o
	
c-libs: util.c encoder.c
	gcc -m32 -Wall -ansi -c -nostdlib -fno-stack-protector util.c -o util.o
	gcc -m32 -Wall -ansi -c -nostdlib -fno-stack-protector encoder.c -o encoder.o

exec: asm-libs c-libs
	ld -m elf_i386 start.o encoder.o util.o -o encoder
	rm -f start.o encoder.o util.o
	
clean:
	rm -f *.o encoder