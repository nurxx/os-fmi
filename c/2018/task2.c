// Напишете програма на С, която приема параметър - име на директория.
// Програмата трябва да извежда името на най-скоро променения(по съдържание)
// файл в тази директория и нейните поддиректории чрез употреба на 
// външни shell команди през pipe()

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <err.h>
#include <sys/types.h>

int main(int argc,char **argv)
{
	if (argc != 2) errx(1,"invalid arguments count");

	int fd1[2];
	int fd2[2];
	int fd3[2];

	pipe(fd1);
	pipe(fd2);
	pipe(fd3);

	pid_t find_pid;
	pid_t sort_pid;
	pid_t head_pid;

	if((find_pid = fork()) == -1) err(1,"fork find");

	if(find_pid == 0){
		close(fd1[0]);

		if(dup2(fd1[1],1) == -1) err(1,"dup2 find");
		if(execlp("find","find",argv[1],"-type","f","-printf","%T@\t%P\n",NULL) == -1){
			err(1,"execlp find");
		}
	}
	close(fd1[1]);

	if(dup2(fd1[0],0) == -1) err(1,"dup2 1 sort");

	if((sort_pid = fork()) == -1) err(1,"fork sort");

	if(sort_pid == 0){
		close(fd2[0]);
		if(dup2(fd2[1],1) == -1) err(1,"dup2 2 sort");
		if(execlp("sort","sort","-n","-k","1",NULL) == -1){
			err(1,"execlp sort");
		}
	}
	close(fd2[1]);

	if(dup2(fd2[0],0) == -1) err(1,"dup2 2 cut");

	if((head_pid = fork()) == -1) err(1,"fork head");

	if (head_pid == 0){
		close(fd3[0]);

		if(dup2(fd3[1],1) == -1) err(1,"dup2 3 head");
		
		if(execlp("head","head","-n","1",NULL) == -1){
			err(1,"execlp head");
		}
	}
	close(fd3[1]);
	if(dup2(fd3[0],0) == -1) err(1,"dup2 cut");

	if(execlp("cut","cut","-d","\t","-f","2",NULL) == -1){
		err(1,"execlp cut");
	}

	exit(EXIT_SUCCESS);
}