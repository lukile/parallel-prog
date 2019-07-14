//
// Created by lukile on 27/06/19.
//
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
//gcc lab4.c -à lab4 -fopenmp
#define MAXVALUE 1024*1024

int NL = 0;

int tid;

int counter = 0;
int values[MAXVALUE];

int main() {
    int i;
    double start, end;
    int tid;
    long sum = 0;

    start = omp_get_wtime();
#pragma omp parallel for firstprivate(tid)
    for(i = 0; i < MAXVALUE; i++) {
        tid = omp_get_thread_num();
        values[i] = tid;
//Cette ligne ne s'execute que dans un thread a la fois. Equivalent d'un lock avant et d'un unlock apres
#pragma omp atomic
        sum += tid;
    }
    end = omp_get_wtime();

    for(i = 0; i < MAXVALUE; i++) {
        printf("%d  ", values[i]);

        if(i+1 % 50 == 0) {
            printf("\n");
        }
    }

    printf("\n");
    printf("Time : %f s\n", end - start);
    printf("TOTAL %ld\n", sum);
    return 0;
}

