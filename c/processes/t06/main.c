/*

Да се напише програма на С, която получава като параметър име на файл. Създава процес син, който записва стринга foobar във файла (ако не съществува, го създава, в противен случай го занулява), след което процеса родител прочита записаното във файла съдържание и го извежда на стандартния изход, добавяйки по един интервал между всеки два символа.

*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <err.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
	
	if (argc != 2){
		errx(1,"Wrong arguments count\n");
		exit(EXIT_FAILURE);
	}
	
	int fd1;
	int fd2;	
	if((fd1 = open(argv[1],O_CREAT | O_WRONLY | O_TRUNC, 0644)) == -1){
		errx(2,"Failed opening file in write mode\n");
		exit(EXIT_FAILURE);
	}

	if((fd2 = open(argv[1],O_RDONLY)) == -1){
		errx(3,"Failed opening file in read mode\n");
		exit(EXIT_FAILURE);
	}

	char c;
	int status;
	if( fork() > 0){
		wait(&status);
		while(read(fd2,&c,1) > 0){
			write(1,&c,1);
			write(1," ",1);
		}
	}
	else{
		write(fd1,"foobar",6);
		close(fd1);
	}
	
	close(fd1);	

	exit(EXIT_SUCCESS);
}
