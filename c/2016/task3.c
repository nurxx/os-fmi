#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <err.h>

int main()
{
	int fd1,fd2,fd3;

	fd1 = open("f1",O_RDONLY);
	if(fd1 < 0) err(1,"Error while opening f1");
	fd2 = open("f2",O_RDONLY);
	if(fd2 < 0) err(1,"Error while opening f2");
	fd3 = open("f3",O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
	if(fd3 < 0) err(1,"Error while opening f3");

	uint32_t x[2], a;
	while(read(fd1,x,sizeof(x)) == sizeof(x)){
		off_t lpt;
		lpt = lseek(fd2,x[0]*sizeof(a),SEEK_SET);
		if(lpt < 0) err(1,"lseek error for file f1");
		for(uint32_t i=0; i < x[1]; i++){
			read(fd2,&a,sizeof(a));
			write(fd3,&a,sizeof(a));
		}
	}

	close(f1);
	close(f2);
	close(f3);

	exit(0);
}