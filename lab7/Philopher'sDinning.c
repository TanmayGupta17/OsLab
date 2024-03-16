#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5
#define THINKING 0
#define HUNGRY 1
#define EATING 2
#define LEFT (i + NUM_PHILOSOPHERS - 1) % NUM_PHILOSOPHERS
#define RIGHT (i + 1) % NUM_PHILOSOPHERS

sem_t mutex;
sem_t forks[NUM_PHILOSOPHERS];

void *philosopher(void *arg) {
    int i = *(int *)arg;

    // Thinking
    printf("Philosopher %d is thinking.\n", i);
    sleep(rand() % 3);

    // Hungry
    printf("Philosopher %d is hungry.\n", i);
    sem_wait(&mutex);
    sem_wait(&forks[LEFT]);
    sem_wait(&forks[RIGHT]);
    sem_post(&mutex);

    // Eating
    printf("Philosopher %d is eating.\n", i);
    sleep(rand() % 3);

    // Finished eating
    sem_post(&forks[LEFT]);
    sem_post(&forks[RIGHT]);

    pthread_exit(NULL);
}

int main() {
    pthread_t philosophers[NUM_PHILOSOPHERS];

    // Initialize semaphores
    sem_init(&mutex, 0, 1);
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_init(&forks[i], 0, 1);
    }

    // Create philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_create(&philosophers[i], NULL, philosopher, &i);
    }

    // Wait for philosopher threads to finish
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }

    // Destroy semaphores
    sem_destroy(&mutex);
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_destroy(&forks[i]);
    }

    return 0;
}
