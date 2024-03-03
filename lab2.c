#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#define FILE_PATH "CUVINTE.TXT"

// Problema 2.1

typedef struct
{
    char nume[50];
    float nota;
} Rezultat;

void printRezultat(Rezultat *rezultat)
{
    printf("Elevul %s are nota %f\n", rezultat->nume, rezultat->nota);
}

int comparare(const void *r1, const void *r2)
{
    Rezultat *rezultat1 = (Rezultat *)r1, *rezultat2 = (Rezultat *)r2;
    if (rezultat1->nota < rezultat2->nota)
    {
        return 1; // le inverseaza
    }
    else
    {
        if (rezultat1->nota > rezultat2->nota)
        {
            return -1; // le lasa in pace
        }
        else
        {
            return strcmp(rezultat1->nume, rezultat2->nume); // sorteaza in functie de nume
        }
    }
}

void p1(void)
{
    int n;
    scanf("%d", &n);
    Rezultat *rezultate = NULL;
    if ((rezultate = malloc(n * sizeof(Rezultat))) == NULL)
    {
        printf("Eroare la alocare dinamica\n");
        return;
    }
    for (int i = 0; i < n; i++)
    {
        scanf("%s %f", rezultate[i].nume, &rezultate[i].nota);
    }
    qsort(rezultate, n, sizeof(Rezultat), comparare);
    for (int i = 0; i < n; i++)
    {
        printRezultat(&rezultate[i]);
    }
}

// Problema 2.2

void eliminare(int *array, int *size, int (*functie)(int))
{
    int i;
    for (i = 0; i < *size; i++)
    {
        if (!functie(array[i]))
        {
            for (int j = i; j < *size - 1; j++)
            {
                array[j] = array[j + 1];
            }
            i--;
            (*size)--;
        }
    }
}

int isNegative(int nr)
{
    if (nr < 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void printArray(int *array, int size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

void p2(void)
{
    int array[] = {-4, 5, -5, -5, 0, -2, 4, 6, 9, -10}, size = 10;
    eliminare(array, &size, isNegative);
    printArray(array, size);
}

// Problema 2.3

int verificare(const void *f1, const void *f2)
{
    float *float1 = (float *)f1, *float2 = (float *)f2;
    if (*float1 > *float2)
    {
        return 1;
    }
    else
    {
        if (*float1 < *float2)
        {
            return -1;
        }
        else
        {
            return 0;
        }
    }
}

void printFloatArray(float *array, int size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        printf("%f ", array[i]);
    }
    printf("\n");
}

void p3(void)
{
    int i, n;
    scanf("%d", &n);
    float array[10];
    for (i = 0; i < n; i++)
    {
        scanf("%f", &array[i]);
    }
    qsort(array, n, sizeof(float), verificare);
    printFloatArray(array, n);
    float x;
    scanf("%f", &x);
    if (bsearch(&x, array, n, sizeof(float), verificare) != NULL)
    {
        printf("Numarul %f exista in vector\n", x);
    }
    else
    {
        printf("Numarul %f nu exista in vector\n", x);
    }
}

// Problema 2.4

void tabelare(double a, double b, int n, double (*functie)(double))
{
    double i, pas;
    pas = (b - a) / n;
    for (i = a; i <= b; i += pas)
    {
        printf("f(%f)=%f\n", i, functie(i));
    }
}

void p4(void)
{
    printf("Functia cos\n");
    tabelare(-10, 10, 20, cos);
    printf("Functia sqrt\n");
    tabelare(0, 20, 20, sqrt);
    printf("Functia fabs\n");
    tabelare(-40, 10, 20, fabs);
}

// Problema 2.5

void tabelare2(double a, double b, int n, double (*functie)(double))
{
    double i;
    for (i = a; i <= b; i += n)
    {
        printf("f(%f)=%f\n", i, functie(i));
    }
}

double f1(double x)
{
    return (x * x * x + 4) / (x * x + 5);
}

double f2(double x)
{
    return x + 10;
}

double f3(double x)
{
    return 2 * x * x - 1;
}

void p5(void)
{
    printf("Functia f1\n");
    tabelare2(-10, 10, 2, f1);
    printf("Functia f2\n");
    tabelare2(0, 20, 3, f2);
    printf("Functia f3\n");
    tabelare2(-40, 10, 4, f3);
}

// Problema 2.6

int lungime_sir(char *text)
{
    return strlen(text);
}

int numar_vocale(char *text)
{
    int contor = 0, i;
    for (i = 0; i < strlen(text); i++)
    {
        if (strchr("AEIOUaeiou", text[i]) != NULL)
        {
            contor++;
        }
    }
    return contor;
}

int numar_litere_mari(char *text)
{
    int contor = 0, i;
    for (i = 0; i < strlen(text); i++)
    {
        if (isupper(text[i]))
        {
            contor++;
        }
    }
    return contor;
}

int diferenta_ASCII(char *text)
{
    return text[0] - text[strlen(text) - 1];
}

void p6(int argc, char **argv)
{
    FILE *f;
    if ((f = fopen(FILE_PATH, "w")) == NULL)
    {
        perror(FILE_PATH);
        return;
    }

    int (*functii[])(char *) = {lungime_sir, numar_vocale, numar_litere_mari, diferenta_ASCII}, i;

    for (i = 1; i < argc; i++)
    {
        printf("Cuvantul %s are %d litere, %d vocale, %d litere mari si diferenta dintre primul si ultimul caracter este %d\n", argv[i], functii[0](argv[i]), functii[1](argv[i]), functii[2](argv[i]), functii[3](argv[i]));
        fprintf(f, "Cuvantul %s are %d litere, %d vocale, %d litere mari si diferenta dintre primul si ultimul caracter este %d\n", argv[i], functii[0](argv[i]), functii[1](argv[i]), functii[2](argv[i]), functii[3](argv[i]));
    }

    if (fclose(f) != 0)
    {
        perror(NULL);
        return;
    }
}

int main(int argc, char **argv)
{
    p6(argc, argv);
    return 0;
}