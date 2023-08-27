#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(){

	pid_t pid;
	pid = fork();
	if (pid < 0){
		fprintf(stderr, "Criação falhou");
		exit(-1);
	}
	else if (pid == 0){
		printf("Esta é a execução do filho (PID=%d), cujo pai é o PID=%d\n, ", getpid(), getppid());
			execlp("/bin/ls", "ls", "-l", NULL);
			printf("Testando o execlp\n");
			exit(0);
	}
	else{
		wait(NULL);
		printf("Processo filho finalizou\n");
		exit(0);
	}
	return 0;


}