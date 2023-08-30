#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *threadFunction(void *arg) {
    int threadNumber = *(int *)arg;
    printf("Thread %d\n", threadNumber);
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: ./programa <num>\n");
        return 1;
    }

    int numThreads = atoi(argv[1]);
    pthread_t *threads = malloc(sizeof(pthread_t) * numThreads);

    for (int i = 0; i < numThreads; i++) {
        int *threadNumber = malloc(sizeof(int));
        *threadNumber = i;
        pthread_create(&threads[i], NULL, threadFunction, threadNumber);
    }

    for (int i = 0; i < numThreads; i++) {
        pthread_join(threads[i], NULL);
    }

    free(threads);

    printf("Processo original terminou\n");

    return 0;

}