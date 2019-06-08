/*

Да се напише програма на С, която получава като параметър команда (без параметри) и при успешното ѝ изпълнение, извежда на стандартния изход името на командата.

*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <err.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

int main(int argc, char*argv[]){
	
	if (argc != 2){
		errx(1,"Wrong arguments count\n");
		exit(EXIT_FAILURE);	
	}
	int status;
		
	if (fork()){
		wait(&status);
		printf("Ran command -> %s\n",argv[1]);
	}
	else{
		char* path = strcat("/bin/",argv[1]); 
		if (execl(path,argv[1], (char*) NULL) == -1){
			errx(2,"Error execling\n");
			exit(EXIT_FAILURE);
		}
	}

	exit(EXIT_SUCCESS);
}
