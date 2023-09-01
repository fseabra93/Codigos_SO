#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define ARRAY_SIZE 10

typedef int matrix_t[ARRAY_SIZE][ARRAY_SIZE];
matrix_t MA,MB,MC;

typedef struct {
  int       id;
  int       size;
  int       row;
  int       column;
  matrix_t  *MA;
  matrix_t  *MB;
  matrix_t  *MC;
} matrix_work_order_t;

/* Routine to multiply a row by a column and place element in the result matrix. */

void mult(int size,             /* size of the matrix */
          int row,              /* row of result to compute */
          int column,           /* column of result to compute */
          matrix_t MA,          /* input matrix */
          matrix_t MB,          /* input matrix */
          matrix_t MC) {       /* result matrix */

      int position;

      printf("imprime dentro de mult\n");
      for (int i=0; i<size; i++){
        for (int j=0; j<size; j++){
            printf("%d ", MA[i][j]);
        }printf("\n");
      }

      MC[row][column] = 0;
      for(position = 0; position < size; position++) {
            MC[row][column] = MC[row][column] +
              ( MA[row][position]  *  MB[position][column] ) ;
      }
}

void peer_mult(matrix_work_order_t *work_orderp)
{

   mult(work_orderp->size,
        work_orderp->row,
        work_orderp->column,
        *(work_orderp->MA),
        *(work_orderp->MB),
        *(work_orderp->MC));

   free(work_orderp);
}

void preencher(){
    srand(time(NULL));
    int r;

    for (int i = 0; i < ARRAY_SIZE; i++){
        for (int j = 0; j < ARRAY_SIZE; j++){
            r = rand();
            //MA[i][j] = r%100; 
            MA[i][j] = 3; 
        }
    }

    for (int i = 0; i < ARRAY_SIZE; i++){
        for (int j = 0; j < ARRAY_SIZE; j++){
            r = rand();
            MB[i][j] = 4;//r%100; 
        }
    }


}

void imprimir(){

    printf("Matriz\n");
    for (int i = 0; i < ARRAY_SIZE; i++){
        for (int j = 0; j < ARRAY_SIZE; j++){
            printf("%3d ", MC[i][j]); 
        }printf("\n");
    }
    printf("\n");
/*
    printf("Matriz B\n");

    for (int i = 0; i < tam; i++){
        for (int j = 0; j < tam; j++){
            printf("%3d ", MB[i][j]);  
        }printf("\n");
    }


    printf("\n");
    printf("Matriz C\n");

    for (int i = 0; i < tam; i++){
        for (int j = 0; j < tam; j++){
            printf("%3d ", MC[i][j]);  
        }printf("\n");
    }*/
}


int main(void) {
      int size = ARRAY_SIZE, row, column;
      matrix_t MA,MB,MC;

      preencher();

      matrix_work_order_t *work_orderp;
      pthread_t peer[size*size];

      /* Process Matrix, by row, column */
      for(row = 0; row < size; row++)   {
        for (column = 0; column < size; column++) {

             int id = column + row*10;

             work_orderp =
             (matrix_work_order_t *)malloc(sizeof(matrix_work_order_t));
             work_orderp->id = id;
             work_orderp->size = size;
             work_orderp->row = row;
             work_orderp->column = column;
             work_orderp->MA = &MA;
             work_orderp->MB = &MB;
             work_orderp->MC = &MC;

             pthread_create(&(peer[id]), NULL, (void *)peer_mult,
                             (void *)work_orderp);
        }
      }

             /* Wait for peers to exit */
      for (int i = 0; i < (size * size); i++) {
         pthread_join(peer[i],  NULL);
      }

      imprimir();
      

      return 0;
}
