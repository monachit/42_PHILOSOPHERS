#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void* myThread(void* arg) {
    int* val = (int*)arg;
    printf("Thread is running. Value: %d\n", *val);
    pthread_exit(NULL);
}

int main() {
    pthread_t thread;
    int value = 10;

    // Create a new thread
    pthread_create(&thread, NULL, myThread, (void*)&value);

    // Detach the thread
    pthread_detach(thread);

    printf("Thread detached. Main thread continues...\n");

    // Main thread continues executing while the other thread runs independently
    // sleep(1); // Give the detached thread time to finish
    usleep(1000);

    return 0;
}
