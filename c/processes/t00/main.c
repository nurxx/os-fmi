/*
Да се напише програма на C, която изпълнява команда date.
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <err.h>

int main()
{
	
	if ((execl("/bin/date","date", (char*) NULL)) == -1){
		errx(1,"Error\n");
	}

	printf("Success\n");

	exit(EXIT_SUCCESS);
}
