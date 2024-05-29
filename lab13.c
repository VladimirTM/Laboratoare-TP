#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "hs_utils.h"

// Problema 13.1

void p1(int n)
{
    printf("Numarul %d este impar %d este par %d este negativ %d este pozitiv %d\n", n, esteImpar(n), estePar(n), esteNegativ(n), estePozitiv(n));
}

// Problema 13.2

int *makeRandArray(int seed, int n)
{
    int *array = NULL, i;
    if ((array = malloc(n * sizeof(int))) == NULL)
    {
        return NULL;
    }
    srand(seed);
    for (i = 0; i < n; i++)
    {
        array[i] = rand();
    }
    return array;
}

void p2(void)
{
    int *array, i;
    array = makeRandArray(10, 10);
    for (i = 0; i < 10; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
    free(array);
}

// Problema 13.3

int *makeRandLimitArray(int seed, int n, int a, int b)
{
    int *array = NULL, i, nr;
    if ((array = malloc(n * sizeof(int))) == NULL)
    {
        return NULL;
    }
    srand(seed);
    for (i = 0; i < n; i++)
    {
        nr = rand();
        if (a < nr && nr < b)
        {
            array[i] = nr;
        }
        else
        {
            i--;
        }
    }
    return array;
}

void p3(void)
{
    int *array, i;
    array = makeRandLimitArray(10, 10, 1000, 4000);
    for (i = 0; i < 10; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
    free(array);
}

// Problema 13.4

int findElemLin(int *v, int n, int x)
{
    int i;
    for (i = 0; i < n; i++)
    {
        if (v[i] == x)
        {
            return i;
        }
    }
    return -1;
}

int findElemBin(int *v, int n, int x)
{
    int start, stop, mijloc;
    start = 0;
    stop = n - 1;
    while (start <= stop)
    {
        mijloc = (start + stop) / 2;
        if (v[mijloc] == x)
        {
            return mijloc;
        }
        else
        {
            if (v[mijloc] < x)
            {
                stop = mijloc - 1;
            }
            else
            {
                start = mijloc + 1;
            }
        }
    }
    return -1;
}

int comparare(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}

void testareLiniara(int *array)
{
    int i, nr;
    time_t start, end;
    double time_taken;
    for (i = 0; i < 100; i++)
    {
        printf("Iteratia liniara %d: ", i);
        nr = rand() % 10000;
        start = clock();
        findElemLin(array, 50000, nr);
        end = clock();
        time_taken = ((double)end - start) / CLOCKS_PER_SEC;
        printf("%.10f\n", time_taken);
    }
}

void testareLogaritmica(int *array)
{
    int i, nr;
    time_t start, end;
    double time_taken;
    for (i = 0; i < 100; i++)
    {
        printf("Iteratia logaritmica %d: ", i);
        nr = rand() % 10000;
        start = clock();
        findElemBin(array, 50000, nr);
        end = clock();
        time_taken = ((double)end - start) / CLOCKS_PER_SEC;
        printf("%.10f\n", time_taken);
    }
}

void p4(void)
{
    int v[] = {1, 2, 3, 4};
    printf("%d\n", findElemLin(v, 4, 0));
    printf("%d\n", findElemBin(v, 4, 5));
    int *array = NULL, i;
    array = malloc(50000 * sizeof(int));
    for (i = 0; i < 50000; i++)
    {
        array[i] = rand() % 10000;
    }
    testareLiniara(array);
    qsort(array, 50000, sizeof(int), comparare);
    testareLogaritmica(array);
    free(array);
}

int main(void)
{
    // p1(10);
    // p2();
    // p3();
    p4();
    return 0;
}