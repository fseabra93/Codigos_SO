
//aula4_shared_memory

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
	*a = *a + 2;
	printf("Executando filho 2 = %d\n", getpid());
	printf("Valor de a dentro do filho 2 (PID=%d) é %d\n", getpid(), *a);
}

int main(){
	int filho1, filho2, pid, status;

	/// implementação da memoria compartilhada
	char *mem;

	int seg_id = shmget(IPC_PRIVATE, 20*sizeof(char), IPC_CREAT | 0666);
	/// fim da implementação da memoria compartilhada

	printf("Pai começou (PID=%d)\n", getpid());

	filho1 = fork();
	if(!filho1){
		implementacao_filho1(&a);
		///inicio do uso de memoria compartilhada
		mem = shmat(seg_id, NULL, 0);
		sprintf(mem, "escrevendo teste");
		printf("%s no processo PID=%d\n", mem, getpid() );
		shmdt(mem);
		///fim do uso de memoria compartilhada
		exit(0);
	}

	status = wait(NULL);
	if(filho1 >0){
		filho2 = fork();
		if(!filho2){
			implementacao_filho2(&a);
			mem = shmat(seg_id, NULL, 0);
			printf("%s no processo PID=%d\n", mem, getpid());
			shmdt(mem);
			exit(0);
		}
	}

	status = wait(NULL);
	printf("(PID=%d) Processo sendo finalizado", getpid());
	printf("O valor final de a=%d\n\n", a);

	shmctl(seg_id, IPC_RMID, NULL);
	exit(0);
	printf("Pai terminou\n");

	return 0;



}