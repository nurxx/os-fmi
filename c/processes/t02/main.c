/*

Да се напише програма на C, която изпълнява команда sleep (за 60 секунди)

*/


#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <err.h>

int main(int argc, char* argv[])
{
	if (argc != 2){
		errx(99,"Not passed sleep duration\n");
		exit(99);
	}

	if (execl("/bin/sleep","sleep",argv[1],(char*) NULL) == -1){
		errx(1,"Error\n");
		exit(1);
	}

	exit(EXIT_SUCCESS);
}
