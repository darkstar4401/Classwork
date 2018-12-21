//This program demonstrates the usage of named pipe between two related processes (parent and child).
//The pipe is only used as a unidirectional pipe.
//See also named_pipe2.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
 
void child(char *path)
{
	int fd;
	ssize_t num;
	char buf[] = "123456789";

	fd = open(path, O_WRONLY);//O_WRONLY effectively makes the pipe unidirectional
	if(fd==-1) {fprintf(stderr,"in child, open error=%d, msg=%s\n",errno,strerror(errno)); exit(-1);}
	//printf("in child, fd=%d, sizeof(buf)=%d, buf=%s\n",fd, sizeof(buf),buf);
	//sleep(2);//the parent will read the message no matter whether the child sleeps or not
	num=write(fd, buf, sizeof(buf));//writer will not start to write until reader has opened the named pipe; use "man 7 fifo" for more information
	printf("in child, write returned num=%lu, Child sent: %s\n",num, buf);
	close(fd);
}//child
 
void parent(char *path)
{
	int fd;
	ssize_t num;
	char buf[512];

	//sleep(1);
	fd = open(path, O_RDONLY);//O_RDONLY effectively makes the pipe unidirectional
	if(fd==-1) {fprintf(stderr,"in parent, open error=%d,msg=%s\n",errno,strerror(errno)); exit(-1);}
	//printf("in parent, sizeof(buf)=%d, fd=%d\n",sizeof(buf),fd);
	num=read(fd, buf, sizeof(buf));
	printf("in parent, read returned num=%lu, Parent received: %s\n", num,buf);
	close(fd);
	unlink(path);
}//parent
 
int main()
{
	//char *path = "/tmp/fifo";
	char path[1024];//used to store the absolute path of the file backing our named pipe
	if (getcwd(path, sizeof(path)) == NULL)
	{
		perror("getcwd() error");
		exit(0);
	}
	strcat(path,"/fifoTest");//now path may contain a string that looks like /home/student/Desktop/fifoTest
	pid_t pid;

	//set buffering method for file stream "stdout": characters are saved up until a newline is output
	setlinebuf(stdout);//see http://linux.die.net/man/3/setlinebuf
	//remove a link to a file
	unlink(path);//see http://linux.die.net/man/3/unlink
	//makes a FIFO special file (a named pipe) with name 'path'. 
	int r=mkfifo(path, 0600);//see http://linux.die.net/man/3/mkfifo or use "man 3 mkfifo" in Linux
	if(r==-1) {fprintf(stderr,"in main, mkfifo call error=%d, msg=%s\n",errno,strerror(errno)); exit(-1);}

	pid = fork();
	if(pid<0) {fprintf(stderr,"in main, fork call error=%d, msg=%s\n",errno,strerror(errno)); exit(-1);}
	else if (pid == 0) {
		child(path);//child process is the writing end
	} else {
		parent(path);//parent process is the reading end
	}
	//unlink(path);
	return 0;
}//main
