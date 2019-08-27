// cat | sort -n | pipe()

#include <unistd.h>
#include <sys/types.h>
#include <err.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char* argv[]){
	if (argc!=3){
		errx(1,"invalid arguments count");
	}

	int fd[2];
	pipe(fd);

	pid_t cat_pid;

	if((cat_pid=fork()) == -1){
		err(1,"fork cat");
	}

	if(cat_pid == 0){
		close(fd[0]);

		if(dup2(fd[1],1) == -1){
			err(1,"dup2 cat");
		}

		if(execlp("cat","cat",argv[1],NULL) == -1){
			err(1,"exec cat");
		}
	}
	close(fd[1]);

	if (dup2(fd[0],0) == -1){
		err(1,"dup2 parent");
	}

	if(execlp("sort","sort",argv[2],NULL) == -1){
		err(1,"exec sort");
	}

	exit(EXIT_SUCCESS);
}