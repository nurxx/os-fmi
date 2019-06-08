/*

Напишете програма, която приема точно 2 аргумента. Първият може да бъде само --min, --max или --print (вижте man 3 strcmp). Вторият аргумент е двоичен файл, в който има записани цели неотрицателни двубайтови числа (uint16_t - вижте man stdint.h). Ако първият аргумент е:

    --min - програмата отпечатва кое е най-малкото число в двоичния файл.
    --max - програмата отпечатва кое е най-голямото число в двоичния файл.
    --print - програмата отпечатва на нов ред всяко число.

*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <err.h>
#include <string.h>
#include <stdint.h>
#include <fcntl.h>

int main(int argc, char* argv[])
{

	if (argc != 3) {
		errx(1,"Wrong arguments count\n");
	}

	if ((strcmp(argv[1],"--min") !=0 && strcmp(argv[1],"--max") !=0 && strcmp(argv[1],"--print")!=0)) {
		errx(2,"First argument must be '--min' , '--max' or '--print'");
	}
	
	int file_desc;
		
	uint16_t number;
	uint16_t max = 0;
	uint16_t min = 65535;
	
	if ((file_desc = open(argv[2],O_RDONLY)) == -1){
		errx(3,"Failed open binary file in read mode\n");
	}
	
	if (strcmp(argv[1],"--print")==0) {
		while(read(file_desc,&number,sizeof(number))){
			printf("%u\n",number);
		}
	}

	while (read(file_desc,&number,sizeof(number))){
		if (number < min){
			min=number;
		}
		else if (number > max){
			max=number;
		}
	}

	if (strcmp(argv[1],"--min")==0){
		printf("Min : %u\n",min);
	} 

	if (strcmp(argv[1],"--max")==0){
		printf("Max : %u\n", max);
	}
	
	close(file_desc);
	
	exit(EXIT_SUCCESS);
}
