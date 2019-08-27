#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <err.h>
#include <fcntl.h>

int main(int argc, char **argv){
	int i;
	for (i = 1; i < argc - 1; i++){
		int fd[2];
		pipe(fd);

		pid_t p = fork();
		if (p == -1){
			err(1,"fork process");
		}
		if (p == 0){
			close(fd[0]);
			if (dup2(fd[1],1) == -1){
				err(1,"dup2");
			}

			if (execlp(argv[i],argv[i],NULL) == -1){
				err(1,"execlp");
			}
		}
		close(fd[1]);
		if(dup2(fd[0],0) == -1){
			err(1,"dup2 parent");
		}
	}
	if(execlp(argv[i],argv[i],NULL)==-1){
		err(1,"execlp last");
	}
	exit(EXIT_SUCCESS);
}