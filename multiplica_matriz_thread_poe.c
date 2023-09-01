#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

#define SIZE 20 // Tamanho das matrizes

int **A, **B, **C;

typedef struct {
    int row;
    int col;
} thread_data;

// Função para preencher a matriz com inteiros aleatórios entre 1 e 100
void fillMatrix(int **matrix) {
    int i, j;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            matrix[i][j] = rand() % 100 + 1;
        }
    }
}

// Função executada por cada thread para calcular a multiplicação de uma célula da matriz C
void *multiply(void *arg) {
    thread_data *data = (thread_data *)arg;
    int i = data->row;
    int j = data->col;
    int k;
    
    C[i][j] = 0;
    for (k = 0; k < SIZE; k++) {
        C[i][j] += A[i][k] * B[k][j];
    }
    
    pthread_exit(NULL);
}

// Função para calcular o tempo de execução em milissegundos
double getExecutionTime(struct timeval start, struct timeval end) {
    return (double)(end.tv_sec - start.tv_sec) * 1000.0 + (double)(end.tv_usec - start.tv_usec) / 1000.0;
}

int main() {
    int i, j;
    pthread_t threads[SIZE][SIZE];
    thread_data thread_data_array[SIZE][SIZE];
    struct timeval start_time, end_time;

    // Aloca a matriz A
    A = (int **)malloc(SIZE * sizeof(int *));
    for (i = 0; i < SIZE; i++) {
        A[i] = (int *)malloc(SIZE * sizeof(int));
    }

    // Aloca a matriz B
    B = (int **)malloc(SIZE * sizeof(int *));
    for (i = 0; i < SIZE; i++) {
        B[i] = (int *)malloc(SIZE * sizeof(int));
    }

    // Aloca a matriz C
    C = (int **)malloc(SIZE * sizeof(int *));
    for (i = 0; i < SIZE; i++) {
        C[i] = (int *)malloc(SIZE * sizeof(int));
    }

    // Preenche as matrizes A e B com inteiros aleatórios
    fillMatrix(A);
    fillMatrix(B);

    gettimeofday(&start_time, NULL); // Inicia a contagem do tempo

    // Cria as threads e define os dados para cada thread
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            thread_data_array[i][j].row = i;
            thread_data_array[i][j].col = j;
            pthread_create(&threads[i][j], NULL, multiply, &thread_data_array[i][j]);
        }
    }

    // Aguarda a conclusão de todas as threads
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            pthread_join(threads[i][j], NULL);
        }
    }

    gettimeofday(&end_time, NULL); // Finaliza a contagem do tempo

    // Imprime a matriz C (resultado da multiplicação)
    printf("Matriz C:\n");
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

    // Calcula e imprime o tempo de execução
    double execution_time = getExecutionTime(start_time, end_time);
    printf("Tempo de execução: %.2f ms\n", execution_time);

    // Libera a memória alocada
    for (i = 0; i < SIZE; i++) {
        free(A[i]);
        free(B[i]);
        free(C[i]);
    }
    free(A);
    free(B);
    free(C);

    return 0;
}