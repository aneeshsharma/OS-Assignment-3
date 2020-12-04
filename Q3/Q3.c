#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

sem_t mutex;
sem_t S[5];

void signalHandler(int signal)
{
    if (signal == SIGINT)
    {
        printf("Exiting now.\n");
        exit(0);
    }
}
int status[5];
int phil[5] = {0, 1, 2, 3, 4};

void *philosopher(void *num)
{
    while (1)
    {
        int *n = num;
        sleep(1);
        get_forks(*n);
        sleep(0);
        put_forks(*n);
    }
}
void think(int position)
{
    int thinking;

    thinking = 10;
    printf("Philosopher %d is thinking for %d seconds.\n", phil[position], thinking);
    sleep(thinking);
}

// Function that tell a philosopher to 'eat'
void eat(int position)
{
    int eating;

    eating = 11;
    printf("Philosopher %d is eating for %d seconds.\n", phil[position], eating);
    sleep(eating);
}

// Function that tell a philosopher to start eating if hungry
void get_forks(int position)
{
    sem_wait(&mutex);
    status[position] = 1;
    printf("Philosopher %d is hungry.\n", phil[position]);
    checkNeighbor(position);
    sem_post(&mutex);
    sem_wait(&S[position]);
}

// Function that tell a philosopher to stop eating and start thinking
void put_forks(int position)
{
    sem_wait(&mutex);
    status[position] = 0;
    think(position);
    checkNeighbor((position + 4) % 5);
    checkNeighbor((position + 1) % 5);
    sem_post(&mutex);
}

// Function that check whether a philosopher can start eating or not.
void checkNeighbor(int position)
{
    if (status[position] == 1 && status[(position + 4) % 5] != 2 && status[(position + 1) % 5] != 2)
    {
        status[position] = 2;
        eat(position);
        sem_post(&S[position]);
    }
}

int main()
{
    signal(SIGINT, signalHandler);

    int i;
    pthread_t tID[5];
    sem_init(&mutex, 0, 1);

    for (i = 0; i < 5; i++)
    {
        sem_init(&S[i], 0, 0);
    }
    for (i = 0; i < 5; i++)
    {
        pthread_create(&tID, NULL, philosopher, &phil[i]);
        think(i);
    }
    for (i = 0; i < 5; i++)
    {
        pthread_join(tID[i], NULL);
    }
}
