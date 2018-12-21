//This program demonstrates the usage of named pipe between two related processes (parent and child).
//The pipe is used as a bidirectional pipe.
//See also named_pipe.c where the pipe is used as a unidirectional pipe.
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
	char buf[] = "child_123456789";//message to be written
	char buf2[512];//buffer to store read message

	fd = open(path, O_RDWR);//O_RDWR makes the pipe bidirectional
	if(fd==-1) {fprintf(stderr,"in child, open error=%d,msg=%s\n",errno,strerror(errno)); exit(-1);}
	num=write(fd, buf, sizeof(buf));
	printf("in child, write returned num=%lu, Child sent: %s\n", num,buf);
	sleep(1);//sleep for one second to avoid the risk of previously written message in buf being read by the child itself
	num=read(fd, buf2, sizeof(buf2));
	printf("in child, read returned num=%lu, Child received: %s\n", num,buf2);
	close(fd);
	unlink(path);
}//child
 
void parent(char *path)
{
	int fd;
	ssize_t num;
	char buf[512];//buffer to store read message
	char buf2[]= "parent_abcde";//message to be written

	fd = open(path, O_RDWR);//O_RDWR makes the pipe bidirectional
	if(fd==-1) {fprintf(stderr,"in parent, open error=%d,msg=%s\n",errno,strerror(errno)); exit(-1);}
	num=read(fd, buf, sizeof(buf));
	printf("in parent read returned num=%lu, Parent received: %s\n", num,buf);
	//sleep(2);//the child will read the message in buf2 no matter whether the parent sleeps 2 seconds or not
	num=write(fd, buf2, sizeof(buf2));
	printf("in parent write returned num=%lu, Parent sent: %s\n", num,buf2);
	close(fd);
}//parent
 
int main()
{
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
	//makes a FIFO special file with name path.
	int r=mkfifo(path, 0600);//see http://linux.die.net/man/3/mkfifo or use "man 3 mkfifo" in Linux
	if(r==-1) {fprintf(stderr,"in main, mkfifo call error=%d, msg=%s\n",errno,strerror(errno)); exit(-1);}
	//Opening a FIFO for reading normally blocks until some other process opens the same FIFO for writing, and vice versa. See fifo(7) for non-blocking handling of FIFO special files.

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
