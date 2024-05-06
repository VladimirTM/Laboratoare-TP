#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Problema 10.1

int cmmdc(int a, int b)
{
    if (b == 0)
    {
        return a;
    }
    else
    {
        return cmmdc(b, a % b);
    }
}

void p1(void)
{
    printf("%d\n", cmmdc(24, 8));
}

// Problema 10.2

int suma_cifrelor(int n)
{
    if (n < 10)
    {
        return n;
    }
    else
    {
        return n % 10 + suma_cifrelor(n / 10);
    }
}

void p2(void)
{
    printf("%d\n", suma_cifrelor(123));
}

// Problema 10.3

int max(int a, int b)
{
    if (a > b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

int cifra_max(int n)
{
    if (n < 10)
    {
        return n;
    }
    else
    {
        return max(n % 10, cifra_max(n / 10));
    }
}

void p3(void)
{
    printf("%d\n", cifra_max(264368));
}

// Problema 10.4

int fib(int n)
{
    if (n == 1 | n == 0)
    {
        return 1;
    }
    else
    {
        return fib(n - 1) + fib(n - 2);
    }
}

void p4(void)
{
    printf("%d\n", fib(4));
}

// Problema 10.5

char *strFib(int n, char *s1, char *s2)
{
    if (n == 1)
    {
        return s1;
    }
    else if (n == 2)
    {
        return s2;
    }
    else
    {
        char *result = (char *)malloc(strlen(s1) + strlen(s2) + 1);
        strcpy(result, s1);
        strcat(result, s2);
        return strFib(n - 1, s2, result);
    }
}

void p5(void)
{
    char *s1 = "a";
    char *s2 = "b";
    printf("%s\n", strFib(10, s1, s2));
}

// Problema 10.6

float phi(int n)
{
    if (n <= 0)
    {
        return 1.0;
    }
    else
    {
        float fib_n = fib(n);
        float fib_n_minus_1 = fib(n - 1);
        return fib_n / fib_n_minus_1;
    }
}

void p6(void)
{
    printf("%f\n", phi(20));
}

// Problema 10.7

float serieTaylor(float *valoare, float *termenAnterior, int *n, int x, float precizie)
{
    if (*termenAnterior < precizie)
    {
        return *valoare;
    }
    else
    {
        *n = *n + 1;
        *termenAnterior = *termenAnterior * x / *n;
        *valoare = *valoare + *termenAnterior;
        return serieTaylor(valoare, termenAnterior, n, x, precizie);
    }
}

void p7(void)
{
    float valoare = 1;
    float termenAnterior = 1;
    int n = 0;
    int x = 1;
    float precizie = 0.000001;
    printf("%f\n", serieTaylor(&valoare, &termenAnterior, &n, x, precizie));
}

// Problema 10.8

int binarySearch(int *v, int st, int dr, int x)
{
    if (st > dr)
    {
        return -1;
    }
    else
    {
        int mij = (st + dr) / 2;
        if (v[mij] == x)
        {
            return mij;
        }
        else if (v[mij] < x)
        {
            return binarySearch(v, mij + 1, dr, x);
        }
        else
        {
            return binarySearch(v, st, mij - 1, x);
        }
    }
}

void p8(void)
{
    int v[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    if(binarySearch(v, 0, 8, 10) != -1)
    {
        printf("Elementul a fost gasit\n");
    }
    else
    {
        printf("Elementul nu a fost gasit\n");
    }
}

int main(void)
{
    p8();
    return 0;
}