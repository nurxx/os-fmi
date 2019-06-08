/*

Да се напише програма на C, която която създава файл в текущата директория и генерира два процесa, които записват низовете foo и bar в създадения файл.

Програмата  да записва низовете последователно, като първия е foo.


*/


#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <err.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		errx(1,"Wrong arguments count\n");
		exit(EXIT_FAILURE);
	}

	int fd1;
	int fd2;
	int status;

	if (fork()){
		wait(&status);
		printf("in parent\n");
		if ( (fd1 = open(argv[1],O_CREAT|O_WRONLY,0644)) == -1){
			errx(2,"Failed opening file in write mode\n");
			exit(EXIT_FAILURE);
		}
		lseek(fd1,3,SEEK_SET);
		write(fd1,"bar",3);		
		close(fd1);
	}
	else{
		printf("in child\n");
		if ( (fd2 = open(argv[1],O_CREAT|O_WRONLY,0644)) == -1){
			errx(2,"Failed opening file in write mode\n");
			exit(EXIT_FAILURE);
		}
		
		lseek(fd2,3,SEEK_SET);
		write(fd2,"foo",3);
		close(fd2);
	}
		
	


	exit(EXIT_SUCCESS);
}
