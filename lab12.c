#include <stdio.h>

#define MAX 100

int n, k;
int ans[MAX];

// Problema 12.1

int verificare1(int p)
{
    if (ans[p] == 0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int solutie1(int p)
{
    int count = 0, i;
    for (i = 0; i <= p; i++)
    {
        if (ans[i] == 1)
        {
            count++;
        }
    }
    return (p == n - 1 && count == k);
}

void afisare1(void)
{
    int i;
    for (i = 0; i < n; i++)
    {
        printf("%d", ans[i]);
    }
    printf("\n");
}

void back1(int p)
{
    int i;
    if (p == n)
    {
        return;
    }
    for (i = 0; i <= 9; i++)
    {
        ans[p] = i;
        if (verificare1(p))
        {
            if (solutie1(p))
            {
                afisare1();
            }
            else
            {
                back1(p + 1);
            }
        }
    }
}

void p1(void)
{
    n = 3;
    k = 2;
    back1(0);
}

// Problema 12.2

int verificare2(int p)
{
    int i;
    for (i = 1; i < p; i++)
    {
        if (ans[i] == ans[p])
        {
            return 0;
        }
    }
    return 1;
}
int solutie2(int p)
{
    int mijloc, i, j;
    if (p == n)
    {
        mijloc = n / 2 + n % 2;
        for (i = 1; i < mijloc; i++)
        {
            for (j = i + 1; j <= mijloc; j++)
            {
                if (ans[i] < ans[j])
                {
                    return 0;
                }
            }
        }
        for (i = mijloc; i < n; i++)
        {
            for (j = i + 1; j <= n; j++)
            {
                if (ans[i] > ans[j])
                {
                    return 0;
                }
            }
        }
        return 1;
    }
    else
    {
        return 0;
    }
}

void afisare2(void)
{
    int i;
    for (i = 1; i <= n; i++)
    {
        printf("%d", ans[i]);
    }
    printf("\n");
}

void back2(int p)
{
    int i;
    for (i = 1; i <= n; i++)
    {
        ans[p] = i;
        if (verificare2(p))
        {
            if (solutie2(p))
            {
                afisare2();
            }
            else
            {
                back2(p + 1);
            }
        }
    }
}

void p2(void)
{
    n = 5;
    back2(1);
}

// Problema 12.3

int numV[MAX], len, max;

void descompunere(int nr)
{
    int aux = nr, count = 0;
    len = 0;
    while (aux)
    {
        count++;
        aux = aux / 10;
    }
    while (nr)
    {
        numV[count - len] = nr % 10;
        len++;
        nr = nr / 10;
    }
}

int verificare3(int p)
{
    int i;
    for (i = 1; i < p; i++)
    {
        if (ans[i] >= ans[p])
        {
            return 0;
        }
    }
    return 1;
}

int solutie3(int p)
{
    if (p == (len - k))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int numar(void)
{
    int i, numar = 0;
    for (i = 1; i <= (len - k); i++)
    {
        numar = numar * 10 + numV[ans[i]];
    }
    return numar;
}

void back3(int p)
{
    int i, aux;
    for (i = 1; i <= len; i++)
    {
        ans[p] = i;
        if (verificare3(p))
        {
            if (solutie3(p))
            {
                aux = numar();
                if (aux > max)
                {
                    max = aux;
                }
            }
            else
            {
                back3(p + 1);
            }
        }
    }
}

void p3(void)
{
    n = 3452234;
    k = 4;
    descompunere(n);
    back3(1);
    printf("%d\n", max);
}

// Problema 12.4

char culori[7][100] = {" ", "alb", "galben", "rosu", "verde", "albastru", "negru"};

int verificare4(int p)
{
    int i;
    for (i = 1; i < p; i++)
    {
        if (ans[i] == ans[p])
        {
            return 0;
        }
    }
    return 1;
}

int solutie4(int p)
{
    if (p == 3 && (ans[2] == 4 || ans[2] == 2))
    {
        return 1;
    }
    return 0;
}

void afisare4()
{
    int i;
    for (i = 1; i <= 3; i++)
    {
        printf("%s ", culori[ans[i]]);
    }
    printf("\n");
}

void back4(int p)
{
    int i;
    for (i = 1; i <= 6; i++)
    {
        ans[p] = i;
        if (verificare4(p))
        {
            if (solutie4(p))
            {
                afisare4();
            }
            else
            {
                back4(p + 1);
            }
        }
    }
}

void p4(void)
{
    back4(1);
}

// Problema 12.5

float volume[MAX] = {0.0, 1.23, 3.47, 0.89, 4.12, 2.36, 4.78, 1.56, 3.09, 0.45, 2.78, 4.33, 1.98, 3.67, 0.11, 2.45, 3.79, 4.56, 0.67, 2.88, 3.21}, volum;

int verificare5(int p)
{
    int i;
    for (i = 1; i < p; i++)
    {
        if (ans[i] == ans[p])
        {
            return 0;
        }
    }
    return 1;
}

int solutie5(int p)
{
    int i;
    float suma = 0.0;
    for (i = 1; i <= p; i++)
    {
        suma = suma + volume[ans[i]];
    }
    return suma <= volum;
}

void afisare5(int p)
{
    int i;
    for (i = 1; i <= p; i++)
    {
        printf("%f ", volume[ans[i]]);
    }
    printf("\n");
}

void back5(int p)
{
    int i;
    for (i = 1; i <= n; i++)
    {
        ans[p] = i;
        if (verificare5(p))
        {
            if (solutie5(p))
            {
                afisare5(p);
            }
            back5(p + 1);
        }
    }
}

void p5(void)
{
    n = 5;
    volum = 6.6;
    back5(1);
}

// Problema 12.6

int c, b, g, a;
char entitati[5][100] = {"", "casa", "bloc", "gradina", "atelier"};

int verificare6(int p)
{
    if (p != 1)
    {
        switch (ans[p])
        {
        case 1:
        {
            if (ans[p - 1] == 1 || ans[p - 1] == 2 || ans[p - 1] == 3)
            {
                return 1;
            }
            break;
        }
        case 2:
        {
            if (ans[p - 1] == 1 || ans[p - 1] == 2)
            {
                return 1;
            }
            break;
        }
        case 3:
        {
            if (ans[p - 1] == 1 || ans[p - 1] == 3 || ans[p - 1] == 4)
            {
                return 1;
            }
            break;
        }
        case 4:
        {
            if (ans[p - 1] == 3 || ans[p - 1] == 4)
            {
                return 1;
            }
            break;
        }
        }
    }
    else
    {
        return 1;
    }
    return 0;
}

int solutie6(int p)
{
    int i, countC = 0, countB = 0, countG = 0, countA = 0;
    for (i = 1; i <= p; i++)
    {
        switch (ans[i])
        {
        case 1:
        {
            countC++;
            break;
        }
        case 2:
        {
            countB++;
            break;
        }
        case 3:
        {
            countG++;
            break;
        }
        case 4:
        {
            countA++;
            break;
        }
        }
    }
    return (c == countC && b == countB && g == countG && a == countA);
}

void afisare6(void)
{
    int i;
    for (i = 1; i <= c + b + g + a; i++)
    {
        printf("%s ", entitati[ans[i]]);
    }
    printf("\n");
}

void back6(int p)
{
    if (p > c + b + g + a)
    {
        return;
    }
    int i;
    for (i = 1; i <= 4; i++)
    {
        ans[p] = i;
        if (verificare6(p))
        {
            if (solutie6(p))
            {
                afisare6();
            }
            else
            {
                back6(p + 1);
            }
        }
    }
}

void p6(void)
{
    c = 2;
    b = 1;
    g = 1;
    a = 1;
    back6(1);
}

// Problema 12.7

int laturi[100] = {0, 1, 2, 2, 1}, latura;

int verificare7(int p)
{
    int i;
    for(i = 1; i < p; i++)
    {
        if(ans[i] == ans[p])
        {
            return 0;
        }
    }
    return 1;
}

int solutie7(int p)
{
    int arieMare = 0, arieSolutie = 0, i;
    arieMare = latura * latura;
    for(i = 1; i <= p; i++)
    {
        arieSolutie = arieSolutie + ans[i] * ans[i];
    }
    return (arieSolutie <= arieMare) && (p == n);
}

void back7(int p)
{
    int i;
    for(i = 1; i <= n; i++)
    {
        ans[p] = i;
        if(verificare7(p))
        {
            if(solutie7(p))
            {
                k = 1;
            }
            else
            {
                back7(p + 1);
            }
        }
    }
}

void p7(void)
{
    n = 4;
    k = 0;
    latura = 4;
    back7(1);
    if(k == 1)
    {
        printf("Exista configuratie\n");
    }
    else
    {
        printf("Nu exista configuratie\n");
    }
}

// Problema 12.8

int lungime;

int verificare8(int p)
{
    int i;
    for(i = 1; i < p; i++)
    {
        if(ans[i] >= ans[p])
        {
            return 0;
        }
    }
    return 1;
}

int solutie8(int p)
{
    int i, suma = 0;
    for(i = 1; i <=p; i++)
    {
        suma = suma + ans[i];
    }
    return (suma == lungime) && (p == n);
}

void afisare8(void)
{
    int i;
    for(i = 1; i <= n; i++)
    {
        printf("%d ", ans[i]);
    }
    printf("\n");
}

void back8(int p)
{
    int i;
    for(i = 1; i <= lungime; i++)
    {
        ans[p] = i;
        if(verificare8(p))
        {
            if(solutie8(p))
            {
                afisare8();
            }
            else
            {
                back8(p + 1);
            }
        }
    }
}

void p8(void)
{
    lungime = 20;
    n = 3;
    back8(1);
}

int main(void)
{
    p8();
    return 0;
}
