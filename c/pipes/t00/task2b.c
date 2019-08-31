#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
	int waitStatus;
	char cmd[32];
	int i=0;


	while(1){
		write(1,"> ",2);
		while( (read(0,&cmd[i],1)) && cmd[i] !='\n' ){
			if(cmd[i] == ' ' || cmd[i] == '\t')
			{
				continue;
			}
			else{
				++i;
			}
		}
		if ( cmd[i] == '\n' ){
			cmd[i] = '\0';
		}
		if( strcmp(cmd,"exit") == 0){
			exit(EXIT_SUCCESS);
		}else{
			if(fork()){
				wait(&waitStatus);
				i=0;
			}else{
				if(execvp(cmd,cmd,NULL) < 0){
					printf("cannot execute %s\n",cmd);
					exit(1);
				}
			}
		}
	}
}