#undef _GNU_SOURCE
#define _GNU_SOURCE

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include "lind_platform.h"

#define DIR "testfolder"

int main(int argc, char **argv) {
    lindrustinit(0);
    mode_t dir_per = (S_IRUSR | S_IWUSR);
    if (lind_mkdir(DIR, dir_per, 1) == -1) {
        perror("mkdir");
        exit(EXIT_FAILURE);
    }
    printf("Created directory successfully\n");
    fflush(stdout);

    if (lind_rmdir(DIR, 1) == -1) {
        perror("rmdir");
        exit(EXIT_FAILURE);
    }
    printf("Removed directory successfully\n");
    fflush(stdout);
    lindrustfinalize();
    return 0;
}
