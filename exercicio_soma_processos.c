#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/shm.h>

//exercicio_soma_processos

void somar(int *a, int b){
    *a = *a + b;
}

int main(int argc, char * argv[]){
    
    int num = atoi(argv[1]);
    printf("num = %d\n", num);
    int size = num;

    /// implementação da memoria compartilhada
	int *mem;
	int valor = shmget(IPC_PRIVATE, 20*sizeof(int), IPC_CREAT | 0666);
	mem = shmat(valor, NULL, 0);
    if (mem < 0){
		printf("Erro na alocação\n");
	return 0;
	}
    *mem = 0;

    //processos
    pid_t pid[size];
    for (int i=0; i<size; i++){
        pid[i] = -1;
    }
    	
    for (int i=0; i<size; i++){
        pid[i] = fork();
	    if (pid[i] == 0){
            mem = shmat(valor, NULL, 0);
            int contador = i+1;
            somar(mem , contador);
            printf("Filho %d finalizou (PID=%d) e o valor da soma é %d\n", i+1, getpid(), *mem);
		    shmdt(mem);
            exit(0);
	    }
    }

	for(int i=0; i<size*2; i++){
		wait(NULL);
	}

	shmctl(valor, IPC_RMID, NULL);
	printf("Soma = %d\n", *mem);
	printf("Pai terminou\n");
	exit(0);

	return 0;

}