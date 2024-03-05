#include <stdio.h>
#include <string.h>

#define SIZE 100

// Problema 3.1

int top = -1, stack[SIZE];

void push(int item)
{
    if (top == SIZE - 1)
    {
        printf("Stiva este plina\n");
        return;
    }
    stack[++top] = item;
}

int pop(void)
{
    if (top == -1)
    {
        printf("Stiva este goala\n");
        return -1;
    }
    return stack[top--];
}

void peek(void)
{
    if (top == -1)
    {
        printf("Stiva este goala\n");
        return;
    }
    printf("%d\n", stack[top]);
}
// Problema 3.2

int front = -1, rear = -1, queue[SIZE];

void enqueue(int item)
{
    if (rear == SIZE - 1)
    {
        printf("Coada este plina\n");
        return;
    }
    if (front == -1)
    {
        front = 0;
    }
    queue[++rear] = item;
}

int dequeue(void)
{
    if (front == -1 || front > rear)
    {
        printf("Coada este goala\n");
        return -1;
    }
    return queue[front++];
}

void qpeek(void)
{
    if (front == -1 || front > rear)
    {
        printf("Coada este goala\n");
    }
    printf("%d\n", queue[front]);
}

// Problema 3.3

char stivaCuvinte[SIZE][100];
int row = -1;

void pushString(char *newString)
{
    if (row == SIZE - 1)
    {
        printf("Stiva este plina.\n");
        return;
    }
    strcpy(stivaCuvinte[++row], newString);
}

char *popString(void)
{
    if (row == -1)
    {
        printf("Stiva este goala.\n");
        return NULL;
    }
    return stivaCuvinte[row--];
}

void p3(void)
{
    char text[SIZE], *buffer;
    int optiune, citiri = 0;
    do
    {
        printf("1 - Citeste text nou\n");
        printf("2 - Salveaza text\n");
        printf("3 - Undo text\n");
        printf("4 - Afiseaza textul actual\n");
        printf("0 - Exit\n");
        printf("Introdu optiunea: ");
        scanf("%d", &optiune);

        switch (optiune)
        {
        case 1:
        {
            getchar();
            if (fgets(text, 100, stdin) == NULL)
            {
                printf("Eroare la citire.\n");
            }
            else
            {
                citiri++;
            }
            break;
        }
        case 2:
        {
            if (citiri == 0)
            {
                printf("Citeste mai intai un text.\n");
                break;
            }
            else
            {
                pushString(text);
            }
            break;
        }
        case 3:
        {
            buffer = popString();
            if (buffer != NULL)
            {
                strcpy(text, buffer);
            }
            break;
        }
        case 4:
        {
            printf("%s", text);
        }
        case 0:
        {
            break;
        }
        default:
        {
            printf("Ai introdus o operatie invalida.\n");
        }
        }
    } while (optiune != 0);
}

// Problema 3.4

char coadaMesaje[SIZE][256];
int fata = -1, spate = -1;

void enqueueMessage(char *mesaj)
{
    if (spate == SIZE - 1)
    {
        printf("Coada este plina\n");
        return;
    }
    if (fata == -1)
    {
        fata = 0;
    }
    strcpy(coadaMesaje[++spate], mesaj);
}

char *dequeueMessage(void)
{
    if (fata == -1 || fata > spate)
    {
        printf("Coada este goala\n");
        return NULL;
    }
    return coadaMesaje[fata++];
}

void p4(void)
{
    char mesaj[256], *buffer;
    int optiune, citiri = 0;
    do
    {
        printf("1 - Citeste mesaj nou\n");
        printf("2 - Salveaza mesaj\n");
        printf("3 - Recupereaza mesaj\n");
        printf("4 - Afiseaza mesaj actual\n");
        printf("0 - Exit\n");
        printf("Introdu optiunea: ");
        scanf("%d", &optiune);

        switch (optiune)
        {
        case 1:
        {
            getchar();
            if (fgets(mesaj, 256, stdin) == NULL)
            {
                printf("Eroare la citire.\n");
            }
            else
            {
                citiri++;
            }
            break;
        }
        case 2:
        {
            if (citiri == 0)
            {
                printf("Citeste mai intai un mesaj.\n");
                break;
            }
            else
            {
                enqueueMessage(mesaj);
            }
            break;
        }
        case 3:
        {
            buffer = dequeueMessage();
            if (buffer != NULL)
            {
                strcpy(mesaj, buffer);
            }
            break;
        }
        case 4:
        {
            printf("%s", mesaj);
        }
        case 0:
        {
            break;
        }
        default:
        {
            printf("Ai introdus o operatie invalida.\n");
        }
        }
    } while (optiune != 0);
}

int main(void)
{
    return 0;
}