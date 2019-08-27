#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <err.h>
#include <sys/types.h>

int main(int argc, char **argv)
{
	int fd = open("serror.txt",O_RDWR | O_CREAT | O_TRUNC );
	dup2(fd,2);

	if(execvp("sort",argv) == -1){
		err(1,"exec sort");
	}
	exit(EXIT_SUCCESS);
}