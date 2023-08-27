#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
using namespace std;

int main(){
	pid_t pid[5]={-1, -1, -1, -1, -1};
	int status;
	pid[0] = fork();
		if (pid[0] < 0){
			cout << "Erro ao criar processo #0\n";
			return 1;
		}
	if (pid[0] > 0){ //se for o pai...
		cout << "PAI: criando o segundo processo\n";
		pid[1] = fork();
			if (pid[1] < 0){
			cout << "Erro ao criar processo #0\n";
			return 1;
			}
	}
	//os filhos...
	if (pid[0] == 0){
		cout << "FILHO#0: Criando o processo filho cujo PID é o " << getpid() << endl;
		pid[2] = fork();
	}

	if (pid[1] == 0){
		cout << "FILHO#1: Criando o processo filho cujo PID é o " << getpid() << endl;
		pid[3] = fork();
	}

	if ((pid[0] == 0) || (pid[1] == 0)){
		//for (;;);
	}
	else{
		status = wait(NULL);
		cout << "Processo filho #" << status << " finalizou\n";
	}

	return 0;


}