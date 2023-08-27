
//aula4_shared_memory2

#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/shm.h>
//#include <iostream>
//using namespace std;



int a =0;

void implementacao_filho1(int *a){
	*a = *a + 1;
	printf("Executando filho 1 = %d\n", getpid());
	printf("Valor de a dentro do filho1(PID=%d) é %d\n", getpid(), *a);

}

void implementacao_filho2(int *a){
	*a = *a * 2;
	printf("Executando filho 2 = %d\n", getpid());
	printf("Valor de a dentro do filho 2 (PID=%d) é %d\n", getpid(), *a);
}

int main(){
	int filho1, filho2, pid, status;

	/// implementação da memoria compartilhada
	int *mem;

	int valor = shmget(IPC_PRIVATE, 20*sizeof(int), IPC_CREAT | 0666);
	/// fim da implementação da memoria compartilhada

	mem = shmat(valor, NULL, 0);
	if (mem < 0){
		printf("Erro na alocação\n");
		return 0;
	}
	*mem = 5;

	printf("Pai começou (PID=%d) e o valor do inteiro é %d\n", getpid(), *mem);

	filho1 = fork();
	if (filho1 > 0){
		filho2 = fork();
	}
	if (filho1 == 0){//se for o filho 1
		mem = shmat(valor, NULL, 0);
		//sleep(1);
		implementacao_filho1(mem);
		printf("Filho 1 finalizou (PID=%d) e o valor do inteiro é %d\n", getpid(), *mem);
		shmdt(mem);
		exit(0);
	}
	else if (filho2 == 0){ // se for o filho2
		mem = shmat(valor, NULL, 0);
		implementacao_filho2(mem);
		printf("Filho 2 finalizou (PID=%d) e o valor do inteiro é %d\n", getpid(), *mem);
		shmdt(mem);
		exit(0);
	}

	for(int i=0; i<2; i++){
		wait(NULL);
	}

	shmctl(valor, IPC_RMID, NULL);
	printf("valor= %d\n", *mem);
	printf("Pai terminou\n");
	exit(0);

	return 0;



}