#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdarg.h>
#include <ctype.h>
#include <string.h>

int suma, *array = NULL, *valori, n;

int valid1(int pozitie)
{
    int s = 0, i;
    for (i = 0; i <= pozitie; i++)
    {
        if (i > 0 && array[i] < array[i - 1])
        {
            return 0;
        }
        s = s + array[i];
    }
    return s <= suma;
}

int solutie1(int pozitie)
{
    int s = 0, i;
    for (i = 0; i <= pozitie; i++)
    {
        s = s + array[i];
    }
    return s == suma;
}

void afisare1(int pozitie, FILE *file)
{
    int i, contor, anterior;
    contor = 1;
    anterior = -1;
    for (i = 0; i < pozitie; i++)
    {
        if (anterior == -1)
            ;
        else
        {
            if (anterior == array[i])
            {
                contor++;
            }
            else
            {
                fprintf(file, "%d*%d ", contor, anterior);
                contor = 1;
            }
        }
        anterior = array[i];
    }

    if (anterior == array[pozitie])
    {
        contor++;
        fprintf(file, "%d*%d ", contor, anterior);
    }
    else
    {
        fprintf(file, "%d*%d ", contor, anterior);
        contor = 1;
        fprintf(file, "%d*%d ", contor, array[pozitie]);
    }

    fprintf(file, "\n");
}

void back1(int pozitie, FILE *file)
{
    int i;
    for (i = 0; i < n; i++)
    {
        array[pozitie] = valori[i];
        if (valid1(pozitie))
        {
            if (solutie1(pozitie))
            {
                afisare1(pozitie, file);
            }
            else
            {
                back1(pozitie + 1, file);
            }
        }
    }
}

void p1(void)
{
    FILE *in, *out;
    in = fopen("n.txt", "r");
    out = fopen("rezultate.txt", "w");
    fscanf(in, "%d", &n);
    valori = malloc(n * sizeof(int));
    int i;
    for (i = 0; i < n; i++)
    {
        fscanf(in, "%d", &valori[i]);
    }
    fscanf(in, "%d", &suma);
    array = malloc((suma + 1) * sizeof(int));
    back1(0, out);
    free(valori);
    free(array);
    fclose(in);
    fclose(out);
}

// Problema 2

void initFisier1(void)
{
    int numar = 7, a[] = {7, 8, 10, 10, 10, 2, 6}, s = 30, i;
    FILE *out = NULL;
    out = fopen("credite.in", "wb");
    fprintf(out, "%d\n", numar);
    for (i = 0; i < numar; i++)
    {
        fprintf(out, "%d ", a[i]);
    }
    fprintf(out, "\n%d\n", s);
    fclose(out);
}

int valid2(int pozitie)
{
    int i, s = 0;
    for (i = 0; i <= pozitie; i++)
    {
        if (i > 0 && array[i] > array[i - 1])
        {
            return 0;
        }
        s = s + array[i];
    }
    return s <= suma;
}

int solutie2(int pozitie)
{
    int i, s = 0;
    for (i = 0; i <= pozitie; i++)
    {
        s = s + array[i];
    }
    return s >= suma;
}

void afisare2(int pozitie, FILE *file)
{
    fprintf(file, "%d, ", pozitie + 1);
    int i;
    for (i = 0; i <= pozitie; i++)
    {
        fprintf(file, "%d ", array[i]);
    }
    fprintf(file, "\n");
}

void back2(int pozitie, FILE *file)
{
    int i;
    for (i = 0; i < n; i++)
    {
        array[pozitie] = valori[i];
        if (valid2(pozitie))
        {
            if (solutie2(pozitie))
            {
                afisare2(pozitie, file);
            }
            else
            {
                back2(pozitie + 1, file);
            }
        }
    }
}

void p2(void)
{
    initFisier1();
    FILE *in, *out;
    in = fopen("credite.in", "rb");
    out = fopen("examene.out", "w");
    fscanf(in, "%d", &n);
    valori = malloc(n * sizeof(int));
    int i;
    for (i = 0; i < n; i++)
    {
        fscanf(in, "%d", &valori[i]);
    }
    fscanf(in, "%d", &suma);
    array = malloc((suma + 1) * sizeof(int));
    back2(0, out);
    free(valori);
    free(array);
    fclose(in);
    fclose(out);
}

// Problema 3

int m;

void initFisier2(void)
{
    int a = 3, b = 6;
    FILE *out = NULL;
    out = fopen("sesiune.in", "wb");
    fprintf(out, "%d %d\n", a, b);
    fclose(out);
}

int valid3(int pozitie)
{
    int i;
    if (pozitie == 0)
    {
        return 1;
    }
    else
    {
        for (i = 0; i < pozitie; i++)
        {
            if (array[i] != 0 && array[pozitie] != 0 && array[i] >= array[pozitie])
            {
                return 0;
            }
        }
    }
    return (array[pozitie - 1] == 0 || array[pozitie] == 0) && pozitie <= (m - 1);
}

int solutie3(int pozitie)
{
    int s = 0, i, max = (n * (n + 1)) / 2;
    for (i = 0; i <= pozitie; i++)
    {
        s = s + array[i];
    }
    return pozitie == (m - 1) && s == max;
}

void afisare3(int pozitie, FILE *file)
{
    int i;
    for (i = 0; i <= pozitie; i++)
    {
        fprintf(file, "%d", array[i]);
    }
    fprintf(file, "\n");
}

void back3(int pozitie, FILE *file)
{
    int i;
    for (i = 0; i <= n; i++)
    {
        array[pozitie] = i;
        if (valid3(pozitie))
        {
            if (solutie3(pozitie))
            {
                afisare3(pozitie, file);
            }
            else
            {
                back3(pozitie + 1, file);
            }
        }
    }
}

void p3(void)
{
    initFisier2();
    FILE *in, *out;
    in = fopen("sesiune.in", "rb");
    out = fopen("calendar.txt", "w");
    fscanf(in, "%d %d", &n, &m);
    array = malloc((m + 1) * sizeof(int));
    back3(0, out);
    free(array);
    fclose(in);
    fclose(out);
}

// Problema 4

void initFisier3(void)
{
    int a = 6, array[] = {1, 2, 1, 3, 3, 4, 2, 3, 3, 5, 4, 5}, b = 3, i;
    FILE *out = NULL;
    out = fopen("domino.in", "wb");
    fprintf(out, "%d\n", a);
    for (i = 0; i < 2 * a; i = i + 2)
    {
        fprintf(out, "%d %d\n", array[i], array[i + 1]);
    }
    fprintf(out, "%d", b);
    fclose(out);
}

typedef struct
{
    int x1, x2;
} Domino;

Domino *piese = NULL;
int nr;

void printPiesa(int index, FILE *file)
{
    if (index / n == 0)
    {
        fprintf(file, "%d %d ", piese[index % n].x1, piese[index % n].x2);
    }
    else
    {
        fprintf(file, "%d %d ", piese[index % n].x2, piese[index % n].x1);
    }
}

int valid4(int pozitie)
{
    int i;
    for (i = 0; i < pozitie; i++)
    {
        if (array[i] % n == array[pozitie] % n)
        {
            return 0;
        }
    }
    return pozitie <= (nr - 1);
}

int solutie4(int pozitie)
{
    int i;
    if (pozitie > 0)
    {
        int j;
        for (i = 0; i < pozitie; i++)
        {
            j = i + 1;
            if (array[i] / n == 0)
            {
                if (array[j] / n == 0)
                {
                    if (piese[array[i] % n].x2 != piese[array[j] % n].x1)
                    {
                        return 0;
                    }
                }
                else
                {
                    if (piese[array[i] % n].x2 != piese[array[j] % n].x2)
                    {
                        return 0;
                    }
                }
            }
            else
            {
                if (array[j] / n == 0)
                {
                    if (piese[array[i] % n].x1 != piese[array[j] % n].x1)
                    {
                        return 0;
                    }
                }
                else
                {
                    if (piese[array[i] % n].x1 != piese[array[j] % n].x2)
                    {
                        return 0;
                    }
                }
            }
        }
    }
    return pozitie == (nr - 1);
}

void afisare4(FILE *file)
{
    int i;
    for (i = 0; i < nr; i++)
    {
        printPiesa(array[i], file);
    }
    fprintf(file, "\n");
}

void back4(int pozitie, FILE *file)
{
    int i;
    for (i = 0; i < 2 * n; i++)
    {
        array[pozitie] = i;
        if (valid4(pozitie))
        {
            if (solutie4(pozitie))
            {
                afisare4(file);
            }
            else
            {
                back4(pozitie + 1, file);
            }
        }
    }
}

void p4(void)
{
    initFisier3();
    FILE *in, *out;
    in = fopen("domino.in", "rb");
    out = fopen("aranjari.txt", "w");
    fscanf(in, "%d", &n);
    array = malloc(2 * (n + 1) * sizeof(int));
    piese = malloc((n + 1) * sizeof(Domino));
    int i;
    for (i = 0; i < n; i++)
    {
        fscanf(in, "%d %d", &piese[i].x1, &piese[i].x2);
    }
    fscanf(in, "%d", &nr);
    back4(0, out);
    free(array);
    free(piese);
    fclose(in);
    fclose(out);
}

// Problema 5

void initFisier4(void)
{
    int a = 10;
    FILE *out = NULL;
    out = fopen("n.in", "wb");
    fprintf(out, "%d\n", a);
    fclose(out);
}

int valid5(int pozitie)
{
    int i, count0 = 0, count1 = 0;
    for (i = 0; i <= pozitie; i++)
    {
        if (array[i] == 0)
        {
            count0++;
        }
        else
        {
            count1++;
        }
    }
    if (count1 > count0)
    {
        return 0;
    }
    return pozitie <= (n - 1);
}

int solutie5(int pozitie)
{
    int i, count0 = 0, count1 = 0;
    for (i = 0; i <= pozitie; i++)
    {
        if (array[i] == 0)
        {
            count0++;
        }
        else
        {
            count1++;
        }
    }
    return count0 == count1 && pozitie == (n - 1);
}

void afisare5(FILE *file)
{
    int i;
    for (i = 0; i < n; i++)
    {
        if (array[i] == 0)
        {
            fprintf(file, "(");
        }
        else
        {
            fprintf(file, ")");
        }
    }
    fprintf(file, "\n");
}

void back5(int pozitie, FILE *file)
{
    int i;
    for (i = 0; i <= 1; i++)
    {
        array[pozitie] = i;
        if (valid5(pozitie))
        {
            if (solutie5(pozitie))
            {
                afisare5(file);
            }
            else
            {
                back5(pozitie + 1, file);
            }
        }
    }
}

void p5(void)
{
    initFisier4();
    FILE *in, *out;
    in = fopen("n.in", "rb");
    out = fopen("solutii.txt", "w");
    fscanf(in, "%d", &n);
    array = malloc((n + 1) * sizeof(int));
    back5(0, out);
    free(array);
    fclose(in);
    fclose(out);
}

// Problema 6

double d(int x)
{
    return sin(x) + pow(2, x);
}

double e(int x)
{
    return pow(3, x);
}

double f(int x)
{
    return x;
}

double g(int x)
{
    return 1 + 2 * x + 3 * x * x + 4 * x * x * x;
}

double b(int x, double (*d)(int), double (*e)(int))
{
    return d(x) * e(x);
}

double c(int x, double (*f)(int), double (*g)(int))
{
    return f(x) / g(x);
}

double a(int x, double (*b)(int, double (*)(int), double (*)(int)), double (*c)(int, double (*)(int), double (*)(int)), double (*d)(int), double (*e)(int), double (*f)(int), double (*g)(int))
{
    return b(x, d, e) + c(x, f, g);
}

void initFisier5(void)
{
    int a = 2;
    FILE *out = NULL;
    out = fopen("x.in", "wb");
    fprintf(out, "%d\n", a);
    fclose(out);
}

void p6(void)
{
    initFisier5();
    FILE *in = NULL, *out = NULL;
    in = fopen("x.in", "rb");
    out = fopen("rezultate.txt", "w");
    int x;
    fscanf(in, "%d", &x);
    fprintf(out, "a(%d) = %f\n", x, a(x, b, c, d, e, f, g));
    fprintf(out, "b(%d) = %f\n", x, b(x, d, e));
    fprintf(out, "c(%d) = %f\n", x, c(x, f, g));
    fprintf(out, "d(%d) = %f\n", x, d(x));
    fprintf(out, "e(%d) = %f\n", x, e(x));
    fprintf(out, "f(%d) = %f\n", x, f(x));
    fclose(in);
    fclose(out);
}

// Problema 7

void p7(void)
{
    FILE *in, *out = NULL;
    in = fopen("cuvinte.txt", "r");
    out = fopen("compuse.txt", "w");
    int n, pozitie, i;
    char buffer[100];
    fscanf(in, "%d", &n);
    for (i = 0; i < n; i++)
    {
        fscanf(in, "%d", &pozitie);
        fscanf(in, "%99s", buffer);
        if (pozitie > (strlen(buffer) - 1))
        {
            fprintf(out, "%c\n", buffer[strlen(buffer) - 1]);
        }
        else
        {
            fprintf(out, "%c\n", buffer[pozitie]);
        }
    }
    fclose(in);
    fclose(out);
}

// Problema 8

typedef enum
{
    casatorit,
    necasatorit,
    divortat,
    vaduv
} StareCivila;

typedef union
{
    int nrCopii : 5;
    float inaltime;
    int timpDivort : 7;
    char initiala;
} Carateristica;

typedef struct
{
    char nume[20];
    char prenume[20];
    int dataNasterii;
    char sex;
    StareCivila stareCivila;
    Carateristica carateristica;
} Persoana;

// Problema 9

typedef struct
{
    char cuvant[20];
    char explicatie[200];
} Dictionar;

// Problema 10

typedef struct nod
{
    int info;
    struct nod *next;
} Nod;

Nod *newNod(int info)
{
    Nod *new = NULL;
    new = malloc(1 * sizeof(Nod));
    new->info = info;
    new->next = NULL;
    return new;
}

Nod *adaugaNod(int info, Nod *lista)
{
    Nod *new = newNod(info);
    if (lista == NULL)
    {
        lista = new;
    }
    else
    {
        Nod *aux = NULL;
        for (aux = lista; aux->next != NULL; aux = aux->next)
            ;
        aux->next = new;
    }
    return lista;
}

void afisareLista(Nod *lista)
{
    Nod *aux;
    for (aux = lista; aux != NULL; aux = aux->next)
    {
        printf("%d ", aux->info);
    }
    printf("\n");
}

void fafisareLista(Nod *lista, FILE *file)
{
    Nod *aux;
    for (aux = lista; aux != NULL; aux = aux->next)
    {
        fprintf(file, "%d ", aux->info);
    }
    fprintf(file, "\n");
}

void freeLista(Nod *lista)
{
    Nod *aux;
    while (lista != NULL)
    {
        aux = lista;
        lista = lista->next;
        free(aux);
    }
}

Nod *reuniune(Nod *lista1, Nod *lista2)
{
    Nod *newLista = NULL, *aux = NULL, *aux2 = NULL;
    int ok = 1;
    for (aux = lista1; aux != NULL; aux = aux->next)
    {
        newLista = adaugaNod(aux->info, newLista);
    }
    for (aux = lista2; aux != NULL; aux = aux->next)
    {
        ok = 1;
        for (aux2 = newLista; aux2 != NULL; aux2 = aux2->next)
        {
            if (aux->info == aux2->info)
            {
                ok = 0;
            }
        }
        if (ok == 1)
        {
            newLista = adaugaNod(aux->info, newLista);
        }
    }
    return newLista;
}

Nod *intersectie(Nod *lista1, Nod *lista2)
{
    Nod *newLista = NULL, *aux1 = NULL, *aux2 = NULL;
    for (aux1 = lista1; aux1 != NULL; aux1 = aux1->next)
    {
        for (aux2 = lista2; aux2 != NULL; aux2 = aux2->next)
        {
            if (aux1->info == aux2->info)
            {
                newLista = adaugaNod(aux1->info, newLista);
            }
        }
    }
    return newLista;
}

void p10(void)
{
    FILE *multimeA = NULL, *multimeB = NULL;
    multimeA = fopen("multimeA.txt", "r+w");
    multimeB = fopen("multimeB.txt", "r+w");
    int aux;
    Nod *listaA = NULL, *listaB = NULL;
    // a
    while (fscanf(multimeA, "%d", &aux) == 1)
    {
        listaA = adaugaNod(aux, listaA);
    }
    while (fscanf(multimeB, "%d", &aux) == 1)
    {
        listaB = adaugaNod(aux, listaB);
    }
    afisareLista(listaA);
    afisareLista(listaB);
    // b
    Nod *reunion = NULL;
    reunion = reuniune(listaA, listaB);
    afisareLista(reunion);
    // c
    Nod *intersection = NULL;
    intersection = intersectie(listaA, listaB);
    afisareLista(intersection);
    // d
    fafisareLista(reunion, multimeA);
    fafisareLista(intersection, multimeA);
    fafisareLista(reunion, multimeB);
    fafisareLista(intersection, multimeB);
    fclose(multimeA);
    fclose(multimeB);
    freeLista(listaA);
    freeLista(listaB);
    freeLista(reunion);
    freeLista(intersection);
}

// Problema 11

int verificare(Nod *lista)
{
    Nod *aux = NULL;
    int index = 0;
    if (lista->info == '(')
    {
        for (aux = lista; aux != NULL; aux = aux->next)
        {
            if (index == 0)
            {
                if (aux->info != '(')
                {
                    return 0;
                }
            }
            else
            {
                if (index == 4)
                {
                    if (aux->info != ')')
                    {
                        return 0;
                    }
                }
                else
                {
                    if (index == 8)
                    {
                        if (aux->info != '-')
                        {
                            return 0;
                        }
                    }
                    else
                    {
                        if (isnumber(aux->info) == 0)
                        {
                            return 0;
                        }
                    }
                }
            }
            index++;
        }
        if (index - 1 != 12)
        {
            return 0;
        }
    }
    else
    {
        for (aux = lista; aux != NULL; aux = aux->next)
        {
            if (index == 3)
            {
                if (aux->info != '-')
                {
                    return 0;
                }
            }
            else
            {
                if (index == 7)
                {
                    if (aux->info != '-')
                    {
                        return 0;
                    }
                }
                else
                {
                    if (isnumber(aux->info) == 0)
                    {
                        return 0;
                    }
                }
            }
            index++;
        }
        if (index - 1 != 11)
        {
            return 0;
        }
    }
    return 1;
}

void afisareTelefon(Nod *lista)
{
    Nod *aux = NULL;
    for (aux = lista; aux != NULL; aux = aux->next)
    {
        printf("%c", aux->info);
    }
    printf("\n");
}

void p11(void)
{
    Nod *numarTelefon = NULL;
    FILE *in = NULL;
    in = fopen("numar.txt", "r");
    char ch;
    while (fscanf(in, "%c", &ch) == 1)
    {
        numarTelefon = adaugaNod(ch, numarTelefon);
    }
    if (verificare(numarTelefon) == 1)
    {
        afisareTelefon(numarTelefon);
    }
    else
    {
        printf("Numar de telefon invalid\n");
    }
    freeLista(numarTelefon);
    fclose(in);
}

// Problema 12

Nod *inversare(Nod *lista)
{
    if(lista == NULL)
    {
        return lista;
    }
    Nod *anterior = NULL, *aux = NULL, *urmator = NULL;
    for(anterior = lista, aux = lista->next; aux->next != NULL; anterior = aux, aux = urmator)
    {
        urmator = aux->next;
        aux->next = anterior;
    }
    aux->next = anterior;
    lista->next = NULL;
    lista = aux;
    return lista;
}

void p12(void)
{
    FILE *in = NULL;
    in = fopen("multimeA.txt", "r");
    int aux;
    Nod *lista = NULL;
    while (fscanf(in, "%d", &aux) == 1)
    {
        lista = adaugaNod(aux, lista);
    }
    afisareLista(lista);
    lista = inversare(lista);
    afisareLista(lista);
    freeLista(lista);
    fclose(in);
}

int main(void)
{
    p12();
    return 0;
}
