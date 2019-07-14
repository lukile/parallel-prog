//
// Created by lukile on 26/06/19.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//#include <pthread.h>
#include <omp.h>

#define MACOUNT 5000000
#define MAXVAL 1024

int values[MAXVAL];


int counter = 0;


//pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

//Compte le nombre de fois qu'un thread passe dans la boucle

void* increment(void* arg) {
    int *tab;
    tab = (int*)*((int**) arg);

    int tNum = omp_get_thread_num();

    tab[tNum] = 0;


    int isRunning = 0;

    while(0 == isRunning) {
        //pthread_mutex_lock(&mutex);
        tab[tNum] += 1;
        //ou
        //(*mycnt)++
        if(counter < MACOUNT)
            counter++;
        else
            isRunning = 1;
        //pthread_mutex_unlock(&mutex);

    }
    printf("%d Terminated\n", tNum);

    return NULL;
}

int main() {
    int *c;
    int sum = 0;
    int numT;

//Genere les creations des thread (le fork) et le join
#pragma omp parallel
    {
#pragma omp single
        {
        numT = omp_get_num_threads();
        printf("Tnum: %d NB thread = %d\n", omp_get_thread_num(), numT);
        c = (int *) malloc(numT);

    }

    increment((void *) &c);
}
//Coupé le for en plusieurs morceaux
#pragma omp parallel for
    {
        for (int i = 0; i < MAXVAL; i++)
            values[i] = omp_get_thread_num();
    }

    for(int i = 0; i < MAXVAL; i++) {
        printf("%d ", values[i]);
        if(i % 10 == 0)
            printf("\n");
    }
    printf("counter : %d\n", counter);

    for (int i = 0; i < numT; ++i) {
        printf("it :%d - thread %d\n", i, c[i]);
        sum += c[i];
    }

    printf("counter = %d\n\n", counter);

    return 0;
}




