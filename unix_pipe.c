//This program demonstrates the usage of ordinary pipes, which is unidirectional
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

#define BUFFER_SIZE 25
#define READ_END	0
#define WRITE_END	1

int main(void)
{
	char write_msg[BUFFER_SIZE] = "Greetings";
	char read_msg[BUFFER_SIZE];
	pid_t pid;
	int fd[2];

	/* create the pipe */
	if (pipe(fd) == -1) {//you can type "man 2 pipe" inside Linux to get help for the function "pipe"; or visit http://linux.die.net/man/3/pipe
		fprintf(stderr,"Pipe failed");
		return 1;
	}

	pid = fork();/* now fork a child process */
	if (pid < 0) {
		fprintf(stderr, "Fork failed");
		return 1;
	}
	else if (pid > 0) {  /* parent process */
		//sleep(2);//the child will read the message no matter whether the parent sleeps or not
		/* parent is used as a writer, so close the unused read end of the pipe */
		close(fd[READ_END]);//if you remove this line, the program might still work. However it is best practice to close unused fd. See https://stackoverflow.com/questions/19265191/why-should-you-close-a-pipe-in-linux

		/* write to the write end of the pipe */
		write(fd[WRITE_END], write_msg, strlen(write_msg)+1);
		printf("parent sent: %s\n",write_msg);

		/* close the write end of the pipe */
		close(fd[WRITE_END]);
	}
	else { /* child process */
		/* child is used as a reader, so close the unused write end of the pipe */
		close(fd[WRITE_END]);//if you remove this line, the program might still work. However it is best practice to close unused fd. See https://stackoverflow.com/questions/19265191/why-should-you-close-a-pipe-in-linux

		/* read from the read end of the pipe */
		read(fd[READ_END], read_msg, BUFFER_SIZE);
		printf("child received: %s\n",read_msg);

		/* close the read end of the pipe */
		close(fd[READ_END]);
	}

	return 0;
}
