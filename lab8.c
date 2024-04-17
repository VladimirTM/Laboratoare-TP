#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Problema 8.1 si 8.2

typedef struct Cuvant
{
    char text[16];
    int count;
    struct Cuvant *pred;
    struct Cuvant *urm;
} Cuvant;

Cuvant *Cuvant_nou(const char *text)
{
    Cuvant *c = (Cuvant *)malloc(sizeof(Cuvant));
    if (!c)
    {
        printf("memorie insuficienta");
        exit(EXIT_FAILURE);
    }
    strcpy(c->text, text);
    c->count = 1;
    return c;
}

typedef struct
{
    Cuvant *prim;
    Cuvant *ultim;
} Propozitie;

void Propozitie_init(Propozitie *p)
{
    p->prim = p->ultim = NULL;
}

Cuvant *Propozitie_cauta(Propozitie *p, const char *text)
{
    Cuvant *c;
    for (c = p->prim; c; c = c->urm)
    {
        if (!strcmp(c->text, text))
            return c;
    }
    return NULL;
}

void Propozitie_adauga(Propozitie *p, Cuvant *c)
{
    Cuvant *exista = Propozitie_cauta(p, c->text);
    if (exista)
    {
        exista->count++;
        free(c);
    }
    else
    {
        c->pred = p->ultim;
        if (p->ultim)
        {
            p->ultim->urm = c;
        }
        else
        {
            p->prim = c;
        }
        p->ultim = c;
        c->urm = NULL;
    }
}

void Propozitie_sterge(Propozitie *p, Cuvant *c)
{
    if (c->pred)
    {
        c->pred->urm = c->urm;
    }
    else
    {
        p->prim = c->urm;
    }
    if (c->urm)
    {
        c->urm->pred = c->pred;
    }
    else
    {
        p->ultim = c->pred;
    }
    free(c);
}

void Propozitie_elibereaza(Propozitie *p)
{
    Cuvant *c, *urm;
    for (c = p->prim; c; c = urm)
    {
        urm = c->urm;
        free(c);
    }
    Propozitie_init(p);
}

void Propozitie_inserare(Propozitie *p, const char *cuvant_inserat, const char *cuvant_succesor)
{
    Cuvant *inserat = Cuvant_nou(cuvant_inserat);
    Cuvant *succesor = Propozitie_cauta(p, cuvant_succesor);

    if (succesor)
    {
        inserat->pred = succesor->pred;
        inserat->urm = succesor;
        if (succesor->pred)
        {
            succesor->pred->urm = inserat;
        }
        else
        {
            p->prim = inserat;
        }
        succesor->pred = inserat;
    }
    else
    {
        Propozitie_adauga(p, inserat);
    }
}

// Problema 8.3

typedef struct nod
{
    char info[1000];
    struct nod *ant, *urm;
} Nod;

Nod *nouNod(const char *info)
{
    Nod *nouNod = NULL;
    if ((nouNod = (Nod *)malloc(sizeof(Nod))) == NULL)
    {
        printf("Memorie insuficienta");
        exit(EXIT_FAILURE);
    }
    strcpy(nouNod->info, info);
    nouNod->ant = NULL;
    nouNod->urm = NULL;
    return nouNod;
}

Nod *adaugaNod(Nod *lista, const char *info)
{
    Nod *nou = nouNod(info);
    if (lista == NULL)
    {
        return nou;
    }
    else if (strcmp(info, lista->info) < 0)
    {
        nou->urm = lista;
        lista->ant = nou;
        return nou;
    }
    else
    {
        Nod *curent = lista;
        while (curent->urm != NULL && strcmp(info, curent->urm->info) > 0)
        {
            curent = curent->urm;
        }
        nou->urm = curent->urm;
        if (curent->urm != NULL)
        {
            curent->urm->ant = nou;
        }
        curent->urm = nou;
        nou->ant = curent;
        return lista;
    }
}

void afisareLista(Nod *lista)
{
    Nod *curent = lista;
    while (curent != NULL)
    {
        printf("%s\n", curent->info);
        curent = curent->urm;
    }
}

void freeLista(Nod *lista)
{
    Nod *curent = lista;
    Nod *urm = NULL;
    while (curent != NULL)
    {
        urm = curent->urm;
        free(curent);
        curent = urm;
    }
}

void p3(int argc, char **argv)
{
    FILE *fisier = NULL;
    Nod *lista = NULL;
    char buffer[1000];
    if (argc < 2)
    {
        exit(EXIT_FAILURE);
    }
    if ((fisier = fopen(argv[1], "r")) == NULL)
    {
        printf("Eroare la deschiderea fisierului");
        exit(EXIT_FAILURE);
    }

    while (fgets(buffer, 1000, fisier) != NULL)
    {
        lista = adaugaNod(lista, buffer);
    }

    afisareLista(lista);

    freeLista(lista);

    fclose(fisier);
}

// Problema 8.4

typedef struct produs
{
    char nume[50];
    int pret;
    struct produs *anterior, *urmator;
} Produs;

typedef struct categorie
{
    char nume[50];
    Produs *listaDeProduse;
    struct categorie *anterior, *urmator;
} Categorie;

Categorie *newCategorie(const char *nume)
{
    Categorie *nou = NULL;
    if ((nou = malloc(1 * sizeof(Categorie))) == NULL)
    {
        exit(EXIT_FAILURE);
    }
    strcpy(nou->nume, nume);
    nou->anterior = NULL;
    nou->urmator = NULL;
    nou->listaDeProduse = NULL;
    return nou;
}

Categorie *adaugaCategorie(const char *nume, Categorie *listaDeCategorii)
{
    Categorie *nouaCategorie = newCategorie(nume), *aux;
    if (listaDeCategorii == NULL)
    {
        listaDeCategorii = nouaCategorie;
    }
    else
    {
        for (aux = listaDeCategorii; aux->urmator != NULL; aux = aux->urmator)
            ;
        aux->urmator = nouaCategorie;
        nouaCategorie->anterior = aux;
    }
    return listaDeCategorii;
}

Categorie *cautaCategorie(const char *nume, Categorie *listaDeCategorii)
{
    Categorie *aux;
    for (aux = listaDeCategorii; aux != NULL; aux = aux->urmator)
    {
        if (strcmp(nume, aux->nume) == 0)
        {
            return aux;
        }
    }
    return NULL;
}

void afisareCategorii(Categorie *listaDeCategorii)
{
    Categorie *aux;
    for (aux = listaDeCategorii; aux != NULL; aux = aux->urmator)
    {
        printf("%s\n", aux->nume);
    }
}

Produs *newProdus(const char *nume, int pret)
{
    Produs *nou = NULL;
    if ((nou = malloc(1 * sizeof(Produs))) == NULL)
    {
        exit(EXIT_FAILURE);
    }
    strcpy(nou->nume, nume);
    nou->pret = pret;
    nou->anterior = NULL;
    nou->urmator = NULL;
    return nou;
}

Categorie *adaugaProdus(const char *numeProdus, int pret, const char *numeCategorie, Categorie *listaDeCategorii)
{
    Produs *nouProdus = newProdus(numeProdus, pret), *aux;
    Categorie *categorieCautata = NULL;
    categorieCautata = cautaCategorie(numeCategorie, listaDeCategorii);
    if (categorieCautata->listaDeProduse == NULL)
    {
        categorieCautata->listaDeProduse = nouProdus;
    }
    else
    {
        for (aux = categorieCautata->listaDeProduse; aux->urmator != NULL; aux = aux->urmator)
            ;
        aux->urmator = nouProdus;
        nouProdus->anterior = aux;
    }
    return listaDeCategorii;
}

void afisareProduse(const char *nume, Categorie *listaDeCategorii)
{
    Categorie *auxC;
    Produs *auxP;
    auxC = cautaCategorie(nume, listaDeCategorii);
    if (auxC != NULL)
    {
        for (auxP = auxC->listaDeProduse; auxP != NULL; auxP = auxP->urmator)
        {
            printf("%s costa %d\n", auxP->nume, auxP->pret);
        }
    }
}

void freeProduse(Produs *listaDeProduse)
{
    Produs *curent = listaDeProduse;
    Produs *urm = NULL;
    while (curent != NULL)
    {
        urm = curent->urmator;
        free(curent);
        curent = urm;
    }
}

void freeCategorii(Categorie *listaDeCategorii)
{
    Categorie *curent = listaDeCategorii;
    Categorie *urmator = NULL;
    while (curent != NULL)
    {
        freeProduse(curent->listaDeProduse);
        urmator = curent->urmator;
        free(curent);
        curent = urmator;
    }
}

void p4(void)
{
    int optiune, pret;
    char numeCategorie[50], numeProdus[50];
    Categorie *listaDeCategorii = NULL;
    do
    {
        scanf("%d", &optiune);
        switch (optiune)
        {
        case 1:
        {
            scanf("%49s", numeCategorie);
            listaDeCategorii = adaugaCategorie(numeCategorie, listaDeCategorii);
            break;
        }
        case 2:
        {
            scanf("%49s", numeCategorie);
            scanf("%49s", numeProdus);
            scanf("%d", &pret);
            listaDeCategorii = adaugaProdus(numeProdus, pret, numeCategorie, listaDeCategorii);
            break;
        }
        case 3:
        {
            afisareCategorii(listaDeCategorii);
            break;
        }
        case 4:
        {
            scanf("%49s", numeCategorie);
            afisareProduse(numeCategorie, listaDeCategorii);
            break;
        }
        case 5:
        {
            freeCategorii(listaDeCategorii);
            break;
        }
        }
    } while (optiune != 5);
}

// Problema 8.5

typedef struct automobil
{
    unsigned int codMasina : 14;
    unsigned int numarLocuri : 4;
    unsigned int putere : 9;
    char marca[50];
    char culoare[50];
    unsigned int anulFabricatiei : 11;
    struct automobil *anterior;
    struct automobil *urmator;
} Automobil;

Automobil *adaugaAutomobil(unsigned int codMasina, unsigned int numarLocuri, unsigned int putere, const char *marca, const char *culoare, unsigned int anulFabricatiei, Automobil *listaDeMasini)
{
    Automobil *nou = NULL;
    if ((nou = malloc(1 * sizeof(Automobil))) == NULL)
    {
        exit(EXIT_FAILURE);
    }
    nou->codMasina = codMasina;
    nou->numarLocuri = numarLocuri;
    nou->putere = putere;
    strcpy(nou->marca, marca);
    strcpy(nou->culoare, culoare);
    nou->anulFabricatiei = anulFabricatiei;
    nou->anterior = NULL;
    nou->urmator = NULL;
    if (listaDeMasini == NULL)
    {
        return nou;
    }
    else
    {
        nou->urmator = listaDeMasini;
        listaDeMasini->anterior = nou;
    }
    return nou;
}

Automobil *stergeAutomobil(unsigned int codMasina, Automobil *listaDeMasini)
{
    Automobil *aux = listaDeMasini;
    while (aux != NULL && aux->codMasina != codMasina)
    {
        aux = aux->urmator;
    }
    if (aux == NULL)
    {
        return listaDeMasini;
    }
    if (aux->anterior != NULL)
    {
        aux->anterior->urmator = aux->urmator;
    }
    if (aux->urmator != NULL)
    {
        aux->urmator->anterior = aux->anterior;
    }
    if (aux == listaDeMasini)
    {
        listaDeMasini = aux->urmator;
    }
    free(aux);
    return listaDeMasini;
}

void afisareAutomobile(Automobil *listaDeAutomobile)
{
    Automobil *aux;
    for (aux = listaDeAutomobile; aux != NULL; aux = aux->urmator)
    {
        printf("Cod masina: %d\n", aux->codMasina);
        printf("Numar locuri: %d\n", aux->numarLocuri);
        printf("Putere: %d\n", aux->putere);
        printf("Marca: %s\n", aux->marca);
        printf("Culoare: %s\n", aux->culoare);
        printf("Anul fabricatiei: %d\n", aux->anulFabricatiei);
    }
}

void afisareAutomobileNumarLocuri(int numarLocuriCautate, Automobil *listaDeAutomobile)
{
    Automobil *aux;
    for (aux = listaDeAutomobile; aux != NULL; aux = aux->urmator)
    {
        if (aux->numarLocuri == numarLocuriCautate)
        {
            printf("Cod masina: %d\n", aux->codMasina);
            printf("Numar locuri: %d\n", aux->numarLocuri);
            printf("Putere: %d\n", aux->putere);
            printf("Marca: %s\n", aux->marca);
            printf("Culoare: %s\n", aux->culoare);
            printf("Anul fabricatiei: %d\n", aux->anulFabricatiei);
        }
    }
}

Automobil *sortareAnFabricatie(Automobil *listaDeAutomobile)
{
    Automobil *aux, *aux2;
    for (aux = listaDeAutomobile; aux != NULL; aux = aux->urmator)
    {
        for (aux2 = aux->urmator; aux2 != NULL; aux2 = aux2->urmator)
        {
            if (aux->anulFabricatiei > aux2->anulFabricatiei)
            {
                Automobil temp = *aux;
                *aux = *aux2;
                *aux2 = temp;
            }
        }
    }
    return listaDeAutomobile;
}

void freeAutomobile(Automobil *listaDeAutomobile)
{
    Automobil *curent = listaDeAutomobile;
    Automobil *urm = NULL;
    while (curent != NULL)
    {
        urm = curent->urmator;
        free(curent);
        curent = urm;
    }
}

void p5(void)
{
    int optiune;
    unsigned int codMasina, numarLocuri, putere, anulFabricatiei;
    char marca[50], culoare[50];
    Automobil *listaDeAutomobile = NULL;
    do
    {
        scanf("%d", &optiune);
        switch (optiune)
        {
        case 1:
        {
            scanf("%d", &codMasina);
            scanf("%d", &numarLocuri);
            scanf("%d", &putere);
            scanf("%49s", marca);
            scanf("%49s", culoare);
            scanf("%d", &anulFabricatiei);
            listaDeAutomobile = adaugaAutomobil(codMasina, numarLocuri, putere, marca, culoare, anulFabricatiei, listaDeAutomobile);
            break;
        }
        case 2:
        {
            scanf("%d", &codMasina);
            listaDeAutomobile = stergeAutomobil(codMasina, listaDeAutomobile);
            break;
        }
        case 3:
        {
            afisareAutomobile(listaDeAutomobile);
            break;
        }
        case 4:
        {
            scanf("%d", &numarLocuri);
            afisareAutomobileNumarLocuri(numarLocuri, listaDeAutomobile);
            break;
        }
        case 5:
        {
            listaDeAutomobile = sortareAnFabricatie(listaDeAutomobile);
            break;
        }
        case 6:
        {
            freeAutomobile(listaDeAutomobile);
            break;
        }
        }
    } while (optiune != 6);
}

int main(int argc, char **argv)
{
    p5();
    return 0;
}