#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define SIZE 100

// Problema 8.1

int *readArray(int size)
{
    int *array = NULL, i, nr;
    if ((array = malloc(size * sizeof(int))) == NULL)
    {
        return NULL;
    }
    for (i = 0; i < size; i++)
    {
        if (scanf("%d", &nr) != 1)
        {
            array[i] = -1;
        }
        else
        {
            array[i] = nr;
        }
    }
    return array;
}

int **readMatrix(int linie, int coloana)
{
    int **matrix = NULL, *array, i;
    if ((matrix = malloc(linie * sizeof(int *))) == NULL)
    {
        return NULL;
    }
    for (i = 0; i < linie; i++)
    {
        if ((array = readArray(coloana)) == NULL)
        {
            continue;
        }
        else
        {
            matrix[i] = array;
        }
    }
    return matrix;
}

void printMatrix(int **matrix, int linie, int coloana)
{
    int i, j;
    for (i = 0; i < linie; i++)
    {
        for (j = 0; j < coloana; j++)
        {
            printf("%2d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int verificareMatrice(int **m1, int **m2, int pozi, int pozj, int size)
{
    int i, j;
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            if (m1[i + pozi][j + pozj] != m2[i][j])
            {
                return 0;
            }
        }
    }
    return 1;
}

void freeMatrix(int **matrix, int linie)
{
    int i;
    for (i = 0; i < linie; i++)
    {
        free(matrix[i]);
    }
}

void p1(void)
{
    int n, m, **m1, **m2, i, j, ok = 0;
    scanf("%d %d", &n, &m);
    m1 = readMatrix(n, n);
    m2 = readMatrix(m, m);
    for (i = 0; i <= (n - m); i++)
    {
        for (j = 0; j <= (n - m); j++)
        {
            if (verificareMatrice(m1, m2, i, j, m) == 1)
            {
                printf("(%d,%d)", i, j);
                ok++;
            }
        }
    }
    if (ok == 0)
    {
        printf("Nu apare");
    }
    printf("\n");
    freeMatrix(m1, n);
    freeMatrix(m2, m);
    free(m1);
    free(m2);
}

// Problema 8.2

char *readCharArray(int size)
{
    char *array = NULL, ch;
    int i;
    if ((array = malloc(size * sizeof(char))) == NULL)
    {
        return NULL;
    }
    for (i = 0; i < size; i++)
    {

        if (scanf("%c", &ch) != 1)
        {
            array[i] = 0;
        }
        else
        {
            if (!isalpha(ch))
            {
                i--;
                continue;
            }
            else
            {
                array[i] = ch;
            }
        }
    }
    return array;
}

char **readCharMatrix(int linie, int coloana)
{
    char **matrix = NULL, *array;
    int i;
    if ((matrix = malloc(linie * sizeof(char *))) == NULL)
    {
        return NULL;
    }
    for (i = 0; i < linie; i++)
    {
        if ((array = readCharArray(coloana)) == NULL)
        {
            continue;
        }
        else
        {
            matrix[i] = array;
        }
    }
    return matrix;
}

void printCharMatrix(char **matrix, int linie, int coloana)
{
    int i, j;
    for (i = 0; i < linie; i++)
    {
        for (j = 0; j < coloana; j++)
        {
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }
}

void freeCharMatrix(char **matrix, int linie)
{
    int i;
    for (i = 0; i < linie; i++)
    {
        free(matrix[i]);
    }
}

void verificareLinieSD(char **matrix, char *cuvant, int linie, int size, int *aparitie)
{
    int ok = 1, i, j;
    for (i = 0; i < size; i++)
    {
        ok = 0;
        if (matrix[linie][i] == cuvant[0])
        {
            ok = 1;
            for (j = 0; j < strlen(cuvant); j++)
            {
                if (i + j >= size)
                {
                    ok = 0;
                    j = strlen(cuvant);
                }
                else
                {
                    if (matrix[linie][i + j] != cuvant[j])
                    {
                        ok = 0;
                    }
                }
            }
        }
        if (ok == 1)
        {
            printf("De la linia %d coloana %d spre dreapta.\n", linie, i);
            *aparitie = *aparitie + 1;
        }
    }
}

void verificareLinieDS(char **matrix, char *cuvant, int linie, int size, int *aparitie)
{
    int ok = 1, i, j;
    for (i = (size - 1); i >= 0; i--)
    {
        ok = 0;
        if (matrix[linie][i] == cuvant[0])
        {
            ok = 1;
            for (j = 0; j < strlen(cuvant); j++)
            {
                if (i - j < 0)
                {
                    ok = 0;
                    j = strlen(cuvant);
                }
                else
                {
                    if (matrix[linie][i - j] != cuvant[j])
                    {
                        ok = 0;
                    }
                }
            }
        }
        if (ok == 1)
        {
            printf("De la linia %d coloana %d spre stânga.\n", linie, i);
            *aparitie = *aparitie + 1;
        }
    }
}

void verificareColoanaSJ(char **matrix, char *cuvant, int coloana, int size, int *aparitie)
{
    int ok = 1, i, j;
    for (i = 0; i < size; i++)
    {
        ok = 0;
        if (matrix[i][coloana] == cuvant[0])
        {
            ok = 1;
            for (j = 0; j < strlen(cuvant); j++)
            {
                if (i + j >= size)
                {
                    ok = 0;
                    j = strlen(cuvant);
                }
                else
                {
                    if (matrix[i + j][coloana] != cuvant[j])
                    {
                        ok = 0;
                    }
                }
            }
        }
        if (ok == 1)
        {
            printf("De la linia %d coloana %d în jos.\n", i, coloana);
            *aparitie = *aparitie + 1;
        }
    }
}

void verificareColoanaJS(char **matrix, char *cuvant, int coloana, int size, int *aparitie)
{
    int ok = 1, i, j;
    for (i = (size - 1); i >= 0; i--)
    {
        ok = 0;
        if (matrix[i][coloana] == cuvant[0])
        {
            ok = 1;
            for (j = 0; j < strlen(cuvant); j++)
            {
                if (i - j < 0)
                {
                    ok = 0;
                    j = strlen(cuvant);
                }
                else
                {
                    if (matrix[i - j][coloana] != cuvant[j])
                    {
                        ok = 0;
                    }
                }
            }
        }
        if (ok == 1)
        {
            printf("De la linia %d coloana %d în sus.\n", i, coloana);
            *aparitie = *aparitie + 1;
        }
    }
}

void p2(void)
{
    char **matrix = NULL, cuvant[SIZE];
    int n, aparitie = 0, i;
    scanf("%d", &n);
    matrix = readCharMatrix(n, n);
    scanf("%99s", cuvant);
    for (i = 0; i < n; i++)
    {
        verificareLinieSD(matrix, cuvant, i, n, &aparitie);
        verificareLinieDS(matrix, cuvant, i, n, &aparitie);
        verificareColoanaSJ(matrix, cuvant, i, n, &aparitie);
        verificareColoanaJS(matrix, cuvant, i, n, &aparitie);
    }
    if (aparitie == 0)
    {
        printf("Nu există soluție\n");
    }
    freeCharMatrix(matrix, n);
    free(matrix);
}

// Problema 8.3

void printStaticMatrix(int matrix[20][10], int linie, int coloana)
{
    int i, j;
    for (i = 0; i < linie; i++)
    {
        for (j = 0; j < coloana; j++)
        {
            printf("%3d ", *(&matrix[0][0] + i * coloana + j));
        }
        printf("\n");
    }
}

void p3(void)
{
    int matrix[20][10], m, n, nr = 1, i, j;
    scanf("%d %d", &m, &n);
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            *(&matrix[0][0] + i * n + j) = nr;
            nr++;
        }
    }
    printStaticMatrix(matrix, m, n);
}

// Problema 8.4

void swap(int *a, int *b)
{
    int aux;
    aux = *a;
    *a = *b;
    *b = aux;
}

void p4(void)
{
    int **matrix = NULL, n, i, j;
    scanf("%d", &n);
    matrix = readMatrix(n, n);
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (i < j)
            {
                swap(&matrix[i][j], &matrix[j][i]);
            }
        }
    }
    printMatrix(matrix, n, n);
    freeMatrix(matrix, n);
    free(matrix);
}

// Problema 8.5

void printArray(int *array, int size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        printf("%d ", *(array + i));
    }
    printf("\n");
}

void p5(void)
{
    int **matrix = NULL, suma[20], produs[20], n, i, j, s, p;
    scanf("%d", &n);
    matrix = readMatrix(n, n);
    for (i = 0; i < n; i++)
    {
        s = 0;
        p = 1;
        for (j = 0; j < n; j++)
        {
            s = s + matrix[i][j];
            p = p * matrix[i][j];
        }
        suma[i] = s;
        produs[i] = p;
    }
    printArray(suma, n);
    printArray(produs, n);
    freeMatrix(matrix, n);
    free(matrix);
}

// Problema 8.6

void p6(void)
{
    int matrix[10][10], n, i, j = 0, prieten;
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        j = 0;
        scanf("%d", &prieten);
        // consider -1 ca punct de oprire pentru citirea pritenilor
        while (prieten != -1)
        {
            matrix[i][j++] = prieten;
            scanf("%d", &prieten);
        }
        printf("Persoana %d are %d prieteni.\n", i, j);
    }
}

// Problema 8.7

void p7(void)
{
    int **matrix = NULL, n, i, j, min = 999999999;
    scanf("%d", &n);
    // consider ca pun in matrice patratica, iar distanta intre un oras si el insusi este 0
    matrix = readMatrix(n, n);
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (matrix[i][j] > 0)
            {
                if (matrix[i][j] < min)
                {
                    min = matrix[i][j];
                }
            }
        }
    }
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (matrix[i][j] == min)
            {
                printf("(%d,%d)\n", i, j);
            }
        }
    }
    freeMatrix(matrix, n);
    free(matrix);
}

// Problema 8.8

void readStaticMatrix(int m[10][10], int linie, int coloana)
{
    int i, j;
    for (i = 0; i < linie; i++)
    {
        for (j = 0; j < coloana; j++)
        {
            scanf("%d", &m[i][j]);
        }
    }
}

void p8(void)
{
    int m, n, p, a[10][10], b[10][10], c[10][10], i, j, k, suma;
    scanf("%d %d %d", &m, &n, &p);
    readStaticMatrix(a, m, n);
    readStaticMatrix(b, n, p);
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < p; j++)
        {
            suma = 0;
            for (k = 0; k < n; k++)
            {
                suma += a[i][k] * b[k][j];
            }
            c[i][j] = suma;
        }
    }
    printStaticMatrix(c, m, p);
}

// Problema 8.9

void p9(void)
{
    int n, m[10][10], i, j;
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (i == j || i + j == n - 1)
            {
                m[i][j] = 1;
            }
            else
            {
                m[i][j] = 0;
            }
        }
    }
    printStaticMatrix(m, n, n);
}

// Problema 8.10

void p10(void)
{
    int m[4][10], n, i, j, ok = 0, ant = -1;
    scanf("%d", &n);
    for(i = 0; i < 4; i++)
    {
        for(j = 0; j < n; j++)
        {
            scanf("%d", &m[i][j]);
        }
    }
    for(i = 0; i < 4; i++)
    {
        ok = 1;
        for(j = 0; j < n; j++)
        {
            if(ant != -1)
            {
                if(ant >= m[i][j])
                {
                    ok = 0;
                }
            }
            ant = m[i][j];
        }
        if(ok == 1)
        {
            printf("Produsul %d a avut o crestere continua pe parcursul anului.\n", i);
        }
    }
}

int main(void)
{
    return 0;
}