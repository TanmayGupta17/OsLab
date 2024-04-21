#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void FCFS(int queue[], int ht, int tt, int n)
{
    int seek = 0;
    for (int i = 0; i < n; i++)
    {
        if (i == 0)
        {
            seek += abs(ht - queue[i]);
        }
        else
        {
            seek += abs(queue[i - 1] - queue[i]);
        }
    }
    printf("FCFS: %d", seek);
}

void SSTF(int queue[], int ht, int tt, int n)
{
    int seek = 0;
    int count = 0;
    int visited[n];
    for (int i = 0; i < n; i++)
        visited[i] = 0;
    while (count < n)
    {
        int shortest = INT_MAX;
        int t;
        for (int i = 0; i < n; i++)
        {
            int s;
            if (visited[i] == 0)
            {
                s = abs(ht - queue[i]);
                if (shortest > s)
                {
                    shortest = s;
                    t = i;
                }
            }
        }
        ht = queue[t];
        visited[t] = 1;
        seek += shortest;
        count++;
    }
    printf("SSTF: %d", seek);
}

void SCAN(int queue[], int ht, int tt, int n, char dir)
{
    int seek = 0;
    int visited[n];

    for (int i = 0; i < n; i++)
        visited[i] = 0;

    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (queue[j] < queue[i])
            {
                int temp = queue[j];
                queue[j] = queue[i];
                queue[i] = temp;
            }
        }
    }

    int ind;
    for (int i = 0; i < n; i++)
    {
        if (queue[i] >= ht)
        {
            ind = i;
            break;
        }
    }

    if (dir == 'r')
    {
        for (int i = ind; i < n; i++)
        {
            seek += abs(ht - queue[i]);
            ht = queue[i];
            visited[i] = 0;
        }
        seek += abs(ht - tt);
        ht = tt;
        for (int i = n - 1; i >= 0; i++)
        {
            if (visited[i] == 0)
            {
                seek += abs(ht - queue[i]);
                ht = queue[i];
                visited[i] = 0;
            }
        }
    }

    else if (dir == 'l')
    {
        for (int i = ind - 1; i >= 0; i--)
        {
            seek += abs(ht - queue[i]);
            ht = queue[i];
            visited[i] = 1;
        }
        seek += ht;
        ht = 0;
        for (int i = 0; i < n; i++)
        {
            if (visited[i] == 0)
            {
                seek += abs(ht - queue[i]);
                ht = queue[i];
                visited[i] = 1;
            }
        }
    }
    printf("SCAN: %d", seek);
}

void CSCAN(int queue[], int ht, int tt, int n, char dir)
{
    int seek = 0;
    int visited[n];
    for (int i = 0; i < n; i++)
    {
        visited[i] = 0;
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (queue[j] < queue[i])
            {
                int temp = queue[j];
                queue[j] = queue[i];
                queue[i] = temp;
            }
        }
    }

    int ind;
    for (int i = 0; i < n; i++)
    {
        if (queue[i] >= ht)
        {
            ind = i;
            break;
        }
    }

    for (int i = ind; i < n; i++)
    {
        seek += abs(ht - queue[i]);
        ht = queue[i];
        visited[i] = 1;
    }
    seek += abs(ht - tt);
    seek += abs(tt - 0);
    ht = 0;
    for (int i = 0; i < n; i++)
    {
        if (visited[i] == 0)
        {
            seek += abs(ht - queue[i]);
            ht = queue[i];
            visited[i] = 1;
        }
    }

    printf("CSCAN: %d", seek);
}

void LOOK(int queue[], int ht, int tt, int n)
{
    int seek = 0;
    int visited[n];
    for (int i = 0; i < n; i++)
    {
        visited[i] = 0;
    }

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (queue[j] < queue[i])
            {
                int temp = queue[i];
                queue[i] = queue[j];
                queue[j] = temp;
            }
        }
    }

    int ind;
    for (int i = 0; i < n; i++)
    {
        if (queue[i] >= ht)
        {
            ind = i;
            break;
        }
    }

    for (int i = ind; i < n; i++)
    {
        seek += abs(ht - queue[i]);
        ht = queue[i];
        visited[i] = 1;
    }
    for (int i = ind - 1; i >= 0; i--)
    {
        seek += abs(ht - queue[i]);
        ht = queue[i];
        visited[i] = 1;
    }
    printf("LOOK: %d", seek);
}

void CLOOK(int queue[], int ht, int tt, int n)
{
    int seek = 0;
    int visited[n];
    for (int i = 0; i < n; i++)
    {
        visited[i] = 0;
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (queue[j] < queue[i])
            {
                int temp = queue[j];
                queue[j] = queue[i];
                queue[i] = temp;
            }
        }
    }

    int ind;
    for (int i = 0; i < n; i++)
    {
        if (queue[i] >= ht)
        {
            ind = i;
            break;
        }
    }

    for (int i = ind; i < n; i++)
    {
        seek += abs(ht - queue[i]);
        ht = queue[i];
        visited[i] = 1;
    }
    seek += abs(queue[n - 1] - queue[0]);
    ht = queue[0];
    for (int i = 1; i < n; i++)
    {
        if (visited[i] == 0)
        {
            seek += abs(ht - queue[i]);
            ht = queue[i];
            visited[i] = 1;
        }
    }
    printf("CLOOK: %d", seek);
}

int main()
{
    int head_track, tail_track;
    int n;
    printf("Enter no of elements in the queue: ");
    scanf("%d", &n);
    int queue[n];
    printf("Enter elements: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &queue[i]);
    }
    printf("Enter head track: ");
    scanf("%d", &head_track);
    printf("Enter tail track: ");
    scanf("%d", &tail_track);
    char direction;
    printf("Enter the direction (l for left, r for right): ");
    scanf(" %c", &direction);

    FCFS(queue, head_track, tail_track, n);
    SSTF(queue, head_track, tail_track, n);
    SCAN(queue, head_track, tail_track, n, direction);
    CSCAN(queue, head_track, tail_track, n, direction);
    LOOK(queue, head_track, tail_track, n);
    CLOOK(queue, head_track, tail_track, n);
}
