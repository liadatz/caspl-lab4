#include "util.h"

extern int system_call();
#define SYS_EXIT 1
#define SYS_READ 3
#define SYS_WRITE 4
#define SYS_OPEN 5
#define SYS_LSEEK 19
#define O_RDRW 2
#define STDOUT 1

extern int system_call();

int main (int argc , char* argv[], char* envp[]) {
    int statusOpen;
    int statusRead;
    int i;
    int fileSize = 27;
    char buffer[fileSize];
    int sizeCmp = 5 - strlen(argv[2]);
    char replace[sizeCmp];
    if (sizeCmp > 0) {
        replace[0] = '.';
        for (i = 1; i < sizeCmp; i++)
            replace[i] = '\x90';
    }
    statusOpen = system_call(SYS_OPEN, argv[1], O_RDRW, 0777);
    if (statusOpen == -1) system_call(SYS_EXIT, 0x55);
    statusRead = system_call(SYS_READ, statusOpen, buffer, fileSize);
    if (statusRead == -1) system_call(SYS_EXIT, 0x55);
    for (i = 0; i < fileSize - 5; i++) {
        if (strncmp(buffer+i, "Shira", 5) == 0) {
            system_call(SYS_WRITE, system_call(SYS_LSEEK, statusOpen, i, 0), argv[2], strlen(argv[2]));
            system_call(SYS_WRITE, system_call(SYS_LSEEK, statusOpen, i+strlen(argv[2]), 0), replace, sizeCmp);
        }
    }
  return 0;
}
