#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int findOptimal(int pages[], int frames[], int p, int f, int counter)
{
    int arr[f];
    int i = 0;
    while (i < f)
    {
        int count = 0;
        for (int j = counter; j < p; j++)
        {
            if (frames[i] == pages[j])
            {
                break;
            }
            count++;
        }
        arr[i] = count;
        i++;
    }
    int furthest = INT_MIN;
    int t;
    for (int j = 0; j < f; j++)
    {
        if (furthest < arr[j])
        {
            furthest = arr[j];
            t = j;
        }
    }

    return t;
}

void Optimal(int pages[], int frames[], int p, int f)
{
    int rear = -1;
    int counter = 0;
    int pagehit = 0;
    int pagefault = 0;
    while (counter < p)
    {
        int flag = 0;
        for (int i = 0; i < f; i++)
        {
            if (frames[i] == pages[counter])
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
                int replica = findOptimal(pages, frames, p, f, counter);
                frames[replica] = pages[counter];
            }
        }
        counter++;
    }
    printf("No of pagfaults: %d", pagefault);
}

int main()
{
    int p, f;
    printf("Enter no of pages: ");
    scanf("%d", &p);
    printf("Enter no of frames: ");
    scanf("%d", &f);
    int pages[p];
    int frames[f];
    printf("Enter pages:");
    for (int i = 0; i < p; i++)
    {
        scanf("%d", &pages[i]);
    }
    Optimal(pages, frames, p, f);
    return 0;
}