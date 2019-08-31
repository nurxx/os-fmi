#include <stdlib.h>
#include <err.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <stdio.h>

int main(int argc, char **argv){
	if(argc != 4){
		errx(1,"Invalid number of arguments.Usage: %s <patch.bin> <f1.bin> <f2.bin>",argv[0]);
	}
	int pf, f1, f2;
	pf = open(argv[1],O_RDONLY);
	if(pf == -1){
		err(1,"%s",argv[1]);
	}
	f1 = open(argv[2],O_RDONLY);
	if (f1 == -1){
		err(1,"%s",argv[2]);
	}
	f2 = open(argv[3],O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if(f2 == -1){
		err(1,"%s",argv[3]);
	}

	uint8_t buf[4096];
	ssize_t read_size = 0;
	while((read_size = read(f1,&buf,sizeof(buf))) > 0){
		if(write(f2,buf,read_size)!= read_size){
			err(1,"error writing to %s",argv[3]);
		}
	}
	close(f1);
	lseek(f2,0,SEEK_SET);
	struct{
		uint16_t offset;
		uint8_t orgbyte;
		uint8_t newbyte;
	}element;

	while(read(pd,&element,sizeof(element)) == sizeof(element)){
		printf("%04x %02x %02x \n",element.offset,element.orgbyte,element.newbyte);
		if(lseek(f2,element.offset,SEEK_SET) < 0){
			close(f2);
			err(1,"lseek %s to %04x failed",argv[2],element.offset);
		}

		if(read(f2,&byte,1) != 1){
			close(f2);
			err(1,"read from %s at %04x failed",argv[2],element.offset);
		}

		if(byte != element.orgbyte){
			close(f2);
			err(1,"byte in %s at %04x is different from %02x",argv[2].element.offset,element.orgbyte);
		}
		lseek(f2,-1,SEEK_CUR);
		if(write(f2,&element.newbyte,1) != 1){
			err(1,"write i %s at %04x of %02x failed",argv[2],element.offset,element.newbyte);
		}
	}
	close(f2);
	close(f1);

	exit(0);
}