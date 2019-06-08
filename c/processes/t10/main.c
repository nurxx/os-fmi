/*

Да се напише програма на С, която получава като параметри три команди (без параметри), изпълнява ги последователно, като изчаква края на всяка и извежда на стандартния изход номера на завършилия процес, както и неговия код на завършване.

*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <err.h>

int main(int argc, char*argv[]){
	if (argc != 4){
		errx(1,"Wrong arguments count\n");
		exit(EXIT_FAILURE);
	}
	
	int stat_1;
	int stat_2;

	pid_t p1;
	pid_t p2;

	if ((p1=fork()) > 0){
		wait(&stat_1);
		printf("pid: %d with exit status: %d",getpid(),WIFEXITED(stat_1));
		if((p2=fork()) > 0){
			wait(&stat_2);
			printf("pid: %d with exit status: %d",getpid(),WIFEXITED(stat_2));
			execlp(argv[3],argv[3],(char*)NULL);
		}
		else{
			execlp(argv[2],argv[2],(char*)NULL);		
		}
	}
	else{
		execlp(argv[1],argv[1],(char*)NULL);
	}
	 
	exit(EXIT_SUCCESS);
}


