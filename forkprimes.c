#include "forkprimes.h"

/* 0 for false, anything else for true */
int is_divisible (int N, int* primes, int len)
{
    int i;
    int* ptr;
    int root = sqrt(N);

    for(i = 0, ptr = primes; i < len; i++, ptr++)
    {
        if(N % (*ptr) == 0)
            return 1; // Found a divisor so return
        if(*ptr > root)
            return 0;
    }

    // Nothing in primes divides n so return
    return 0;
}

int* find_primes(int N)
{
    /* Returns a list of prime numbers smaller than N */ 
    int i;
    int count = 1;
    int pos = 1;
    int size = sizeof(int) * (N / 2);

    int* primes;
    if(!(primes = (int *)malloc(size)))
    {
        printf("ERROR: MEMORY ALLOCATION FAILED!\n");
        exit(-1);
    }
    
    primes[0] = 2;
    for(i = 3; i < N; i++)
    {
        if(!(is_divisible(i, primes, count++)))
            primes[pos++] = i;
    }

    return primes;
}
