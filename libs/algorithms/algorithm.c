//
// Created by yaros on 18.02.2024.
//

#include <stdio.h>


void swap(void * a, void * b, size_t len){
    unsigned char * p = a, * q = b, tmp;
    for (size_t i = 0; i != len; ++i)
    {
        tmp = p[i];
        p[i] = q[i];
        q[i] = tmp;
    }
}

int max(int a, int b) {
    return a > b ? a : b;
}

unsigned int factorial(unsigned int n){
    int result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    //printf("factorial is %u\n", result);
    return result;
}