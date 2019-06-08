/* 
Реализирайте команда cp, работеща с произволен брой подадени входни параметри.
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

int is_reg_file(const char* path){
	struct stat path_stat;
	stat(path,&path_stat);
	return S_ISREG(path_stat.st_mode);
}

int is_dir(const char* path){
	struct stat path_stat;
	stat(path,&path_stat);
	return S_ISDIR(path_stat.st_mode);
}

int main(int argc, char* argv[]){
	char* destination;
	destination = argv[argc-1];
	int file_desc1;
	int file_desc2;

	if(is_reg_file(destination) != 0){
		for(int i=1; i<argc-1; i++){
			file_desc1 = open(argv[i],O_RDONLY);
			file_desc2 = open(destination,O_WRONLY,0644);
			char c;

			if(file_desc1 == -1){
				printf("ERROR: %s\n",strerror(errno));
				exit(EXIT_FAILURE);
			}
			
			while(read(file_desc1,&c,1)){
				write(file_desc2,&c,1);
			}
			close(file_desc1);
			close(file_desc2);
		
		}	
	}

	if(is_dir(destination) != 0){
		for(int i=1; i<argc-1; i++){
			char *file_destination;
			file_desc1 = open(argv[i],O_RDONLY);
			file_destination = strcat(destination,argv[i]);
			file_desc2 = open(file_destination,O_CREAT|O_WRONLY,0644);

			char c;


			if(file_desc1 == -1){
				printf("ERROR: %s\n",strerror(errno));
				exit(EXIT_FAILURE);
			}

			
			while(read(file_desc1,&c,1)){
				write(file_desc2,&c,1);
			}
			close(file_desc1);
			close(file_desc2);
		}	
	}
	printf("Success!\n");
	exit(0);
}
