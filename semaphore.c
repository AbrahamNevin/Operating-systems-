#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

sem_t *mutex, *wrt;
int sharedvar = 99;
int readercount = 0;

void *reader(void *arg) {
    sem_wait(mutex);
    readercount++;
    if (readercount == 1)
        sem_wait(wrt);
    sem_post(mutex);

    printf("\nReader is reading sharedvar = %d", sharedvar);

    sem_wait(mutex);
    readercount--;
    if (readercount == 0)
        sem_post(wrt);
    sem_post(mutex);

    return NULL;
}

void *writer(void *arg) {
    printf("\nWriter trying to enter...");
    sem_wait(wrt);
    sharedvar++;
    printf("\nWriter updated sharedvar = %d", sharedvar);
    sem_post(wrt);
    return NULL;
}

int main() {
    int n, i;
    printf("Enter number of readers & writers: ");
    scanf("%d", &n);

    // Named semaphores
    mutex = sem_open("/mutex_sem", O_CREAT, 0644, 1);
    wrt   = sem_open("/wrt_sem", O_CREAT, 0644, 1);

    pthread_t readers[n], writers[n];

    for (i = 0; i < n; i++) {
        pthread_create(&writers[i], NULL, writer, NULL);
        pthread_create(&readers[i], NULL, reader, NULL);
    }

    for (i = 0; i < n; i++) {
        pthread_join(writers[i], NULL);
        pthread_join(readers[i], NULL);
    }

    // Clean up semaphores
    sem_close(mutex);
    sem_close(wrt);
    sem_unlink("/mutex_sem");
    sem_unlink("/wrt_sem");

    return 0;
}

