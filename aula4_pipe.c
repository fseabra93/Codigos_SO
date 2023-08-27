//aula4_pipe

#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]){

	int vetor_pipe[2], TAM; //0 para ler e 1 para escrever
	pid_t pid;
	TAM = strlen(argv[1]) + 1;
	char buffer[TAM];

	pipe(vetor_pipe); //cria o pipe
	pid = fork(); //cria um novo processo
	if (pid == 0){ //se é o processo filho
		close(vetor_pipe[1]); //fecha o caminho de escrita pois não será utilizado
		while (read(vetor_pipe[0], &buffer, TAM) > 0)  // leia enquanto não for o fim
		close(vetor_pipe[0]); //fecha o caminho de leitura do pipe
		printf("FILHO: O filho terminou e leu: %s\n", buffer);
		exit(EXIT_SUCCESS); // termina o processo filho
	}
	else{
		close(vetor_pipe[0]); // fecha o caminho de leitura pois não será utilizado
		sleep(2);
		write (vetor_pipe[1], argv[1], strlen(argv[1])+1); //envia o conteúdo do parâmetro
		close(vetor_pipe[1]); // fecha o caminho de escrita caracterizando o fim (EOF)
		printf("PAI: O pai terminou e escreveu: %s\n", argv[1]);
		wait(NULL); // espera até que o filho termine
		printf("PAI: O filho terminou");
		exit(EXIT_SUCCESS);

	}
	return 0;
}