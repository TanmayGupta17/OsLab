#include <stdio.h>
#include <stdlib.h>

void FIFO(int pages[], int frames[], int p, int f)
{
    int rear = -1;
    int front = -1;
    int pagehit = 0;
    int pagefault = 0;
    int counter = 0;
    while (counter < p)
    {
        int flag = 0;
        for (int i = 0; i < f; i++)
        {
            if (pages[counter] == frames[i])
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
                frames[++rear] = pages[counter];
            }
            else
            {
                front = (front + 1) % f;
                frames[front] = pages[counter];
            }
        }
        counter++;
    }
    printf("No of pagefaults: %d", pagefault);
}

int main()
{
    int f, p;
    printf("Enter no of pages: ");
    scanf("%d", &p);
    printf("Enter no of frames: ");
    scanf("%d", &f);
    int pages[p];
    int frames[f];
    printf("Enter page: ");
    for (int i = 0; i < p; i++)
    {
        scanf("%d", &pages[i]);
    }
    FIFO(pages, frames, p, f);
}