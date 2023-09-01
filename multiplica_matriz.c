#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define SIZE 20 // Tamanho das matrizes

int **A, **B, **C;

// Função para preencher a matriz com inteiros aleatórios entre 1 e 100
void fillMatrix(int **matrix) {
    int i, j;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            matrix[i][j] = rand() % 100 + 1;
        }
    }
}

// Função para calcular o tempo de execução em milissegundos
double getExecutionTime(struct timeval start, struct timeval end) {
    return (end.tv_sec - start.tv_sec) * 1000.0 + (end.tv_usec - start.tv_usec) / 1000.0;
}

int main() {
    int i, j, k;
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

    // Preenche a matriz C com a multiplicação de A por B
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            C[i][j] = 0;
            for (k = 0; k < SIZE; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
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