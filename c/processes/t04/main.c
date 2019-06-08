#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>


int main ()
{
	int n = 100;
	int status;

	if (fork()) {
		wait(&status);
		for (int i = 0; i < n; i++) {
			printf("father\n");
		}
	} else {
		for (int i = 0; i < n; i++) {
			printf("son\n");
		}
	}

	exit(EXIT_SUCCESS);
}
