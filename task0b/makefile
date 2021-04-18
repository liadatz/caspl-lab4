all: exec

asm-libs: start.s
	nasm -f elf32 start.s -o start.o
	
c-libs: util.c patch.c
	gcc -m32 -Wall -ansi -c -nostdlib -fno-stack-protector util.c -o util.o
	gcc -m32 -Wall -ansi -c -nostdlib -fno-stack-protector patch.c -o patch.o

exec: asm-libs c-libs
	ld -m elf_i386 start.o patch.o util.o -o patch
	rm -f start.o patch.o util.o
	
clean:
	rm -f *.o patch