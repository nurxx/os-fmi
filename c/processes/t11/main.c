/*

Да се напише програма на C, която получава като параметри от команден ред две команди (без параметри) и име на файл в текущата директория. Ако файлът не съществува, го създава. Програмата изпълнява командите последователно, по реда на подаването им. Ако първата команда завърши успешно, програмата добавя нейното име към съдържанието на файла, подаден като команден параметър. Ако командата завърши неуспешно, програмата уведомява потребителя чрез подходящо съобщение.

*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <err.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>



int main(int argc, char* argv[])
{
	if (argc != 4){
		errx(1,"Wrong arguments count\n");
		exit(EXIT_FAILURE);
	}

	int fd1;
	
	if( (fd1=open(argv[3],O_CREAT | O_WRONLY,0644)) == -1){
		errx(2,"Failed opening file in write mode\n");
		exit(EXIT_FAILURE);
	}

	int status;
	
	if( fork() > 0){
		wait(&status);
		if(WIFEXITED(status)){
			write(fd1,&argv[1][0],1);
			while(*argv[1]++ !='\0'){
 				write(fd1,&(*argv[1]),1);
			}
			execlp(argv[2],argv[2],(char*)NULL);
		}
		else {
			close(fd1);
			write(1,"Unsuccessful\n",16);
		}
	}
	else{
		execlp(argv[1],argv[1],(char*)NULL);
	}

	close(fd1);
	exit(EXIT_SUCCESS);
}
