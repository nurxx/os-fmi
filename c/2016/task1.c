// Напишете програма на Ц, която приема параметър - име на (двоичен) файл с байтове.
// Програмата трябва да сортира файла

#include <stdio.h>
#include <stdint.h>
#include <err.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]){
	if (argc != 2){
		errx(1,"invalid number of arguments");
	}
	int fd;
	fd = open(argv[1],O_RDWR);
	if (fd == -1){
		err(1,"%s",argv[1]);
	}

	const size_t buf_size = 96321;
	uint8_t buf[buf_size];

	ssize_t read_size = 0;
	unsigned int stats[256] = {0};
	do{
		read_size = read (fd, &buf, sizeof(buf));
		if(read_size < 0){
			int saved_errno = errno;
			close(fd);
			errno = saved_errno;
			err(1,"%s",argv[1]);
		}
		for (unsigned int i=0; i<read_size ; i++){
			stats[buf[i]]++;
		}
	} while(read_size > 0);

	lseek(fd,0,SEEK_SET);

	for (unsigned int i=0; i<256; i++){
		uint8_t c = i;
		while(stats[i] > 0){
			if(write(fd,&c,1) != 1){
				int saved_errno = errno;
				close(fd);
				errno = saved_errno;
				err(1,"Error while writing");
			}
			stats[i]--;
		}
	}
	close(fd);
	exit(0);
}