#include <stdio.h>
#include <stdlib.h>

typedef struct block
{
    int start;
    int size;
    struct block *next;
} block;

block *root = NULL;

void insert(int size)
{
    block *ptr = (block *)malloc(sizeof(block));
    block *temp = root;
    ptr->size = size;
    ptr->start = 0;
    if (root == NULL)
    {
        root = ptr;
    }
    else
    {
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        ptr->next = NULL;
        temp->next = ptr;
    }
}

void displayprocess()
{
    block *temp = root;
    while (temp != NULL)
    {
        printf("[%d - %d] %d bytes\n", temp->start, temp->start + temp->size - 1, temp->size);
        temp = temp->next;
    }
    printf("\n");
}

void firstfit(int size)
{
    block *temp = root;
    while (temp != NULL)
    {
        if (temp->size >= size)
        {
            printf("Allocated %d bytes at [%d - %d]\n", size, temp->start, temp->size);
            temp->start += size;
            temp->size -= size;
            return;
        }
        temp = temp->next;
    }
    printf("Insufficient memory for allocation of %d bytes\n", size);
}

void bestfit(int size)
{
    block *temp = root;
    block *best = NULL;
    int minsize = 99999;
    while (temp != NULL)
    {
        if (temp->size >= size && temp->size - size < minsize)
        {
            best = temp;
            minsize = temp->size - size;
        }
        temp = temp->next;
    }
    if (best != NULL)
    {
        printf("Allocated %d bytes at [%d - %d]\n", size, best->start, best->size);
        best->start += size;
        best->size -= size;
        return;
    }
    else
    {
        printf("Insufficient memory for allocation of %d bytes\n", size);
    }
}

int main()
{
    int nh;
    printf("Enter no of holes: ");
    scanf("%d", &nh);
    int np;
    printf("Enter no of processes: ");
    scanf("%d", &np);
    printf("Enter size of holes:\n");
    for (int i = 0; i < nh; i++)
    {
        int size;
        scanf("%d", &size);
        insert(size);
    }
    printf("Enter size of processes:\n");
    for (int i = 0; i < np; i++)
    {
        int size;
        scanf("%d", &size);
        bestfit(size);
    }
}
