#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void* imprime(void *tid){
    printf("Essa é a thread %d\n", (int) (size_t)tid);
    pthread_exit(NULL);
}

int main(int argc , char * argv[]){

    int num = atoi(argv[1]);
    printf("num = %d\n", num);
    int size = num;

    pthread_t thread[num];
    void *thread_return;
    printf("Processo principal criando threads\n");

    for (int i=0; i<num; i++){
        int status;

        status = pthread_create(&thread[i], NULL, imprime, i);
        if(status!=0){
            printf("Erro na criação da thread. Código do erro: %d\n", status);
            return 1;
        }
    }

    printf("Esperando thread finalizar....\n");
    pthread_join(thread, &thread_return); //equivale ao wait mas especifica qual thread vc quer esperar terminar
    printf("Thread finalizada\n");

    printf("Processo pai vai finalizar\n");

    return 0;

}