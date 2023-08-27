#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
using namespace std;

int main(){
	pid_t pid;
	pid = fork();

	if (pid<0){
		cout << "Erro ao criar processo\n";
		return 1;
	}
	else if (pid == 0){
		cout << "Essa é a execução do filho\n";
		cout << "Esperando.....\n";
		sleep(10);
		cout << "Voltou\n";
		execlp("/bin/ls", "ls", "-l", NULL);
	}
	else {
		wait(NULL);
		cout << "Processo filho finalizou\n";
	}
	return 0;
}