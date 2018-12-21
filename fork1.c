//demonstration of fork().
//before fork(), you only have one process; after a successful call to fork(), you get two duplicate processes each starting to execute the statements after fork().
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int value = 5;

int main(int argc, char *argv[])
{
	pid_t pid;

	pid = fork();
	if(pid<0) {fprintf(stderr,"fork failed\n"); exit(pid);}
	else if (pid == 0) { /* child process */
		value += 15;
		printf ("In CHILD process: value = %d\n",value);
		return 0;
	}
	else if (pid > 0) { /* parent process */
		wait(NULL);//wait for child process to finish
		printf ("In PARENT process: value = %d\n",value);//will print out 5, not the child's copy.
		return 0;
	}
}
/*
				P
				|
				|
			   fork()
			   / \
			  P   P2
*/
