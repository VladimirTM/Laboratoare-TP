#include <stdio.h>
#include <stdlib.h>

// Problema 11.1 Greedy

int origine[2][1];

int comparare(const void *a, const void *b)
{
    int x1, y1, x2, y2, dist1, dist2;
    x1 = ((int *)a)[0];
    y1 = ((int *)a)[1];
    x2 = ((int *)b)[0];
    y2 = ((int *)b)[1];
    dist1 = (x1 - origine[0][0]) * (x1 - origine[0][0]) + (y1 - origine[1][0]) * (y1 - origine[1][0]);
    dist2 = (x2 - origine[0][0]) * (x2 - origine[0][0]) + (y2 - origine[1][0]) * (y2 - origine[1][0]);
    return dist1 - dist2;
}

void p1(void)
{
    int n, coordonate[2][100], i;
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        scanf("%d %d", &coordonate[0][i], &coordonate[1][i]);
    }

    qsort(coordonate, n, 2 * sizeof(int), comparare);

    for (i = 0; i < n; i++)
    {
        printf("%d %d\n", coordonate[0][i], coordonate[1][i]);
    }
}

// Problema 11.2 Divide et Impera

void p2(void)
{
    int n, i;
    double ma, mb, m, d, G = 667400000000, pas, x = 0.0, Fa, Fb;
    scanf("%d %lf %lf %lf %lf", &n, &ma, &mb, &m, &d);

    pas = d / n;

    for (i = 0; i <= n; i++)
    {
        Fa = G * ma * m / (x * x);
        Fb = G * mb * m / ((d - x) * (d - x));
        printf("%lf %lf %lf\n", x, Fa, Fb);
        x += pas;
    }
}

// Problema 11.3 Divide et Impera

int reduceMatrix(int matrice[][100], int m, int n)
{
    if (m == 0 || n == 0)
    {
        return 0;
    }
    else if (m == 1 && n == 1)
    {
        return matrice[0][0];
    }
    else
    {
        int mijlocRand = m / 2;
        int mijlocColoana = n / 2;

        int stangaSus[m][n], dreaptaSus[m][n], stangaJos[m][n], dreaptaJos[m][n];

        for (int i = 0; i < mijlocRand; i++)
        {
            for (int j = 0; j < mijlocColoana; j++)
            {
                stangaSus[i][j] = matrice[i][j];
            }
        }

        for (int i = 0; i < mijlocRand; i++)
        {
            for (int j = mijlocColoana; j < n; j++)
            {
                dreaptaSus[i][j - mijlocColoana] = matrice[i][j];
            }
        }

        for (int i = mijlocRand; i < m; i++)
        {
            for (int j = 0; j < mijlocColoana; j++)
            {
                stangaJos[i - mijlocRand][j] = matrice[i][j];
            }
        }

        for (int i = mijlocRand; i < m; i++)
        {
            for (int j = mijlocColoana; j < n; j++)
            {
                dreaptaJos[i - mijlocRand][j - mijlocColoana] = matrice[i][j];
            }
        }

        int reducereStangaSus = reduceMatrix(stangaSus, mijlocRand, mijlocColoana);
        int reducereDreaptaSus = reduceMatrix(dreaptaSus, mijlocRand, n - mijlocColoana);
        int reducereStangaJos = reduceMatrix(stangaJos, m - mijlocRand, mijlocColoana);
        int reducereDreaptaJos = reduceMatrix(dreaptaJos, m - mijlocRand, n - mijlocColoana);

        int maximSus = (reducereStangaSus > reducereDreaptaSus) ? reducereStangaSus : reducereDreaptaSus;
        int minimJos = (reducereStangaJos < reducereDreaptaJos) ? reducereStangaJos : reducereDreaptaJos;

        return maximSus - minimJos;
    }
}

void p3(void)
{
    int m, n, matrice[100][100], i, j;
    scanf("%d %d", &m, &n);
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            scanf("%d", &matrice[i][j]);
        }
    }

    printf("%d\n", reduceMatrix(matrice, m, n));
}

// Problema 11.4 Greedy

typedef struct
{
    char nume[15];
    int valoare;
} Jucator;

int comparareJucatori(const void *a, const void *b)
{
    Jucator *jucator1 = (Jucator *)a;
    Jucator *jucator2 = (Jucator *)b;
    return jucator1->valoare - jucator2->valoare;
}

void p4(void)
{
    int n, m, i, count = 0;
    Jucator jucatori[100];
    scanf("%d %d", &n, &m);
    for (i = 0; i < n; i++)
    {
        scanf("%s %d", jucatori[i].nume, &jucatori[i].valoare);
    }

    qsort(jucatori, n, sizeof(Jucator), comparareJucatori);

    for (i = n - 1; i >= 0; i--)
    {
        if (count == n / m)
        {
            printf("\n");
            count = 0;
        }
        printf("%s %d\n", jucatori[i].nume, jucatori[i].valoare);
        count++;
    }
}

// Problema 11.5 Divide et Impera

void afisareLiterara(int n)
{
    if (n < 0 || n >= 1000)
    {
        printf("Numarul trebuie sa fie intre 0 si 999.\n");
        return;
    }

    const char *unitati[] = {"zero", "unu", "doi", "trei", "patru", "cinci", "sase", "sapte", "opt", "noua"};
    const char *zeci[] = {"", "zece", "douazeci", "treizeci", "patruzeci", "cincizeci", "saizeci", "saptezeci", "optzeci", "nouazeci"};
    const char *sute[] = {"", "o suta", "doua sute", "trei sute", "patru sute", "cinci sute", "sase sute", "sapte sute", "opt sute", "noua sute"};

    int suta = n / 100;
    int zecile = (n / 10) % 10;
    int unitatea = n % 10;

    printf("%s", sute[suta]);

    if (suta == 0 && zecile == 0 && unitatea == 0)
    {
        printf(" zero");
    }
    else if (zecile == 1)
    {
        if (unitatea == 0)
        {
            printf(" zece");
        }
        else if (unitatea == 1)
        {
            printf(" unsprezece");
        }
        else if (unitatea == 2)
        {
            printf(" doisprezece");
        }
        else if (unitatea == 3)
        {
            printf(" treisprezece");
        }
        else if (unitatea == 4)
        {
            printf(" paisprezece");
        }
        else if (unitatea == 5)
        {
            printf(" cincisprezece");
        }
        else if (unitatea == 6)
        {
            printf(" saisprezece");
        }
        else if (unitatea == 7)
        {
            printf(" saptesprezece");
        }
        else if (unitatea == 8)
        {
            printf(" optsprezece");
        }
        else if (unitatea == 9)
        {
            printf(" nouasprezece");
        }
    }
    else
    {
        printf(" %s", zeci[zecile]);
        if (unitatea != 0)
        {
            printf(" %s", unitati[unitatea]);
        }
    }

    printf("\n");
}

void p5(void)
{
    int n;
    while (1)
    {
        printf("Introduceti un numar (0-999): ");
        scanf("%d", &n);
        if (n == 1000)
        {
            break;
        }
        afisareLiterara(n);
    }
}

int main(void)
{
    p5();
    return 0;
}