/*
	Да се напише програма на C, която изпълнява команда ls с точно един аргумент.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <err.h>

int main(int argc, char*argv[])
{
	if (argc != 2){
		errx(1,"Wrong arguments count\n");
		exit(1);
	}

	if (execl("/bin/ls","ls",argv[1], (char*) NULL) == -1){
		errx(2,"Error listing\n");
		exit(2);
	}

	exit(EXIT_SUCCESS);
}
