all: exec

asm-libs: start.s
	nasm -f elf32 start.s -o start.o
	
c-libs: util.c flame2.c
	gcc -m32 -Wall -ansi -c -nostdlib -fno-stack-protector util.c -o util.o
	gcc -m32 -Wall -ansi -c -nostdlib -fno-stack-protector flame2.c -o flame2.o

exec: asm-libs c-libs
	ld -m elf_i386 start.o flame2.o util.o -o flame2
	rm -f start.o flame2.o util.o
	
clean:
	rm -f *.o flame2