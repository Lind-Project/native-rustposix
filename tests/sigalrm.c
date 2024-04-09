#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "lind_platform.h"

void catcher( int sig ) {
    printf( "Alarm Handled. Exiting\n" );
    fflush(stdout);
    exit(0);
}

int main( int argc, char *argv[] ) {

    lindrustinit(0);
    rustposix_thread_init(1, 0);
    time_t start, finish;
    struct sigaction sact;
    sigset_t new_set, old_set;
    double diff;

    sigemptyset( &sact.sa_mask );
    sact.sa_flags = 0;
    sact.sa_handler = catcher;
    lind_sigaction( SIGALRM, &sact, NULL );

    printf( "SIGALRM signals blocked\n");
    fflush(stdout);

    alarm(2);     /* SIGALRM will be sent in 1 second */

    while(1);

    lindrustfinalize();

    return(0);
}

