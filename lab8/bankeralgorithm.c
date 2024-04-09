#include <stdio.h>
#include <stdlib.h>

void issafe(int process[][3], int resources[], int maxneed[][3], int n)
{
    int need[n][3];
    for (int i = 0; i < n; i++)
    {
        printf("need for process(%d):", i);
        for (int j = 0; j < 3; j++)
        {
            need[i][j] = maxneed[i][j] - process[i][j];
            printf("%d \t", need[i][j]);
        }
        printf("\n");
    }

    int safesequence[n];
    int added[n];
    for (int j = 0; j < n; j++)
    {
        added[j] = 0;
    }
    int count = 0;
    while (count < n)
    {
        int found = 0;
        for (int i = 0; i < n; i++)
        {
            if (!added[i])
            {
                int j;
                for (j = 0; j < 3; j++)
                {
                    if (need[i][j] > resources[j])
                    {
                        break;
                    }
                }
                if (j == 3)
                {
                    safesequence[count++] = i;
                    added[i] = 1;
                    found = 1;
                    for (int k = 0; k < 3; k++)
                    {
                        resources[k] += process[i][k];
                    }
                }
            }
        }
        if (!found)
        {
            printf("System is not in safe state.\n");
            return;
        }
    }
    printf("safesequence:< ");
    for (int j = 0; j < n; j++)
    {
        printf("P(%d)", safesequence[j]);
    }
    printf(">");
}

int main()
{
    int n;
    printf("Enter no of processes: ");
    scanf("%d", &n);
    int process[n][3];
    int resources[3];
    for (int i = 0; i < 3; i++)
    {
        printf("Enter resources for %d: ", i);
        scanf("%d", &resources[i]);
    }
    for (int i = 0; i < n; i++)
    {
        printf("Enter resources for process(%d):\n", i);
        for (int j = 0; j < 3; j++)
        {
            printf("Enter resources for %d: ", i);
            scanf("%d", &process[i][j]);
            resources[j] -= process[i][j];
        }
    }
    int maxneed[n][3];
    for (int i = 0; i < n; i++)
    {
        printf("Enter maxneed for process(%d):\n", i);
        for (int j = 0; j < 3; j++)
        {
            printf("Enter resources for %d: ", i);
            scanf("%d", &maxneed[i][j]);
        }
    }
    issafe(process, resources, maxneed, n);
}
