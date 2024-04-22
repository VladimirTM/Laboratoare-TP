#include <stdio.h>
#include <stdlib.h>

// Problema 9.1

typedef struct nod1
{
    int info;
    struct nod1 *next;
} Nod1;

Nod1 *init1(int info, Nod1 *next)
{
    Nod1 *nou = NULL;
    if ((nou = malloc(1 * sizeof(Nod1))) == NULL)
    {
        return NULL;
    }
    nou->info = info;
    nou->next = next;
    return nou;
}

Nod1 *adaugaSfarsit1(Nod1 *nou, Nod1 *lista)
{
    Nod1 *aux = NULL;
    if (lista == NULL)
    {
        lista = nou;
    }
    else
    {
        for (aux = lista; aux->next != NULL; aux = aux->next)
            ;
        aux->next = nou;
    }
    return lista;
}

Nod1 *stergeInceput1(Nod1 **lista)
{
    Nod1 *auxLista = *lista, *inceput = NULL;
    if (auxLista == NULL)
    {
        return NULL;
    }
    else
    {
        inceput = auxLista;
        auxLista = auxLista->next;
    }
    *lista = auxLista;
    return inceput;
}

void afisareLista1(Nod1 *lista)
{
    Nod1 *aux = NULL;
    for (aux = lista; aux != NULL; aux = aux->next)
    {
        printf("%d ", aux->info);
    }
    printf("\n");
}

void freeLista1(Nod1 *lista)
{
    Nod1 *aux = NULL;
    while (lista != NULL)
    {
        aux = lista;
        lista = lista->next;
        free(aux);
    }
}

void p1(FILE *file)
{
    int k, i, info;
    Nod1 *lista = NULL, *aux;
    fscanf(file, "%d", &k);
    while (fscanf(file, "%d", &info) == 1)
    {
        aux = init1(info, NULL);
        lista = adaugaSfarsit1(aux, lista);
    }
    afisareLista1(lista);
    for (i = 0; i < k; i++)
    {
        aux = stergeInceput1(&lista);
        aux->next = NULL;
        lista = adaugaSfarsit1(aux, lista);
    }
    afisareLista1(lista);
    freeLista1(lista);
}

// Problema 9.2

void p2(FILE *file)
{
    int info;
    Nod1 *listaPara = NULL, *listaImpara = NULL, *aux;
    while (fscanf(file, "%d", &info) == 1)
    {
        aux = init1(info, NULL);
        if (info % 2 == 0)
        {
            listaPara = adaugaSfarsit1(aux, listaPara);
        }
        else
        {
            listaImpara = adaugaSfarsit1(aux, listaImpara);
        }
    }
    afisareLista1(listaPara);
    afisareLista1(listaImpara);
    for (aux = listaPara; aux->next != NULL; aux = aux->next)
        ;
    aux->next = listaImpara;
    afisareLista1(listaPara);
    freeLista1(listaPara);
}

// Problema 9.3

Nod1 *adaugareSpeciala1(Nod1 *lista)
{
    Nod1 *aux = NULL, *nou = NULL;
    for (aux = lista; aux != NULL; aux = aux->next)
    {
        if (aux->info % 2 == 0)
        {
            nou = init1(aux->info / 2, aux->next);
            aux->next = nou;
        }
    }
    return lista;
}

void p3(FILE *file)
{
    int info;
    Nod1 *lista = NULL, *aux;
    while (fscanf(file, "%d", &info) == 1)
    {
        aux = init1(info, NULL);
        lista = adaugaSfarsit1(aux, lista);
    }
    lista = adaugareSpeciala1(lista);
    afisareLista1(lista);
    freeLista1(lista);
}

// Problema 9.4

typedef struct nod2
{
    int info;
    struct nod2 *anterior, *urmator;
} Nod2;

Nod2 *init2(int info, Nod2 *anterior, Nod2 *urmator)
{
    Nod2 *nou = NULL;
    if ((nou = malloc(1 * sizeof(Nod2))) == NULL)
    {
        return NULL;
    }
    nou->info = info;
    nou->anterior = anterior;
    nou->urmator = urmator;
    return nou;
}

Nod2 *adaugaSfarsit2(Nod2 *nou, Nod2 *lista)
{
    Nod2 *aux = NULL;
    if (lista == NULL)
    {
        lista = nou;
    }
    else
    {
        for (aux = lista; aux->urmator != NULL; aux = aux->urmator)
            ;
        aux->urmator = nou;
        nou->anterior = aux;
    }
    return lista;
}

void afisareLista2(Nod2 *lista)
{
    Nod2 *aux = NULL;
    for (aux = lista; aux != NULL; aux = aux->urmator)
    {
        printf("%d ", aux->info);
    }
    printf("\n");
}

void freeLista2(Nod2 *lista)
{
    Nod2 *aux = NULL;
    while (lista != NULL)
    {
        aux = lista;
        lista = lista->urmator;
        free(aux);
    }
}

void p4(FILE *file)
{
    int info, auxSwap;
    Nod2 *aux = NULL, *lista = NULL;
    while (fscanf(file, "%d", &info) == 1)
    {
        aux = init2(info, NULL, NULL);
        lista = adaugaSfarsit2(aux, lista);
    }
    afisareLista2(lista);
    for (aux = lista; aux != NULL && aux->urmator != NULL; aux = aux->urmator->urmator)
    {
        auxSwap = aux->info;
        aux->info = aux->urmator->info;
        aux->urmator->info = auxSwap;
    }
    afisareLista2(lista);
    freeLista2(lista);
}

// Problema 9.5

Nod2 *stegereSpeciala1(Nod2 *lista)
{
    Nod2 *aux = NULL, *anterior = NULL;
    if (lista == NULL)
    {
        return lista;
    }
    else
    {
        if (lista->urmator == NULL)
        {
            freeLista2(lista);
            return NULL;
        }
        else
        {
            if (lista->urmator->urmator == NULL)
            {
                freeLista2(lista);
                return NULL;
            }
            else
            {
                aux = lista;
                lista = lista->urmator;
                free(aux);
                for (aux = lista; aux->urmator->urmator != NULL; aux = aux->urmator)
                    ;
                anterior = aux;
                aux = aux->urmator;
                anterior->urmator = NULL;
                free(aux);
            }
        }
    }
    return lista;
}

void p5(FILE *file)
{
    int info;
    Nod2 *aux = NULL, *lista = NULL;
    while (fscanf(file, "%d", &info) == 1)
    {
        aux = init2(info, NULL, NULL);
        lista = adaugaSfarsit2(aux, lista);
    }
    afisareLista2(lista);
    lista = stegereSpeciala1(lista);
    afisareLista2(lista);
    freeLista2(lista);
}

// Problema 9.6

Nod2 *adaugareSpeciala2(Nod2 *lista)
{
    Nod2 *aux = NULL, *inceput = lista, *sfarsit = NULL;
    if (lista->urmator == NULL)
    {
        return lista;
    }
    else
    {
        for (aux = lista; aux->urmator->urmator != NULL; aux = aux->urmator)
            ;
        sfarsit = aux->urmator;
        aux->urmator = NULL;
        sfarsit->urmator = inceput;
        sfarsit->anterior = NULL;
        lista = sfarsit;
    }
    return lista;
}

void p6(FILE *file)
{
    int info;
    Nod2 *aux = NULL, *lista = NULL;
    while (fscanf(file, "%d", &info) == 1)
    {
        aux = init2(info, NULL, NULL);
        lista = adaugaSfarsit2(aux, lista);
    }
    afisareLista2(lista);
    lista = adaugareSpeciala2(lista);
    afisareLista2(lista);
    freeLista2(lista);
}

// Problema 9.7

int palindrom(int numar)
{
    int oglindit = 0, copie = numar;
    while (copie != 0)
    {
        oglindit = oglindit * 10 + copie % 10;
        copie = copie / 10;
    }
    return (oglindit == numar);
}

void p7(FILE *file)
{
    int info, numar = 0, p = 1;
    Nod2 *aux = NULL, *lista = NULL;
    while (fscanf(file, "%d", &info) == 1)
    {
        aux = init2(info, NULL, NULL);
        lista = adaugaSfarsit2(aux, lista);
    }
    for (aux = lista; aux != NULL; aux = aux->urmator)
    {
        numar = aux->info * p + numar;
        p = p * 10;
    }
    if (palindrom(numar) == 1)
    {
        printf("Numarul este palindrom\n");
    }
    else
    {
        printf("Numarul nu este palindrom\n");
    }
    freeLista2(lista);
}

// Problrma 9.8

Nod1 *adaugareSpeciala3(Nod1 *lista)
{
    Nod1 *inceput = lista, *aux;
    lista = lista->next;
    for (aux = lista; aux->next != NULL; aux = aux->next)
        ;
    aux->next = inceput;
    inceput->next = NULL;
    return lista;
}

void p8(FILE *file)
{
    int info;
    Nod1 *aux = NULL, *lista = NULL;
    while (fscanf(file, "%d", &info) == 1)
    {
        aux = init1(info, NULL);
        lista = adaugaSfarsit1(aux, lista);
    }
    afisareLista1(lista);
    lista = adaugareSpeciala3(lista);
    afisareLista1(lista);
    freeLista1(lista);
}

// Problema 9.9

void p9(FILE *file)
{
    int info;
    Nod1 *aux = NULL, *lista = NULL, *anterior = NULL;
    while (fscanf(file, "%d", &info) == 1)
    {
        aux = init1(info, NULL);
        lista = adaugaSfarsit1(aux, lista);
    }
    afisareLista1(lista);
    aux = lista;
    while (aux != NULL)
    {
        if (aux->info % 2 == 0)
        {
            if (anterior == NULL)
            {
                lista = aux->next;
                free(aux);
                aux = lista;
            }
            else
            {
                anterior->next = aux->next;
                free(aux);
                aux = anterior->next;
            }
        }
        else
        {
            anterior = aux;
            aux = aux->next;
        }
    }
    afisareLista1(lista);
    freeLista1(lista);
}

// Problema 9.10

void separarePareImpare(Nod1 *lista, Nod1 **listaPare, Nod1 **listaImpare)
{
    Nod1 *aux = lista, *nou = NULL;
    while (aux != NULL)
    {
        if (aux->info % 2 == 0)
        {
            nou = init1(aux->info, NULL);
            *listaPare = adaugaSfarsit1(nou, *listaPare);
        }
        else
        {
            nou = init1(aux->info, NULL);
            *listaImpare = adaugaSfarsit1(nou, *listaImpare);
        }
        aux = aux->next;
    }
}

void p10(FILE *file)
{
    int info;
    Nod1 *aux = NULL, *lista = NULL, *listaPare = NULL, *listaImpare = NULL;
    while (fscanf(file, "%d", &info) == 1)
    {
        aux = init1(info, NULL);
        lista = adaugaSfarsit1(aux, lista);
    }
    afisareLista1(lista);
    separarePareImpare(lista, &listaPare, &listaImpare);
    afisareLista1(listaPare);
    afisareLista1(listaImpare);
    freeLista1(lista);
    freeLista1(listaPare);
    freeLista1(listaImpare);
}

int main(void)
{
    FILE *file = NULL;
    file = fopen("date.in", "r");
    p10(file);
    fclose(file);
    return 0;
}