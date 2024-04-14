#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_REQUESTS 100

// Function to sort the array in ascending order
void sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Function to find the index of the request nearest to the head
int findNearest(int arr[], int n, int head) {
    int minDistance = INT_MAX;
    int index = -1;

    for (int i = 0; i < n; i++) {
        if (abs(head - arr[i]) < minDistance) {
            minDistance = abs(head - arr[i]);
            index = i;
        }
    }

    return index;
}

// SSTF Disk Scheduling Algorithm
void sstf(int requests[], int n, int head) {
    int totalSeek = 0;
    int visited[MAX_REQUESTS] = {0};

    for (int i = 0; i < n; i++) {
        int nearestIndex = findNearest(requests, n, head);
        totalSeek += abs(head - requests[nearestIndex]);
        head = requests[nearestIndex];
        visited[nearestIndex] = 1;
    }

    printf("Total seek time using SSTF: %d\n", totalSeek);
}

// SCAN Disk Scheduling Algorithm
void scan(int requests[], int n, int head, int direction, int maxCylinder) {
    int totalSeek = 0;

    sort(requests, n);

    if (direction == 0) { // Moving towards higher cylinder numbers
        for (int i = 0; i < n; i++) {
            if (requests[i] >= head) {
                totalSeek += abs(head - requests[i]);
                head = requests[i];
            }
        }
        totalSeek += abs(head - maxCylinder);
    } else { // Moving towards lower cylinder numbers
        for (int i = n - 1; i >= 0; i--) {
            if (requests[i] <= head) {
                totalSeek += abs(head - requests[i]);
                head = requests[i];
            }
        }
        totalSeek += head;
    }

    printf("Total seek time using SCAN: %d\n", totalSeek);
}

// C-SCAN Disk Scheduling Algorithm
void cscan(int requests[], int n, int head, int direction, int maxCylinder) {
    int totalSeek = 0;

    sort(requests, n);

    if (direction == 0) { // Moving towards higher cylinder numbers
        for (int i = 0; i < n; i++) {
            if (requests[i] >= head) {
                totalSeek += abs(head - requests[i]);
                head = requests[i];
            }
        }
        totalSeek += abs(head - maxCylinder);
        totalSeek += maxCylinder; // Move back to 0
    } else { // Moving towards lower cylinder numbers
        for (int i = n - 1; i >= 0; i--) {
            if (requests[i] <= head) {
                totalSeek += abs(head - requests[i]);
                head = requests[i];
            }
        }
        totalSeek += head; // Move back to maxCylinder
    }

    printf("Total seek time using C-SCAN: %d\n", totalSeek);
}

// C-LOOK Disk Scheduling Algorithm
void clook(int requests[], int n, int head, int direction, int maxCylinder) {
    int totalSeek = 0;

    sort(requests, n);

    if (direction == 0) { // Moving towards higher cylinder numbers
        for (int i = 0; i < n; i++) {
            if (requests[i] >= head) {
                totalSeek += abs(head - requests[i]);
                head = requests[i];
            }
        }
    } else { // Moving towards lower cylinder numbers
        for (int i = n - 1; i >= 0; i--) {
            if (requests[i] <= head) {
                totalSeek += abs(head - requests[i]);
                head = requests[i];
            }
        }
    }

    printf("Total seek time using C-LOOK: %d\n", totalSeek);
}

int main() {
    int requests[MAX_REQUESTS];
    int n, head, maxCylinder, direction;

    printf("Enter the number of requests: ");
    scanf("%d", &n);

    printf("Enter the requests: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }

    printf("Enter the initial position of the head: ");
    scanf("%d", &head);

    printf("Enter the maximum cylinder number: ");
    scanf("%d", &maxCylinder);

    printf("Enter the direction of movement (0 - towards higher cylinder numbers, 1 - towards lower cylinder numbers): ");
    scanf("%d", &direction);

    int choice;
    printf("\nDisk Scheduling Algorithms Menu:\n");
    printf("1. SSTF\n");
    printf("2. SCAN\n");
    printf("3. C-SCAN\n");
    printf("4. C-LOOK\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch(choice) {
        case 1:
            sstf(requests, n, head);
            break;
        case 2:
            scan(requests, n, head, direction, maxCylinder);
            break;
        case 3:
            cscan(requests, n, head, direction, maxCylinder);
            break;
        case 4:
            clook(requests, n, head, direction, maxCylinder);
            break;
        default:
            printf("Invalid choice.\n");
            break;
    }

    return 0;
}
