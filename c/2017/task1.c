#include <err.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <stdio.h>

static off_t statx_size(const char *name){
	struct stat buf;
	if(stat(fname,&buf) == -1){
		err(1,"Cannot stat %s",fname);
	}
	if(!S_ISREG(buf.st_mode)){
		errx(1,"%s is not a regular file",fname);
	}
	return buf.st_size;
}

static void readx(const int fd, uint8_t* const buf, const size_t sz, const char* const fname){
	size_t left = sz;
	while (left > 0){
		const ssize_t n = read(fd,buf+sz-left,left);
		if(n == -1){
			err(1,"Could not read from %s", fname);
		} else if (n == 0){
			errx(1,"Unexpected EOF on %s",fname);
		}
		left -= n;
	}
}

static void writex(const int fd, const uint8_t const buf, const size_t sz,
	const char* const fname,const uint16_t offset){
	size_t left = sz;
	while (left > 0){
		const ssize_t n = write(fd, buf + sz - left, left);
		if(n == -1){
			err(1,"Could not write the change for offset %04x to %s", offset, fname);
		}else if (n == 0){
			errx(1,"Unexpected short write on %s",fname);
		}
		left -= n;
	}
}

int main(const int argc, const char* const argv[]){
	if(argc != 4){
		errx(1,"Invalid number of argumnets. Usage: %s <f1.bin> <f2.bin> <patch.bin>", argv[0]);
	}
	const off_t f1_size = statx_size(argv[1]);
	if (f1_size != statx_size(argv[2])){
		errx(1,"%s and %s have different file size",argv[1],argv[2]);
	}
	if (f1_size > UINT16_MAX){
		errx(1,"%s size %ld bigger than %d, could not process",argv[1],f1_size,UINT16_MAX);
	}

	const int f1 = open(argv[1], O_RDONLY);
	if(f1 == -1){
		err(1,"Could not open %s", argv[1]);
	}

	const int f2 = open(argv[2],O_RDONLY);

	if(f2 == -1){
		const int saved_errno = errno;
		close(f1);
		errno = saved_errno;
		err(1,"Could not open %s", argv[2]);
	}
	const int pf = open(argv[3], O_RRWR | O_CREAT | O_TRUNC , S_IRUSR | S_IWUSR);
	if (pf == -1){
		const int saved_errno = errno;
		close(f1);
		close(f2);
		errno = saved_errno;
		err(1,"Could not open %s", argv[3]);
	}
	struct {
		uint16_t offset;
		uint8_t orgbyte;
		uint newbyte;
	}__atribute__((packed)) element;

	for (element.offset = 0; element.offset < f1_size; element.offset += sizeof(element.orgbyte)){
		readx(f1,&element.orgbyte,sizeof(element.orgbyte),argv[1]);
		readx(f2,&element.newbyte, sizeof(element.newbyte),argv[2]);
		if(element.orgbyte != element.newbyte){
			writex(pf,(const uint8_t *)&element,sizeof(element),argv[3],element.offset);
		}
	}

	close(f1);
	close(f2);
	close(pf);

	return 0;
}	

