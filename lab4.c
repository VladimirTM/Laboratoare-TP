#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define n 100

// Problema 4.0

typedef struct
{
    char nume[21];
    float nota;
} Student;

void readStudent(Student *s)
{
    scanf("%20s", s->nume);
    scanf("%f", &s->nota);
}

void printStudent(Student *s)
{
    printf("Elevul %s are nota %.2f\n", s->nume, s->nota);
}

void p0(void)
{
    Student s1;
    readStudent(&s1);
    printStudent(&s1);
}

// Problema 4.1

typedef struct
{
    char nume[16];
    unsigned int dimensiune : 11;
    unsigned int tip_document : 2;
    unsigned int tip_fisier : 1;
} Fisier;

int readFisier(Fisier *f)
{
    if (scanf("%15s", f->nume) != 1)
    {
        return 0;
    }
    unsigned int aux;
    if (scanf("%d", &aux) != 1)
    {
        return 0;
    }
    f->dimensiune = aux;
    if (scanf("%d", &aux) != 1)
    {
        return 0;
    }
    f->tip_document = aux;
    if (scanf("%d", &aux) != 1)
    {
        return 0;
    }
    f->tip_fisier = aux;
    return 1;
}

void fprintFisier(Fisier *f, FILE *file)
{
    fprintf(file, "Fisierul %s, de dimensiune %d, cu extensia %s, in modul %s.\n", f->nume, f->dimensiune, f->tip_document == 0 ? ".txt" : (f->tip_document == 1 ? ".doc" : ".xls"), f->tip_fisier == 0 ? "normal" : "read-only");
}

void p1(void)
{
    Fisier f1;
    if (readFisier(&f1))
    {
        fprintFisier(&f1, stdout);
    }
}

// Problema 4.2

void p2(void)
{
    Fisier fisiere[11];
    FILE *f;
    int i, j;
    if ((f = fopen("memorie.txt", "w")) == NULL)
    {
        return;
    }
    for (i = 0; i < 11; i++)
    {
        if (readFisier(&fisiere[i]) == 0)
        {
            break;
        }
    }
    for (j = 0; j < i; j++)
    {
        fprintFisier(&fisiere[j], f);
    }
    if (fclose(f) != 0)
    {
        return;
    }
}

// Problema 4.3

void p3(void)
{
    Fisier *fisiere = NULL, fisier;
    FILE *f;
    int i = 0, size = 0, j;
    if ((f = fopen("memorie.txt", "w")) == NULL)
    {
        return;
    }
    while (readFisier(&fisier) != 0)
    {
        if (i == size)
        {
            size += 10;
            if ((fisiere = (Fisier *)realloc(fisiere, size * sizeof(Fisier))) == NULL)
            {
                return;
            }
        }
        fisiere[i++] = fisier;
    }
    for (j = 0; j < i; j++)
    {
        fprintFisier(&fisiere[j], f);
    }
    free(fisiere);
    if (fclose(f) != 0)
    {
        return;
    }
}

// Problema 4.4

typedef struct
{
    unsigned int numar_picioare : 10;
    unsigned int periculos : 1;
    char abreviere[9];
    unsigned int varsta : 11;
    float greutate;
} Animal;

void readAnimal(Animal *a)
{
    unsigned int aux;
    scanf("%d", &aux);
    a->numar_picioare = aux;
    float auxf;
    scanf("%f", &auxf);
    a->greutate = auxf / 1000;
    scanf("%d", &aux);
    a->periculos = aux;
    scanf("%8s", a->abreviere);
    scanf("%d", &aux);
    a->varsta = aux;
}

void printAnimal(Animal *a)
{
    printf("Animalul %s are %d picioare, %.2f kg, %d ani si este %s.\n", a->abreviere, a->numar_picioare, a->greutate, a->varsta, a->periculos == 0 ? "nepericulos" : "periculos");
}

void p4(void)
{
    Animal a1;
    readAnimal(&a1);
    printAnimal(&a1);
}

// Problema 4.5

typedef struct
{
    unsigned int periculos : 2;
    unsigned int reteta : 1;
    unsigned int varsta : 5;
} Medicament;

void readMedicament(Medicament *m)
{
    int aux;
    scanf("%d", &aux);
    m->periculos = aux;
    scanf("%d", &aux);
    m->reteta = aux;
    scanf("%d", &aux);
    m->varsta = aux;
}

void printMedicament(Medicament *m)
{
    printf("Medicamentul este %s, %s, recomandat la %d ani.\n", m->periculos == 0 ? "nepericulos" : (m->periculos == 1 ? "periculos" : "foarte periculos"), m->reteta == 0 ? "fara reteta" : "cu reteta", m->varsta);
}

void p5(void)
{
    Medicament m1;
    readMedicament(&m1);
    printMedicament(&m1);
}

// Problema 4.6

typedef struct
{
    unsigned char unitate_de_masura : 2;
    char multiplicator : 5;
    unsigned long int valoare;
} Masuratoare;

int readMasuratoare(Masuratoare *m)
{
    float aux;
    scanf("%f", &aux);
    m->unitate_de_masura = aux;
    m->multiplicator = 0;
    scanf("%f", &aux);
    if ((aux - (long int)(aux) != (float)0))
    {
        while ((aux - (long int)(aux) != (float)0))
        {
            m->multiplicator++;
            aux *= 10;
        }
        if (aux > 9223372036854775807)
        {
            printf("Valoarea introdusa este prea mare.\n");
            return 0;
        }
        else
        {
            m->valoare = aux;
        }
    }
    else
    {
        if (aux <= 9)
        {
            m->valoare = aux;
        }
        else
        {
            while (aux > 9 && m->multiplicator > -13)
            {
                if ((aux / 10 - (long int)(aux / 10) != (float)0))
                {
                    break;
                }
                m->multiplicator--;
                aux /= 10;
            }
            if (aux > 9223372036854775807)
            {
                printf("Valoarea introdusa este prea mare.\n");
                return 0;
            }
            else
            {
                m->valoare = aux;
            }
        }
    }
    return 1;
}

void printMasuratoare(Masuratoare *m)
{
    printf("Masuratoarea este %ld ", m->valoare);
    switch (m->multiplicator)
    {
    case -12:
        printf("pico");
        break;
    case -9:
        printf("nano");
        break;
    case -3:
        printf("mili");
        break;
    case -2:
        printf("centi");
        break;
    case -1:
        printf("deci");
        break;
    case 0:
        break;
    case 1:
        printf("deca");
        break;
    case 2:
        printf("hecto");
        break;
    case 3:
        printf("kilo");
        break;
    case 6:
        printf("mega");
        break;
    case 9:
        printf("giga");
        break;
    default:
        printf("10^%d", m->multiplicator);
        break;
    }
    printf("%s\n", m->unitate_de_masura == 0 ? "gram" : (m->unitate_de_masura == 1 ? "metru" : "litru"));
}

void p6(void)
{
    Masuratoare m1;
    if (readMasuratoare(&m1) == 1)
    {
        printMasuratoare(&m1);
    }
}

// Problema 4.7

typedef struct
{
    unsigned int cod : 14;
    unsigned int nr_locuri : 4;
    unsigned int putere : 9;
    char marca[50];
    char culoare[10];
    unsigned int an_fabricatie : 11;
} Automobil;

void addAutomobil(Automobil *a, int *i)
{
    unsigned int aux;
    scanf("%d", &aux);
    a[*i].cod = aux;
    scanf("%d", &aux);
    a[*i].nr_locuri = aux;
    scanf("%d", &aux);
    a[*i].putere = aux;
    scanf("%49s", a[*i].marca);
    scanf("%9s", a[*i].culoare);
    scanf("%d", &aux);
    a[*i].an_fabricatie = aux;
    (*i)++;
}

void deleteAutomobil(Automobil *a, int *i, int cod)
{
    int j, k;
    for (j = 0; j < *i; j++)
    {
        if (a[j].cod == cod)
        {
            for (k = j; k < *i - 1; k++)
            {
                a[k] = a[k + 1];
            }
            (*i)--;
            j--;
        }
    }
}

void printAutomobil(Automobil *a, int i)
{
    int j;
    for (j = 0; j < i; j++)
    {
        printf("Automobilul %s, de culoare %s, cu codul %d, are %d locuri, %d cai putere si a fost fabricat in anul %d.\n", a[j].marca, a[j].culoare, a[j].cod, a[j].nr_locuri, a[j].putere, a[j].an_fabricatie);
    }
}

void printAutomobilLocuri(Automobil *a, int i, int nr_locuri)
{
    int j;
    for (j = 0; j < i; j++)
    {
        if (a[j].cod == nr_locuri)
        {
            printf("Automobilul %s, de culoare %s, cu codul %d, are %d locuri, %d cai putere si a fost fabricat in anul %d.\n", a[j].marca, a[j].culoare, a[j].cod, a[j].nr_locuri, a[j].putere, a[j].an_fabricatie);
        }
    }
}

int sort(const void *a, const void *b)
{
    return ((Automobil *)a)->an_fabricatie - ((Automobil *)b)->an_fabricatie;
}

void p7(void)
{
    Automobil automobile[n];
    int optiune, i = 0;
    do
    {
        printf("1. Adauga automobil\n2. Sterge automobil\n3. Afiseaza automobile\n4. Afiseaza automobile cu un anumit numar de locuri\n5. Sorteaza automobilele\n0. Iesire\n");
        scanf("%d", &optiune);
        switch (optiune)
        {
        case 1:
        {
            addAutomobil(automobile, &i);
            break;
        }
        case 2:
        {
            int cod;
            scanf("%d", &cod);
            deleteAutomobil(automobile, &i, cod);
            break;
        }
        case 3:
        {
            printAutomobil(automobile, i);
            break;
        }
        case 4:
        {
            int nr_locuri;
            scanf("%d", &nr_locuri);
            printAutomobilLocuri(automobile, i, nr_locuri);
            break;
        }
        case 5:
        {
            qsort(automobile, i, sizeof(Automobil), sort);
            break;
        }
        }
    } while (optiune != 0);
}

// Problema 4.8

typedef union
{
    char ISBN[14];
    unsigned int an_aparitie;
} Caracteristica;

typedef struct
{
    char titlu[50];
    char autor[50];
    unsigned int numar_exemplare;
    unsigned int pret : 9;
    unsigned int numar_pagini : 10;
    unsigned int greutate : 13;
    unsigned int tip : 1;
    Caracteristica caracteristica;
} Produs;

void addProdus(Produs *p, int *i)
{
    unsigned int aux;
    scanf("%49s", p[*i].titlu);
    scanf("%49s", p[*i].autor);
    scanf("%d", &aux);
    p[*i].numar_exemplare = aux;
    scanf("%d", &aux);
    p[*i].pret = aux;
    scanf("%d", &aux);
    p[*i].numar_pagini = aux;
    scanf("%d", &aux);
    p[*i].greutate = aux;
    scanf("%d", &aux);
    p[*i].tip = aux;
    if (p[*i].tip == 0)
    {
        scanf("%13s", p[*i].caracteristica.ISBN);
    }
    else
    {
        scanf("%d", &aux);
        p[*i].caracteristica.an_aparitie = aux;
    }
    (*i)++;
}

void printCarti(Produs *p, int i)
{
    int j;
    for (j = 0; j < i; j++)
    {
        if (p[j].tip == 0 && p[j].pret > 100)
        {
            printf("Cartea %s, scrisa de %s, costa %d lei, are %d pagini, cantareste %d grame, are %d exemplare si ISBN-ul %s.\n", p[j].titlu, p[j].autor, p[j].pret, p[j].numar_pagini, p[j].greutate, p[j].numar_exemplare, p[j].caracteristica.ISBN);
        }
    }
}

void printProduse(Produs *p, int i)
{
    int j;
    for (j = 0; j < i; j++)
    {
        if (p[j].tip == 0)
        {
            printf("Cartea %s, scrisa de %s, costa %d lei, are %d pagini, cantareste %d grame, are %d exemplare si ISBN-ul %s.\n", p[j].titlu, p[j].autor, p[j].pret, p[j].numar_pagini, p[j].greutate, p[j].numar_exemplare, p[j].caracteristica.ISBN);
        }
        else
        {
            printf("Revista %s, scrisa de %s, costa %d lei, are %d pagini, cantareste %d grame, are %d exemplare si a aparut in anul %d.\n", p[j].titlu, p[j].autor, p[j].pret, p[j].numar_pagini, p[j].greutate, p[j].numar_exemplare, p[j].caracteristica.an_aparitie);
        }
    }
}

void saveProduse(Produs *p, int i)
{
    FILE *f;
    int j;
    if ((f = fopen("inventar.bin", "wb")) == NULL)
    {
        return;
    }
    for (j = 0; j < i; j++)
    {
        fwrite(&p[j], sizeof(Produs), 1, f);
    }
    if (fclose(f) != 0)
    {
        return;
    }
}

void p8(void)
{
    Produs produse[n];
    int optiune, i = 0;
    do
    {
        printf("1. Adauga produs\n2. Afiseaza cartile care costa peste 100 lei\n3. Afiseaza produsele\n4. Salveaza produsele\n0. Iesire\n");
        scanf("%d", &optiune);
        switch (optiune)
        {
        case 1:
        {
            addProdus(produse, &i);
            break;
        }
        case 2:
        {
            printCarti(produse, i);
            break;
        }
        case 3:
        {
            printProduse(produse, i);
            break;
        }
        case 4:
        {
            saveProduse(produse, i);
            break;
        }
        }
    } while (optiune != 0);
}

int main(void)
{
    return 0;
}