#include <stdio.h>
#include <stdlib.h>

typedef struct PageFrame
{
    int pageNum;
    int timeStamp;
} PageFrame;

int findLRUPage(PageFrame *frames, int numFrames)
{
    int minValue = frames[0].timeStamp;
    int minIndex = 0;
    for (int i = 1; i < numFrames; i++)
    {
        if (frames[i].timeStamp < minValue)
        {
            minValue = frames[i].timeStamp;
            minIndex = i;
        }
    }
    return minIndex;
}

int main()
{
    int numFrames, numPages;

    printf("Enter the number of frames: ");
    scanf("%d", &numFrames);

    printf("Enter the number of pages: ");
    scanf("%d", &numPages);

    PageFrame *frames = (PageFrame *)malloc(numFrames * sizeof(PageFrame));
    int *pageReferences = (int *)malloc(numPages * sizeof(int));

    if (frames == NULL || pageReferences == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter page reference string: ");
    for (int i = 0; i < numPages; i++)
    {
        scanf("%d", &pageReferences[i]);
    }

    int pageFaults = 0;

    for (int i = 0; i < numFrames; i++)
    {
        frames[i].pageNum = -1;
        frames[i].timeStamp = 0;
    }

    for (int i = 0; i < numPages; i++)
    {
        int pageFound = 0;
        for (int j = 0; j < numFrames; j++)
        {
            if (frames[j].pageNum == pageReferences[i])
            {
                frames[j].timeStamp = i + 1;
                pageFound = 1;
                break;
            }
        }
        if (!pageFound)
        {
            int lruIndex = findLRUPage(frames, numFrames);
            frames[lruIndex].pageNum = pageReferences[i];
            frames[lruIndex].timeStamp = i + 1;
            pageFaults++;
        }
    }

    printf("Number of page faults: %d\n", pageFaults);

    free(frames);
    free(pageReferences);

    return 0;
}
