// Напишете програма на С, която използвайки външни shell команди
// да извежда статистика за използването на различните shell-ове
// от потребителите, дефинирани в системата. Изходът да бъде сортиран
// във възходящ ред според брой използвания на shell-овете.

#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <err.h>
#include <fcntl.h>

int main(){
	int fd1[2];
	int fd2[2];
	int fd3[2];
	int fd4[2];

	pipe(fd1);
	pipe(fd2);
	pipe(fd3);
	pipe(fd4);

	pid_t cat_pid;
	pid_t cut_pid;
	pid_t sort_pid;
	pid_t uniq_pid;

	if ((cat_pid = fork()) == -1) err(1,"fork cat");

	if (cat_pid == 0){
		close(fd1[0]);

		if(dup2(fd1[1],1) == -1) err(1,"dup2 cat");
		if(execlp("cat","cat","/etc/passwd",NULL) == -1) err (1,"execlp cat");
	}

	close(fd1[1]);
	if(dup2(fd1[0],0) == -1) err(1,"dup2 cat parent");

	if((cut_pid = fork()) == -1) err(1,"fork cut");

	if(cut_pid == 0){
		close(fd2[0]);

		if(dup2(fd2[1],1) == -1) err(1,"dup2 cut");
		if(execlp("cut","cut","-d",":","-f","7",NULL) == -1) err(1,"execlp cut");
	}

	close(fd2[1]);
	if(dup2(fd2[0],0) == -1) err(1,"dup2 cut parent");

	if ((sort_pid = fork()) == -1) err(1,"fork sort");

	if (sort_pid == 0){
		close(fd3[0]);

		if(dup2(fd3[1],1) == -1) err(1,"dup2 sort");
		if(execlp("sort","sort",NULL)==-1) err(1,"execlp sort");
	}

	close(fd3[1]);
	if(dup2(fd3[0],0) == -1) err(1,"dup2 sort parent");

	if((uniq_pid = fork()) == -1) err(1,"fork uniq");

	if(uniq_pid == 0){
		close(fd4[0]);

		if(dup2(fd4[1],1) == -1) err(1,"dup2 uniq");
		if(execlp("uniq","uniq","-c",NULL) == -1) err(1,"execlp uniq");
	}
	close(fd4[1]);
	if(dup2(fd4[0],0) == -1) err(1,"dup2 uniq parent");

	if(execlp("sort","sort","-n",NULL) == -1) err(1,"execlp sort -n");

	exit(EXIT_SUCCESS);
}