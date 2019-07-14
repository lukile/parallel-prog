//
// Created by lukile on 05/06/19.
//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int isRunning = 1;

void* display(void* arg) {
    while(isRunning == 1) {
        printf("Hello\n");
        sleep(1);
    }
    printf("Terminated\n");
    return NULL;
}

void* userStop(void* arg) {
    getchar();
    isRunning = 0;
    return NULL;
}

int main() {
    pthread_t T1, T2;

#pragma PARALLEL
    //Delegate
    pthread_create(&T1, NULL, display, NULL);
#pragma PARALLEL
    pthread_create(&T2, NULL, userStop, NULL);

    pthread_join(T1, NULL);
    pthread_join(T2, NULL);

    return 0;
}

