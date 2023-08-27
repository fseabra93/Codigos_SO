
//aula4_shared_memory

#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <iostream>
//using namespace std;



int a =0;

void implementacao_filho1(int *a){
	*a = *a + 1;
	//cout << "Executando filho 1 = " << getpid() << endl;
	//cout << "Valor de a dentro do filho1(PID="<< getpid()<<") é " << *a << endl;
}

void implementacao_filho2(int *a){
	*a = *a + 2;
	//cout << "Executando filho 2 = " << getpid() << endl;
	//cout << "Valor de a dentro do filho2(PID="<< getpid()<<") é " << *a << endl;
}

int main(){
	int filho1, filho2, pid, status;

	/// implementação da memoria compartilhada
	char *mem;

	int seg_id = shmget(IPC_PRIVATE, 20*sizeof(char), IPC_CREAT | 0666);
	/// fim da implementação da memoria compartilhada


	cout << "Pai começou (PID=" << getpid() <<")" <<endl;

	filho1 = fork();
	if(!filho1){
		implementacao_filho1(&a);
		///inicio do uso de memoria compartilhada
		mem = shmat(seg_id, NULL, 0);
		sprintf(mem, "escrevendo teste");
		printf("%s no processo PID=%d\n", mem, getpid() );
		//cout << "escrevendo teste com cout";
		//cout << mem << " no processo PID=" << getpid();
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
			//cout << mem << " no processo PID=" << getpid();
			shmdt(mem);
			exit(0);
		}
	}

	status = wait(NULL);
	//cout << "(PID=" << getpid() <<") Processo sendo finalizado" << endl;
	//cout << "O valor final de a=" << a << endl;
	shmctl(seg_id, IPC_RMID, NULL);
	exit(0);
	//cout << "Pai terminou" << endl;

	return 0;



}