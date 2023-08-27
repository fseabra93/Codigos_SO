//aula4_pipe2

#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define MAX_SIZE 4

int main(int argc, char *argv[]){

    int vetor_pipe_ida[2], vetor_pipe_volta[2];
    pid_t pid;
    char buffer[MAX_SIZE];
    int num, resposta;

    pipe(vetor_pipe_ida); //cria o  pipe;
    pipe(vetor_pipe_volta); //cria o pipe
    pid = fork();
    if (pid == 0)// se é o processo filho
    {
        close(vetor_pipe_ida[1]); //fecha o caminho de escrita deste pipe pois não será usado
        while(read(vetor_pipe_ida[0], buffer, MAX_SIZE) > 0); //leia enquanto não for o EOF

        sscanf(buffer, "%d", &num);
        close(vetor_pipe_ida[0]); //fecha o caminho de leitura do pipe pois concluiu a leitura
        printf("O filho leu: %d\n", num);

        num = num+1;
        sprintf(buffer, "%d", num);

        // agora vamos responder ao pai

        close(vetor_pipe_volta[0]);//fecha o caminho de leitura deste pipe

        write(vetor_pipe_volta[1], buffer, MAX_SIZE);
        close(vetor_pipe_volta[1]);

        printf("FILHO: O filho escreveu: %d\n", num);
        printf("FILHO: O filho terminou\n");

        exit(0);
        
    }
    else // se for o processo pai
    {
        num = atoi(argv[1]);
        sprintf(buffer, "%d", num);
        close(vetor_pipe_ida[0]);//fecha o caminho de leitura deste pipe
        write(vetor_pipe_ida[1], buffer, MAX_SIZE); // envia o conteudo
        close(vetor_pipe_ida[1]);
        printf("PAI: O pai escreveu: %s\n", buffer);

        // agora vamos ler a resposta do filho

        close(vetor_pipe_volta[1]);
        while(read(vetor_pipe_volta[0], buffer, MAX_SIZE)>0)
        close(vetor_pipe_volta[0]);
        sscanf(buffer, "%d", &num);
        printf("PAI: O pai leu: %d\n", num);

        wait(NULL);
        printf("PAI: O filho terminou\n");
        printf("PAI: O pai terminou\n");

        exit(0);


    }



}