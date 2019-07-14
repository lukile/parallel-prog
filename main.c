#include <stdio.h>
#include <stdlib.h>
#include <bits/time.h>
#include <time.h>

char* msgdyn;

int main() {

    int val = 33;
    struct timespec start, end;
    msgdyn = malloc(5*sizeof(char));
    clock_gettime(CLOCK_MONOTONIC, &start);

    printf("\nle code est en %p\n", main);
    printf("\nles datas sont en %p\n", &msgdyn);
    printf("\nle pile est en %p\n", &val);
    printf("\nle tas est en %p\n", msgdyn);

    clock_gettime(CLOCK_MONOTONIC, &end);
    printf("\nDt: %lds %ldns\n", end.tv_sec - start.tv_sec, end.tv_nsec - start.tv_nsec);

    return 0;
}