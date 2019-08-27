// ls | sort | wc 

#include <unistd.h>
#include <sys/types.h>
#include <err.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
	if (argc != 2){
		errx(1,"invalid arguments count");
	}

	int fd1[2];
	int fd2[2];

	pipe(fd1);
	pipe(fd2);

	pid_t ls_pid;
	pid_t sort_pid;

	if((ls_pid = fork()) == -1){
		err(1,"fork cat");
	}

	if (ls_pid == 0){
		close(fd1[0]);

		if (dup2(fd1[1],1) == -1){
			err(1,"dup2 ls");
		}

		if (execlp("ls","ls",NULL) == -1){
			err(1,"execlp ls");
		}
	}
	close(fd1[1]);

	if (dup2(fd1[0],0) == -1){
		err(1,"dup2 ls parent");
	}
	
	if ((sort_pid = fork()) == -1){
		err(1,"fork sort");
	}
	if (sort_pid == 0 ){
		close(fd2[0]);

		if (dup2(fd2[1],1) == -1){
			err(1,"dup2 sort");
		}

		if (execlp("sort","sort",NULL) == -1){
			err(1,"execlp sort");
		}
	}
	close(fd2[1]);

	if(dup2(fd2[0],0) == -1){
		err(1,"dup2 parent");
	} 
	if (execlp("wc","wc",argv[1],NULL) == -1){
		err(1,"execlp wc -l");
	}

	exit(EXIT_SUCCESS);
}