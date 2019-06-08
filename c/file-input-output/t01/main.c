/* Копирайте съдържанието на файл1 във файл2 */
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
	if (argc != 3){
		write(2,"Incorrect arguments count\n",30);
		exit(-1);
	}

	int file_d1;
	int file_d2;
	char c;

	if ( ( file_d1 = open(argv[1], O_RDONLY) ) == -1 ) {
		write(2, "File failed to open in read mode\n", 33);
		exit(-1);
	}

	if ( ( file_d2 = open(argv[2], O_CREAT | O_WRONLY, 0644) ) == -1 ){
		write(2, "File failed to open in write mode\n", 34);
		close(file_d1);
		exit(-1);
	}

	while ( read(file_d1, &c, 1) ){
		write(file_d2, &c, 1);
	}

	close(file_d1);
	close(file_d2);
	exit(0);
}

