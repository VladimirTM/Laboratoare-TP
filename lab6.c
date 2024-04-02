#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

// Problema 1

void err(int condition, const char *fmt, ...)
{
    if (condition)
    {
        va_list va;
        va_start(va, fmt);
        fprintf(stderr, "eroare: ");
        vfprintf(stderr, fmt, va);
        va_end(va);
        fputc('\n', stderr);
        exit(EXIT_FAILURE);
    }
}

void p1(void)
{
    int i, n;
    float x, y, e, min, max;
    printf("n=");
    scanf("%d", &n);
    err(n <= 0 || n > 100, "n invalid: %d\n", n);
    printf("x=");
    scanf("%g", &x);
    printf("y=");
    scanf("%g", &y);
    err(x >= y, "x=%g nu este mai mic decat y=%g\n", x, y);
    max = x;
    min = y;
    for (i = 0; i < n; i++)
    {
        printf("e=");
        scanf("%g", &e);
        err(e < x || e > y, "element invalid: %g\n", e);
        if (e < min)
            min = e;
        if (e > max)
            max = e;
    }
    printf("min: %g, max: %g\n", min, max);
}

// Problema 2

float *allocVec(int n, ...)
{
    va_list va;
    va_start(va, n);
    float *f = NULL;
    if ((f = malloc(n * sizeof(float))) == NULL)
    {
        va_end(va);
        return NULL;
    }
    for (int i = 0; i < n; i++)
    {
        f[i] = va_arg(va, double);
    }
    va_end(va);
    return f;
}

void p2(void)
{
    float *f;
    f = allocVec(3, 7.2, 2.1, 0.4);
    for (int i = 0; i < 3; i++)
    {
        printf("%f ", f[i]);
    }
    printf("\n");
    free(f);
}

// Problema 3

void absN(int n, ...)
{
    va_list va;
    float *ptr;
    va_start(va, n);
    for (int i = 0; i < n; i++)
    {
        ptr = va_arg(va, float *);
        *ptr = fabs(*ptr);
    }
    va_end(va);
}

void p3(void)
{
    float x = -12.3, y = 4.5;
    absN(2, &x, &y);
    printf("%f %f\n", x, y);
}

// Problema 4

int crescator(char tip, int n, ...)
{
    va_list va;
    va_start(va, n);
    int x, i, ant_x;
    float y, ant_y;
    for (i = 0; i < n; i++)
    {
        if (i == 0)
        {
            switch (tip)
            {
            case 'd':
            {
                ant_x = va_arg(va, int);
            }
            case 'f':
            {
                ant_y = va_arg(va, double);
            }
            }
        }
        else
        {
            switch (tip)
            {
            case 'd':
            {
                x = va_arg(va, int);
                if (x < ant_x)
                {
                    return 0;
                }
                ant_x = x;
            }
            case 'i':
            {
                y = va_arg(va, double);
                if (y < ant_y)
                {
                    return 0;
                }
                ant_y = y;
            }
            }
        }
    }
    return 1;
}

void p4(void)
{
    printf("%d\n", crescator(3, 'd', -1, 7, 9));
}

// Problema 5

void input(const char *fmt, ...)
{
    int *ptr1, i;
    float *ptr2;
    char *ptr3;
    va_list va;
    // for (i = 0; i < strlen(fmt); i++)
    // {
    //     if (fmt[i] == '%')
    //     {
    //         contor++;
    //     }
    // }
    va_start(va, fmt);
    for (i = 1; i < strlen(fmt); i++)
    {
        if (fmt[i - 1] == '%')
        {
            switch (fmt[i])
            {
            case 'd':
            {
                ptr1 = va_arg(va, int *);
                scanf("%d", ptr1);
                break;
            }
            case 'f':
            {
                ptr2 = va_arg(va, float *);
                scanf("%f", ptr2);
                break;
            }
            case 'c':
            {
                ptr3 = va_arg(va, char *);
                scanf(" %c", ptr3);
                break;
            }
            }
        }
    }
    va_end(va);
}

void p5(void)
{
    int n;
    char ch;
    input("n=%dch=%c", &n, &ch);
    printf("%d %c\n", n, ch);
}

// Problema 6

char *concat(int n, ...)
{
    char *string, *concatS = NULL;
    va_list va;
    va_start(va, n);
    int i;
    for (i = 0; i < n; i++)
    {
        string = va_arg(va, char *);
        if ((concatS = realloc(concatS, (strlen(string) + 1) * sizeof(char))) == NULL)
        {
            va_end(va);
            return NULL;
        }
        strcat(concatS, string);
        strcat(concatS, " ");
    }
    va_end(va);
    return concatS;
}

void p6(void)
{
    char *string = concat(3, "Ion", "si", "Ana");
    printf("%s\n", string);
    free(string);
}

// Problema 7

int comune(int nVec, ...)
{
    va_list va;
    va_start(va, nVec);
    int *v, *ant[2], i, sizeV, sizeAnt, j, k, contor = 0;
    for (i = 0; i < nVec; i++)
    {
        if (i == 0)
        {
            ant[0] = va_arg(va, int *);
            sizeAnt = va_arg(va, int);
            for (j = 0; j < sizeAnt; j++)
            {
                ant[1][j] = 1;
            }
        }
        else
        {
            v = va_arg(va, int *);
            sizeV = va_arg(va, int);
            for (j = 0; j < sizeAnt; j++)
            {
                contor = 0;
                for (k = 0; k < sizeV; k++)
                {
                    if (ant[0][j] == v[k])
                    {
                        contor++;
                    }
                }
                ant[1][j] += contor;
            }
        }
    }
    va_end(va);
    contor = 0;
    for (i = 0; i < sizeAnt; i++)
    {
        if (ant[1][i] == nVec)
        {
            contor++;
        }
    }
    return contor;
}

void p7(void)
{
    int v1[] = {5, 8}, v2[] = {8, 3, 5}, v3[] = {5, 0, 8};
    printf("%d\n", comune(3, v1, 2, v2, 3, v3, 3));
}

// Problema 8

void sortare(int n, ...)
{
    int *v = NULL;
    if ((v = malloc(n * sizeof(int))) == NULL)
    {
        return;
    }
    va_list va;
    va_start(va, n);
    int i, j, aux;
    for (i = 0; i < n; i++)
    {
        v[i] = *(va_arg(va, int *));
    }
    va_end(va);
    for (i = 0; i < n - 1; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (v[i] > v[j])
            {
                aux = v[i];
                v[i] = v[j];
                v[j] = aux;
            }
        }
    }
    va_start(va, n);
    for (i = 0; i < n; i++)
    {
        *(va_arg(va, int *)) = v[i];
    }
    free(v);
    va_end(va);
}

void p8(void)
{
    int x = 5, y = 3, z = 8;
    sortare(3, &x, &y, &z);
    printf("%d %d %d\n", x, y, z);
}

// Problema 9

void p9(int argc, char **argv)
{
    int i;
    float s = 0;
    for (i = 1; i < argc; i++)
    {
        s += atof(argv[i]);
    }
    printf("%f\n", s);
}

// Problema 10

void encode(char *cuvant, int cheie)
{
    int i;
    for (i = 0; i < strlen(cuvant); i++)
    {
        if (cuvant[i] + cheie > 'z')
        {
            cuvant[i] = 'a' + (cuvant[i] + cheie - 'z' - 1);
        }
        else
        {
            cuvant[i] = cuvant[i] + cheie;
        }
    }
    printf("%s ", cuvant);
}

void decode(char *cuvant, int cheie)
{
    int i;
    for (i = 0; i < strlen(cuvant); i++)
    {
        if (cuvant[i] - cheie < 'a')
        {
            cuvant[i] = 'z' - ('a' - (cuvant[i] - cheie) - 1);
        }
        else
        {
            cuvant[i] = cuvant[i] - cheie;
        }
    }
    printf("%s ", cuvant);
}

void p10(int argc, char **argv)
{
    int i, cheie, j;
    char *operatie;
    operatie = argv[1];
    cheie = atoi(argv[2]);
    for (i = 3; i < argc; i++)
    {
        for (j = 0; j < strlen(argv[i]); j++)
        {
            argv[i][j] = tolower(argv[i][j]);
        }
        if (strcmp(operatie, "enc") == 0)
        {
            encode(argv[i], cheie);
        }
        else if (strcmp(operatie, "dec") == 0)
        {
            decode(argv[i], cheie);
        }
    }
    printf("\n");
}

// Problema 11

void p11(int argc, char **argv)
{
    float expresie, numar;
    int i;
    expresie = atof(argv[1]);
    for (i = 2; i < argc; i+=2)
    {
        if (strcmp(argv[i], "add") == 0)
        {
            numar = atof(argv[i + 1]);
            expresie += numar;
        }
        else if (strcmp(argv[i], "sub") == 0)
        {
            numar = atof(argv[i + 1]);
            expresie -= numar;
        }
        else if (strcmp(argv[i], "mul") == 0)
        {
            numar = atof(argv[i + 1]);
            expresie *= numar;
        }
        else if (strcmp(argv[i], "div") == 0)
        {
            numar = atof(argv[i + 1]);
            expresie /= numar;
        }
    }
    printf("%f\n", expresie);
}

// Problema 12

void uOptiune(char *cuvant)
{
    int i;
    for (i = 0; i < strlen(cuvant); i++)
    {
        cuvant[i] = toupper(cuvant[i]);
    }
}

void fOptiune(char *cuvant)
{
    int i;
    cuvant[0] = toupper(cuvant[0]);
    for (i = 1; i < strlen(cuvant); i++)
    {
        cuvant[i] = tolower(cuvant[i]);
    }
}

void rOptiune(char *cuvant)
{
    char aux;
    int i, j;
    i = 0;
    j = strlen(cuvant) - 1;
    while (i < j)
    {
        aux = cuvant[i];
        cuvant[i] = cuvant[j];
        cuvant[j] = aux;
        i++;
        j--;
    }
}

void p12(int argc, char **argv)
{
    int i, optiune[3] = {0}, j;
    for(i = 1; i < argc; i++)
    {
        if(strcmp(argv[i], "-u") == 0)
        {
            optiune[0] = 1;
        }
        else if(strcmp(argv[i], "-f") == 0)
        {
            optiune[1] = 1;
        }
        else if(strcmp(argv[i], "-r") == 0)
        {
            optiune[2] = 1;
        }
        else
        {
            for(j = 0; j < 3; j++)
            {
                if(optiune[j] == 1)
                {
                    switch(j)
                    {
                        case 0:
                        {
                            uOptiune(argv[i]);
                            break;
                        }
                        case 1:
                        {
                            fOptiune(argv[i]);
                            break;
                        }
                        case 2:
                        {
                            rOptiune(argv[i]);
                            break;
                        }
                    }
                }
            }
            printf("%s ", argv[i]);
            for(j = 0; j < 3; j++)
            {
                optiune[j] = 0;
            }
        }
    }
    printf("\n");
}

// Problema 13

void p13(int argc, char **argv)
{
    int i, cod, aparitii[52] = {0}, contor = 0, j;
    cod = atoi(argv[1]);
    switch(cod)
    {
        case 0:
        {
            for(i = 2; i < argc; i++)
            {
                for(j = 0; j < strlen(argv[i]); j++)
                {
                    if(isalpha(argv[i][j]))
                    {
                        contor++;
                    }
                }
            }
            printf("%d\n", contor);
            break;
        }
        case 1:
        {
            for(i = 2; i < argc; i++)
            {
                for(j = 0; j < strlen(argv[i]); j++)
                {
                    if(isalpha(argv[i][j]))
                    {
                        if(isupper(argv[i][j]))
                        {
                            aparitii[argv[i][j] - 'A' + 26]++;
                        }
                        else
                        {
                            aparitii[argv[i][j] - 'a']++;
                        }
                    }
                }
            }
            for(i = 0; i < 52; i++)
            {
                if(aparitii[i] != 0)
                {
                    if(i < 26)
                    {
                        printf("%c %d\n", i + 'a', aparitii[i]);
                    }
                    else
                    {
                        printf("%c %d\n", i - 26 + 'A', aparitii[i]);
                    }
                }
            }
            break;
        }
    }
}

int main(int argc, char **argv)
{
    p13(argc, argv);
    return 0;
}