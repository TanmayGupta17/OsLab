#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int findLRU(int pages[], int frames[], int p, int f, int counter)
{
    int arr[f];
    int count = 0;
    for (int i = 0; i < f; i++)
    {
        for (int j = counter - 1; j >= 0; j--)
        {
            if (frames[i] == pages[j])
            {
                break;
            }
            count++;
        }
        arr[i] = count;
    }
    int least = INT_MIN;
    int t;
    for (int i = 0; i < f; i++)
    {
        if (least < arr[i])
        {
            least = arr[i];
            t = i;
        }
    }
    return t;
}

void LRU(int pages[], int frames[], int p, int f)
{
    int pagehit = 0;
    int pagefault = 0;
    int counter = 0;
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
            if (counter < f)
            {
                frames[counter] = pages[counter];
            }
            else
            {
                int replica = findLRU(pages, frames, p, f, counter);
                frames[replica] = pages[counter];
            }
        }
        counter++;
    }
    printf("No of pagefaults: %d", pagefault);
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
    printf("Enter pages: ");
    for (int i = 0; i < p; i++)
    {
        scanf("%d", &pages[i]);
    }
    LRU(pages, frames, p, f);
    return 0;
}