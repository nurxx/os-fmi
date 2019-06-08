/*

Да се напише програма на C, която получава като параметри от команден ред две команди (без параметри). Изпълнява първата. Ако тя е завършила успешно изпълнява втората.
Ако не, завършва с код -1.

*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <err.h>
#include <string.h>

int main(int argc, char*argv[]){

	if (argc != 3){
		errx(1,"Wrong arguments count\n");
		exit(EXIT_FAILURE);
	}
	
	pid_t pid = fork();
	int status;
	if (pid > 0){
		waitpid(pid,&status,0);		
		if(status == -1)
		{
			printf("%d\n",-1);
		}
		else{
			execlp(argv[2],argv[2],(char*)NULL);
	}	}
	else{
		execlp(argv[1],argv[1],(char*) NULL);
	}

	exit(EXIT_SUCCESS);
}
