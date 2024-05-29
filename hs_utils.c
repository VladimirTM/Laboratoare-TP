#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int estePar(int n)
{
    return (n % 2) == 0;
}

int esteImpar(int n)
{
    return (n % 2) == 1;
}

int esteNegativ(int n)
{
    return n < 0;
}

int estePozitiv(int n)
{
    return n >= 0;
}