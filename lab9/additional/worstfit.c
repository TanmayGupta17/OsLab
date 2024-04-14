#include <stdio.h>
#include <stdlib.h>

typedef struct block
{
    int start;
    int size;
    bool occupied;
    struct block *next;
} block;

block *root = NULL;

void insert(int size)
{
    block *ptr = (block *)malloc(sizeof(block));
    ptr->size = size;
    ptr->start = 0;
    ptr->occupied = false;
    if (root == NULL)
    {
        root = ptr;
        return;
    }
    else
    {
        block *temp = root;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = ptr;
        ptr->next = NULL;
    }
}

void worstfit(int size)
{
    block *temp = root;
    block *largesthole;
    largesthole->size = -99999;
    while (temp != NULL)
    {
        if (temp->size > largesthole->size && temp->occupied == false)
        {
            largesthole = temp;
        }
        temp = temp->next;
    }
    if (largesthole->size != 999999)
    {
        printf("Allocated %d bytes at [%d - %d]", size, largesthole->start, largesthole->size);
        largesthole->size -= size;
        largesthole->start += size;
        largesthole->occupied = true;
        return;
    }
    else
    {
        printf("Insufficient space");
    }
}

int main()
{
    int nh;
    printf("Enter no of holes: ");
    scanf("%d", &nh);
    int np;
    printf("Enter no of process: ");
    scanf("%d", &np);
    printf("enter size of blocks: ");
    for (int i = 0; i < nh; i++)
    {
        int size;
        scanf("%d", &size);
        insert(size);
    }
    printf("Enter size of process: ");
    for (int i = 0; i < np; i++)
    {
        int size;
        scanf("%d", &size);
        worstfit(size);
    }
    return 0;
}
