#include <stdio.h>
#include <stdlib.h>

int findNextUse(int page[], int p, int currentPos);
int findOptimal(int page[], int f, int p, int frame[], int nextUse[], int currentPos);

void FIFO(int page[], int f, int p)
{
    int front = -1;
    int rear = -1;
    int pagefault = 0;
    int pagehit = 0;
    int frame[f];

    for (int i = 0; i < p; i++)
    {
        int flag = 0;
        for (int j = 0; j <= rear; j++)
        {
            if (page[i] == frame[j])
            {
                pagehit++;
                flag = 1;
                break;
            }
        }
        if (flag == 0)
        {
            pagefault++;
            if (rear < f - 1)
            {
                rear++;
                frame[rear] = page[i];
            }
            else
            {
                front++;
                if (front == f)
                    front = 0;
                frame[front] = page[i];
            }
        }
    }
    printf("Number of page faults is: %d\n", pagefault);
}
void Optimal(int page[], int f, int p)
{
    int pagefault = 0;
    int pagehit = 0;
    int frame[f];
    int nextUse[f];
    int position = 0;

    for (int i = 0; i < f; i++)
    {
        frame[i] = -1;
        nextUse[i] = p;
    }

    for (int i = 0; i < p; i++)
    {
        int flag = 0;
        for (int j = 0; j < f; j++)
        {
            if (page[i] == frame[j])
            {
                pagehit++;
                flag = 1;
                break;
            }
        }
        if (flag == 0)
        {
            pagefault++;
            if (position < f)
            {
                frame[position] = page[i];
                nextUse[position] = findNextUse(page, p, i);
                position++;
            }
            else
            {
                int index = findOptimal(page, f, p, frame, nextUse, i);
                frame[index] = page[i];
                nextUse[index] = findNextUse(page, p, i);
            }
        }
    }
    printf("Number of page faults is: %d\n", pagefault);
}

int findNextUse(int page[], int p, int currentPos)
{
    for (int i = currentPos + 1; i < p; i++)
    {
        for (int j = i + 1; j < p; j++)
        {
            if (page[i] == page[j])
                return j;
        }
    }
    return p;
}

int findOptimal(int page[], int f, int p, int frame[], int nextUse[], int currentPos)
{
    int index = 0;
    int max = -1;
    for (int i = 0; i < f; i++)
    {
        int found = 0;
        for (int j = currentPos + 1; j < nextUse[frame[i]]; j++)
        {
            if (frame[i] == page[j])
            {
                found = 1;
                if (j > max)
                {
                    max = j;
                    index = i;
                }
                break;
            }
        }
        if (!found)
            return i;
    }
    return index;
}

int main()
{
    int f;
    printf("Enter number of frames: ");
    scanf("%d", &f);
    int p;
    printf("Enter number of pages: ");
    scanf("%d", &p);
    int pages[p];
    printf("Enter pages: ");
    for (int i = 0; i < p; i++)
    {
        scanf("%d", &pages[i]);
    }
    Optimal(pages, f, p);
    return 0;
}
