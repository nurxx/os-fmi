/*
Реализирайте команда cat, работеща с произволен брой подадени входни параметри.
*/

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc,char*argv[]){
	int file_desc;
	char c;

	for(int i=1 ;i<argc; i++){
		file_desc = open(argv[i],O_RDONLY);

		if(file_desc == -1){
			write(2,"Failed open file in read mode\n",30);
			exit(-1);
		}
		while(read(file_desc,&c,1)){
			write(1,&c,1);
		}
		close(file_desc);
	}

	exit(0);
}