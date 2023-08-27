#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
using namespace std;



int a =0;

void implementacao_filho1(int *a){
	*a = *a + 1;
	cout << "Executando filho 1 = " << getpid() << endl;
	cout << "Valor de a dentro do filho1(PID="<< getpid()<<") é " << *a << endl;
}

void implementacao_filho2(int *a){
	*a = *a + 2;
	cout << "Executando filho 2 = " << getpid() << endl;
	cout << "Valor de a dentro do filho2(PID="<< getpid()<<") é " << *a << endl;
}

int main(){
	int filho1, filho2, pid, status;
	cout << "Pai começou (PID=" << getpid() <<")" <<endl;

	filho1 = fork();
	if(!filho1){
		implementacao_filho1(&a);
		exit(0);
	}

	wait(NULL);
	if(filho1 >0){
		filho2 = fork();
		if(!filho2){
			implementacao_filho2(&a);
			exit(0);
		}
	}

	pid = wait(NULL);
	cout << "(PID=" << getpid() <<") O PID do processo finalizado é o " << pid << endl;
	cout << "O valor final de a=" << a << endl;

	exit(0);
	cout << "Pai terminou" << endl;

	return 0;



}

