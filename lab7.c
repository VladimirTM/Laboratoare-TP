#include <stdio.h>
#include <stdlib.h>

#define path "data.in"

FILE *file;

typedef struct nod
{
    int info;
    struct nod *next;
} nod;

void afisare(nod *lista)
{
    nod *p;
    for (p = lista; p != NULL; p = p->next)
    {
        printf("%d ", p->info);
    }
    printf("\n");
}

nod *newNod(int info, nod *next)
{
    nod *nou = NULL;
    if ((nou = malloc(1 * sizeof(nod))) == NULL)
    {
        return NULL;
    }
    nou->info = info;
    nou->next = next;
    return nou;
}

nod *adaugaInceput(int info, nod *lista)
{
    nod *nou = NULL;
    nou = newNod(info, lista);
    lista = nou;
    return lista;
}

nod *adaugaFinal(int info, nod *lista)
{
    nod *nou = NULL, *aux;
    nou = newNod(info, NULL);
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

nod *stergeInceput(nod *lista)
{
    if (lista == NULL)
    {
        return lista;
    }
    nod *aux;
    aux = lista;
    lista = lista->next;
    free(aux);
    return lista;
}

nod *stergeFinal(nod *lista)
{
    if (lista == NULL)
    {
        return lista;
    }
    if (lista->next == NULL)
    {
        free(lista);
        return NULL;
    }
    nod *aux, *final;
    for (aux = lista; aux->next->next != NULL; aux = aux->next)
        ;
    final = aux->next;
    aux->next = NULL;
    free(final);
    return lista;
}

nod *sterge(int info, nod *lista)
{
    nod *aux, *ant;
    if (lista == NULL)
    {
        return lista;
    }
    if (lista->info == info)
    {
        aux = lista;
        lista = lista->next;
        free(aux);
    }
    else
    {
        for (ant = lista, aux = lista->next; aux != NULL; ant = ant->next, aux = aux->next)
        {
            if (aux->info == info)
            {
                ant->next = aux->next;
                free(aux);
                break;
            }
        }
    }
    return lista;
}

void freeLista(nod *lista)
{
    nod *aux;
    while (lista != NULL)
    {
        aux = lista->next;
        free(lista);
        lista = aux;
    }
}

nod *init(int *size)
{
    nod *lista = NULL;
    int listSize, i, info;
    fscanf(file, "%d", &listSize);
    *size = listSize;
    for (i = 0; i < listSize; i++)
    {
        fscanf(file, "%d", &info);
        lista = adaugaFinal(info, lista);
    }
    return lista;
}

// Problema 7.1

void p1(void)
{
    nod *lista1 = NULL, *lista2 = NULL;
    int size1, size2, i, data1, data2;
    lista1 = init(&size1);
    lista2 = init(&size2);
    for (i = 0; i < (size1 < size2 ? size1 : size2); i++)
    {
        data1 = lista1->info;
        data2 = lista2->info;
        if (data1 != data2)
        {
            printf("0\n");
            free(lista1);
            free(lista2);
            return;
        }
        lista1 = stergeInceput(lista1);
        lista2 = stergeInceput(lista2);
    }
    printf("1\n");
    free(lista1);
    free(lista2);
}

// Problema 7.2

void p2(void)
{
    nod *lista = NULL;
    int size;
    lista = init(&size);
    if (lista == NULL)
    {
        return;
    }
    nod *prev, *q, *aux;
    for (prev = lista, q = lista->next; q->next != NULL; prev = q, q = aux)
    {
        aux = q->next;
        q->next = prev;
    }
    q->next = prev;
    lista->next = NULL;
    lista = q;
    afisare(lista);
    freeLista(lista);
}

// Problema 7.3

int isInList(int info, nod *lista)
{
    nod *p;
    for (p = lista; p != NULL; p = p->next)
    {
        if (p->info == info)
        {
            return 1;
        }
    }
    return 0;
}

void p3(void)
{
    nod *lista1, *lista2, *lista3 = NULL;
    int size1, size2, i, data;
    lista1 = init(&size1);
    lista2 = init(&size2);
    for (i = 0; i < size1; i++)
    {
        data = lista1->info;
        lista1 = stergeInceput(lista1);
        if (!isInList(data, lista1))
        {
            lista3 = adaugaFinal(data, lista3);
        }
    }
    for (i = 0; i < size2; i++)
    {
        data = lista2->info;
        lista2 = stergeInceput(lista2);
        if (!isInList(data, lista3))
        {
            lista3 = adaugaFinal(data, lista3);
        }
    }
    afisare(lista3);
    freeLista(lista1);
    freeLista(lista2);
    freeLista(lista3);
}

// Problema 7.4

nod *sterge4(int info, nod *inceput, nod *final)
{
    nod *aux, *ant;
    if (inceput == NULL)
    {
        return inceput;
    }
    if (inceput->info == info)
    {
        aux = inceput;
        inceput = inceput->next;
        free(aux);
        if (inceput == NULL)
        {
            final = NULL;
        }
    }
    else
    {
        for (ant = inceput, aux = inceput->next; aux != NULL; ant = ant->next, aux = aux->next)
        {
            if (aux->info == info)
            {
                ant->next = aux->next;
                free(aux);
                if (ant->next == NULL)
                {
                    final = ant;
                }
                break;
            }
        }
    }
    return inceput;
}

// Problema 7.5

void p5(void)
{
    nod *lista1, *lista2;
    int size1, size2, i, data;
    lista1 = init(&size1);
    lista2 = init(&size2);
    if (size1 > size2)
    {
        for (i = 0; i < size1; i++)
        {
            data = lista1->info;
            if (!isInList(data, lista2))
            {
                printf("0\n");
                freeLista(lista1);
                freeLista(lista2);
                return;
            }
            lista1 = lista1->next;
        }
    }
    else
    {
        for (i = 0; i < size2; i++)
        {
            data = lista2->info;
            if (!isInList(data, lista1))
            {
                printf("0\n");
                freeLista(lista1);
                freeLista(lista2);
                return;
            }
            lista2 = lista2->next;
        }
    }
    printf("1\n");
    freeLista(lista1);
    freeLista(lista2);
}

// Problema 7.6

nod *inserareCrescatoare(int data, nod *lista)
{
    nod *p, *q, *nouNod;
    nouNod = newNod(data, NULL);
    if (lista == NULL)
    {
        lista = nouNod;
    }
    else
    {
        if (nouNod->info < lista->info)
        {
            adaugaInceput(data, lista);
        }
        else
        {
            if (lista->next == NULL)
            {
                adaugaFinal(data, lista);
            }
            else
            {
                for (p = lista, q = lista->next; q != NULL; p = p->next, q = q->next)
                {
                    if (p->info <= data && data <= q->info)
                    {
                        p->next = nouNod;
                        nouNod->next = q;
                        break;
                    }
                }
            }
        }
    }
    return lista;
}

nod *sortare(nod *lista)
{
    nod *p;
    nod *listaSortata = NULL;
    for (p = lista; p != NULL; p = p->next)
    {
        listaSortata = inserareCrescatoare(p->info, listaSortata);
    }
    return listaSortata;
}

void p6(void)
{
    nod *lista;
    int size;
    lista = init(&size);
    lista = sortare(lista);
    afisare(lista);
    freeLista(lista);
}

// Problema 7.7

void p7(void)
{
    nod *lista1, *lista2, *p;
    int size1, size2;
    lista1 = init(&size1);
    lista2 = init(&size2);
    for (p = lista1; p != NULL; p = p->next)
    {
        adaugaFinal(p->info, lista2);
    }
    lista2 = sortare(lista2);
    afisare(lista2);
    freeLista(lista1);
    freeLista(lista2);
}

int main(void)
{
    if ((file = fopen(path, "r")) == NULL)
    {
        printf("Eroare\n");
        return 0;
    }
    p7();
    if (fclose(file) != 0)
    {
        printf("Eroare\n");
        return 0;
    }
}