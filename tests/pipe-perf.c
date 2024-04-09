#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include "lind_platform.h"

unsigned long long WRITE_BUFFER_SIZE = 1UL << 16;
unsigned long long NUMBER_OF_WRITES = 1UL << (30 - 14);
unsigned long long READ_BUFFER_SIZE = 1UL << 16;
unsigned long long OUTLOOP = 1UL << 4;

pthread_barrier_t barrier; // wait for buffer allocation
int fd[2];

double getCurrentTime() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec + ts.tv_nsec / 1e9;
}

void* writerThreadFuncion(void *arg) {
    (void)arg;

    // NOTE: this is not a fork, this just create a new cage
    // lind_fork

    // preapre the write buffer
    char *buffer = malloc(sizeof(char) * WRITE_BUFFER_SIZE);
    for (int i = 0; i < WRITE_BUFFER_SIZE; i++) buffer[i] = 'A';

    pthread_barrier_wait(&barrier);

    for (int n = 0; n < OUTLOOP; n++)
    {
        for (int count = 0; count < NUMBER_OF_WRITES; count++)
        {
            lind_write(fd[1], buffer, WRITE_BUFFER_SIZE, 1);
        }
    }
    lind_close(fd[1], 1);
    free(buffer);
    return NULL;
}

void* readerThreadFunction(void *arg) {
    (void)arg;

    // prepare the read buffer
    char *buffer = (char *)calloc(READ_BUFFER_SIZE, sizeof(char));
    
    pthread_barrier_wait(&barrier);

    while ((lind_read(fd[0], buffer, READ_BUFFER_SIZE, 1)) > 0) {}
    
    free(buffer);
    return NULL;
}

int main(void)
{
    lindrustinit(0);
    int ret;

    // make the pipes
    if (lind_pipe(fd, 1) < 0) {
		perror("pipe()");
		exit(EXIT_FAILURE);
	}
    
    pthread_barrier_init(&barrier, NULL, 3);

    // create the reader and writer threads
    pthread_t writerThread, readerThread;

    if(pthread_create(&writerThread, NULL, writerThreadFuncion, NULL)) {
        perror("Failred to create writer thread!");
        return 1;
    }

    if(pthread_create(&readerThread, NULL, readerThreadFunction, NULL)) {
        perror("Failred to create reader thread!");
        return 1;
    }

    // prepare the timer
    double start, end, elapsed;

    // wait for: writer is ready to write, reader is ready to reead
    pthread_barrier_wait(&barrier);

    start = getCurrentTime();
    pthread_join(readerThread, NULL);
    end = getCurrentTime();
    pthread_join(writerThread, NULL);

    elapsed = end - start;

    printf("Pipe took %f seconds to execute \n", elapsed);
    return 0;
}