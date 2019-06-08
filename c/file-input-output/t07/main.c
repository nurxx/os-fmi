/*

Koпирайте файл /etc/passwd в текущата ви работна директория и променете разделителят на копирания файл от ":", на "?"

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <err.h>
#include <libgen.h>

int main(){

	char *src_file = "/etc/passwd";
	char *dest_file = basename("/etc/passwd");
	
	int fd1;
	int fd2;
	char c;
	
	if ((fd1 = open(src_file,O_RDONLY)) == -1) {
		errx(2,"Failed reading /etc/passwd\n");
	}
	
	if ((fd2 = open(dest_file,O_CREAT|O_WRONLY,0644)) == -1){
		errx(3,"Failed open destination file\n");
		close(fd1);
	}
	
	while (read(fd1,&c,1)){
		if(c == ':'){
			c='?';
		}
		write(fd2,&c,1);	
	}

	close(fd1);
	close(fd2); 
	exit(EXIT_SUCCESS);
}
