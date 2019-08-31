/* реализация на конвейера "ls | wc -l" */
#include <stdint.h>
#include <stdio.h>
#include <sys/types.h>
#include <err.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
int main(){
	int fd[2];

	pipe(fd);

	pid_t ls_pid;
	if ((ls_pid = fork()) == -1){
		errx(1,"fork ls");
	}

	if(ls_pid == 0){
		close(fd[0]);
		if(dup2(fd[1],1) == -1){
			err(1,"dup2 ls");
		}
		if(execlp("ls","ls",NULL) == -1){
			err(1,"exec ls");
		}
	}
	close(fd[1]);
	if(dup2(fd[0],0) == -1){
		err(1,"dup2 ls -> wc");
	}

	if(execlp("wc","wc","-l",NULL) == -1){
		err(1,"exec wc");
	}
	exit(EXIT_SUCCESS);
}