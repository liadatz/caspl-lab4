#include "util.h"
#include <dirent.h>

extern int system_call();
#define SYS_EXIT 1
#define SYS_READ 3
#define SYS_WRITE 4
#define SYS_OPEN 5
#define SYS_CLOSE 6
#define SYS_LSEEK 19
#define SYS_GETDENTS 141
#define O_RDRW 2
#define O_RDONLY 0
#define O_WRONLY 1
#define O_CREAT 64
#define STDOUT 0
#define STDIN 0

/*d_types*/
#define DT_REG 8
#define DT_DIR 4
#define DT_FIFO 1
#define DT_SOCK 12
#define DT_LNK 10
#define DT_BLK 6
#define DT_CHR 2

struct linux_dirent {
    long           d_ino;
    long           d_off;
    unsigned short d_reclen;
    char           d_name[];
};


int main(int argc, char **argv) {
    int p = 0;
    int a = 0;
    char buff[8192];
    struct linux_dirent *d;
    int debug = 0, i;
    long bpos;
    char d_type;
    char* d_typeS;

    /* reading from argv */
    for (i = 1; i < argc; i++) {
        /* debug mode - Task 1b */
        if ((strcmp(argv[i], "-D")) == 0) debug = 1;
        /* read from file - Task 1d */
        if ((argv[i][0] == '-') & (argv[i][1] == 'p')) p = (argv[i][2]);
        /* export to file - Task 2 */
        if ((argv[i][0] == '-') & (argv[i][1] == 'a')) a = (argv[i][2]);
    }
    
    
    int dir = system_call(SYS_OPEN, ".", O_RDONLY, 0777);
    int dirLoad = system_call(SYS_GETDENTS, dir, buff, 8192);

    if (dirLoad == -1) system_call(SYS_EXIT, 0x55);

    for (bpos = 0; bpos < dirLoad;) {
        d = (struct linux_dirent*) (buff + bpos);
        d_type = *(buff + bpos + d->d_reclen -1);
        d_typeS = (d_type == DT_REG) ?  "regular" :
                    (d_type == DT_DIR) ?  "directory" :
                    (d_type == DT_FIFO) ? "FIFO" :
                    (d_type == DT_SOCK) ? "socket" :
                    (d_type == DT_LNK) ?  "symlink" :
                    (d_type == DT_BLK) ?  "block dev" :
                    (d_type == DT_CHR) ?  "char dev" : "???";
        if (p != 0) {
            if (d->d_name[0] == p) {
            system_call(SYS_WRITE, STDOUT, d->d_name, strlen(d->d_name));
            system_call(SYS_WRITE, STDOUT, " ", 1);
            system_call(SYS_WRITE, STDOUT, d_typeS, strlen(d_typeS));
            system_call(SYS_WRITE, STDOUT, "\n", 1);
            }
        }
        else {
            system_call(SYS_WRITE, STDOUT, d->d_name, strlen(d->d_name));
            system_call(SYS_WRITE, STDOUT, "\n", 1);
        }
        bpos += d->d_reclen;
    }
    /*for(i = 0 ; i < dirLoad ; i = i + 11){
        system_call(SYS_WRITE, STDOUT, (entp + i)->d_name, strlen((entp + i)->d_name));
    }*/
    system_call(SYS_CLOSE, dir);
    return 0;
}
