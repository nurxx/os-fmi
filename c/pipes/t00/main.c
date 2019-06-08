/* реализация на конвейера "ls | wc -l" */

#include <sys/types.h>
#define READ 0
#define WRITE 1
main (void)
{
	int pd[2], status;
	pid_t pid;
	pipe(pd);
	pid = fork( );
	if ( pid == 0 ) {
	/* in first child */
		close(1);
		dup(pd[WRITE]);
		close(pd[READ]);
		close(pd[WRITE]);
		execlp("ls", "ls", 0);
		perror("Cannot exec ls" );
		exit(1);
		}
	/* in parent */
	if ( pid == -1 ) {
		perror("Cannot fork first child");
		exit(1);
	}
	pid = fork();
	if ( pid == 0 ) {
	/* in second child */
		close(0);
		dup(pd[READ]);
		close(pd[READ]) ;
		close(pd[WRITE]) ;
		execlp("wc", "wc", "-l", 0);
		perror("Cannot exec wc");
		exit(1);
	}
	/* in parent */
		close(pd[READ]) ;
		close(pd[WRITE]);
		if ( pid == -1 ) {
		perror("Cannot f ork second child");
		exit(1); }
		}
		waitpid(pid, &s tatus, 0);
		printf("Parent after end o f pipe: status=%d\n", status);
		exit(0);
}
