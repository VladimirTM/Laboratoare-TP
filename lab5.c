#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// Problema 5.2

void p2(int argc, char **argv)
{
    FILE *src, *dst;
    if ((src = fopen(argv[1], "rb")) == NULL)
    {
        return;
    }
    if ((dst = fopen(argv[2], "wb")) == NULL)
    {
        return;
    }

    uint64_t buffer[512];
    int r;

    while ((r = fread(buffer, sizeof(uint64_t), 512, src)) > 0)
    {
        fwrite(buffer, sizeof(uint64_t), r, dst);
    }

    if (fclose(src) != 0)
    {
        return;
    }
    if (fclose(dst) != 0)
    {
        return;
    }
}

// Problema 5.3

void p3(void)
{
    int m, n;
    scanf("%d %d", &m, &n);
    int **a = NULL;
    if ((a = malloc(m * sizeof(int *))) == NULL)
    {
        return;
    }
    int i, j;
    for (i = 0; i < m; i++)
    {
        if ((a[i] = malloc(n * sizeof(int))) == NULL)
        {
            return;
        }
        for (j = 0; j < n; j++)
        {
            scanf("%d", &a[i][j]);
        }
    }
    FILE *f;
    if ((f = fopen("matrice.txt", "wb")) == NULL)
    {
        return;
    }

    fprintf(f, "%d %d\n", m, n);
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            fprintf(f, "%d ", a[i][j]);
        }
        fprintf(f, "\n");
    }

    for (i = 0; i < m; i++)
    {
        free(a[i]);
    }
    free(a);

    if (fclose(f) != 0)
    {
        return;
    }
}

// Problema 5.4

typedef struct
{
    char *nume;
    float pret;
} Produs;

Produs produse[1000];
int nProduse;

void citire()
{
    FILE *fis;
    unsigned short nNume;

    if ((fis = fopen("produse.dat", "rb")) == NULL)
        return;
    int dimensiune;
    fread(&dimensiune, sizeof(int), 1, fis);
    for (int i = 0; i < dimensiune; i++)
    {
        fread(&nNume, sizeof(unsigned short), 1, fis);
        char *pNume = (char *)malloc((nNume + 1) * sizeof(char));
        fread(pNume, sizeof(char), nNume, fis);
        pNume[nNume] = '\0';
        produse[nProduse].nume = pNume;
        fread(&produse[nProduse].pret, sizeof(float), 1, fis);
        nProduse++;
    }
}

void adaugare()
{
    Produs p;
    char nume[1000];

    printf("nume: ");
    fgets(nume, 1000, stdin);
    nume[strcspn(nume, "\r\n")] = '\0';
    if ((p.nume = (char *)malloc((strlen(nume) + 1) * sizeof(char))) == NULL)
    {
        printf("memorie insuficienta");
        exit(EXIT_FAILURE);
    }
    strcpy(p.nume, nume);
    printf("pret: ");
    scanf("%g", &p.pret);
    produse[nProduse] = p;
    nProduse++;
}

void afisare()
{
    int i;
    for (i = 0; i < nProduse; i++)
    {
        printf("%s: %g\n", produse[i].nume, produse[i].pret);
    }
}

void scriere()
{
    FILE *fis;
    int i;
    unsigned short nNume;

    if ((fis = fopen("produse.dat", "wb")) == NULL)
    {
        printf("nu se poate deschide fisierul\n");
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < nProduse; i++)
    {
        nNume = (unsigned short)strlen(produse[i].nume);
        fwrite(&nNume, sizeof(unsigned short), 1, fis);
        fwrite(produse[i].nume, sizeof(char), nNume, fis);
        fwrite(&produse[i].pret, sizeof(float), 1, fis);
    }

    fclose(fis);
}

void eliberare()
{
    int i;
    for (i = 0; i < nProduse; i++)
        free(produse[i].nume);
}

void p4(void)
{
    int optiune;
    citire();
    do
    {
        printf("optiune: ");
        scanf("%d", &optiune);
        getchar();
        switch (optiune)
        {
        case 1:
            adaugare();
            break;
        case 2:
            afisare();
            break;
        case 3:
            scriere();
            eliberare();
            break;
        default:
            printf("optiune invalida\n");
        }
    } while (optiune != 3);
}

// Problema 5.5

void p5(int argc, char **argv)
{
    FILE *f;
    if ((f = fopen(argv[1], "rb")) == NULL)
    {
        return;
    }

    int buffer[16], r, offset = 0;

    while ((r = fread(buffer, sizeof(int), 16, f)) > 0)
    {
        printf("%08x ", offset);
        for (int i = 0; i < 16; i++)
        {
            if (i < r)
            {
                printf("%02X ", buffer[i]);
            }
            else
            {
                printf("%02X ", 0);
            }
        }
        for (int i = 0; i < 16; i++)
        {
            if (i < r)
            {
                if (buffer[i] >= 32 && buffer[i] <= 255)
                {
                    printf("%c", buffer[i]);
                }
                else
                {
                    printf(".");
                }
            }
            else
            {
                printf(".");
            }
        }
        printf("\n");
        offset += 16;
    }

    if (fclose(f) != 0)
    {
        return;
    }
}

// Problema 5.6

void p6(int argc, char **argv)
{
    FILE *f1, *f2;
    if ((f1 = fopen(argv[1], "rb")) == NULL)
    {
        return;
    }
    if ((f2 = fopen(argv[2], "rb")) == NULL)
    {
        return;
    }

    int offset = 0;
    int byte1, byte2;

    for (;;)
    {
        byte1 = fgetc(f1);
        byte2 = fgetc(f2);

        if (byte1 == EOF || byte2 == EOF)
        {
            break;
        }

        if (byte1 != byte2)
        {
            printf("Offset: %02X\n", offset);
            printf("File 1: %02X\n", byte1);
            printf("File 2: %02X\n", byte2);
        }

        offset++;
    }

    if (byte1 == EOF)
    {
        while (byte2 != EOF)
        {
            printf("%02X ", byte2);
            byte2 = fgetc(f2);
        }
    }
    else
    {
        while (byte1 != EOF)
        {
            printf("%02X ", byte1);
            byte1 = fgetc(f1);
        }
    }

    fclose(f1);
    fclose(f2);
    printf("\n");
}

// Problema 5.7

void p7(int argc, char **argv)
{
    FILE *f;
    if ((f = fopen(argv[1], "ab")) == NULL)
    {
        return;
    }

    int offset = strtol(argv[2], NULL, 16);
    fseek(f, offset, SEEK_SET);
    for (int i = 3; i < argc; i++)
    {
        fputc(strtol(argv[i], NULL, 16), f);
    }

    if (fclose(f) != 0)
    {
        return;
    }
}

// Problema 5.8

void p8(int argc, char **argv)
{
    FILE *f;
    if ((f = fopen(argv[1], "rb")) == NULL)
    {
        return;
    }

    int r, offset = 0;
    char byte;
    while ((r = fread(&byte, sizeof(char), 1, f)) > 0)
    {
        for (int i = 2; i < argc; i++)
        {
            if (byte == strtol(argv[i], NULL, 16))
            {
                printf("Offset: %02X\n", offset);
            }
        }
        offset++;
    }

    if (fclose(f) != 0)
    {
        return;
    }
}

// Problema 5.9

void p9(int argc, char **argv)
{
    for (int i = 1; i < argc - 1; i++)
    {
        p2(2, (char *[]){argv[0], argv[i], argv[argc - 1]});
    }
}

int main(int argc, char **argv)
{
    return 0;
}