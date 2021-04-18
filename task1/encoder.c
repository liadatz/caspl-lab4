#include "util.h"

extern int system_call();
#define SYS_EXIT 1
#define SYS_READ 3
#define SYS_WRITE 4
#define SYS_OPEN 5
#define SYS_CLOSE 6
#define SYS_LSEEK 19
#define O_RDRW 2
#define O_RDONLY 0
#define O_WRONLY 1
#define O_CREAT 64
#define STDOUT 0
#define STDIN 0


extern int system_call();

int main(int argc, char **argv) {
    int input = 0;
    int output = 1;
    int i;
    char c[1];
    int debug = 0, counter = 0;

    /* reading from argv */
    for (i = 1; i < argc; i++) {
        /* debug mode - Task 1b */
        if ((strcmp(argv[i], "-D")) == 0) debug = 1;

        /* read from file - Task 1d */
        if ((argv[i][0] == '-') & (argv[i][1] == 'i')) input = system_call(SYS_OPEN, (argv[i]+2), O_RDONLY, 0777);
        /* export to file - Task 2 */
        if ((argv[i][0] == '-') & (argv[i][1] == 'o')) output = system_call(SYS_OPEN, (argv[i]+2), O_CREAT | O_WRONLY, 0777);
    }

    if (input < 0 || output < 0) system_call(SYS_EXIT, 0x55);

    /* encoder*/
    while ((system_call(SYS_READ, input, c, 1)) > 0) {
        /*if (c[0] == '\n'){
            if (debug) fprintf(stderr, "\nthe number of letters: %i\n\n", counter);
            system_call(SYS_WRITE, output, c, 1);
            counter = 0;
            continue;
        }
        */
        /* if (debug) fprintf(stderr, "%i\t", c); */
        if ((c[0] >= 'A') & (c[0] <= 'Z')) {
            c[0] += 32;
            counter++;
        }
        /* if (debug) fprintf(stderr, "%i\n", c); */
        system_call(SYS_WRITE, output, c, 1);
    }
    
    system_call(SYS_WRITE, output, "\n", 1);
    /* close FILE */
    if (input != 0) system_call(SYS_CLOSE, input);
    if (input != 1) system_call(SYS_CLOSE, output);
    return 0;
}