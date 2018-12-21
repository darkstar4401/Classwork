//another demonstration of usage of fork().
//Be sure to understand how many processes are created and how many pids are printed.
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()//getpid is a function that returns the process id of caller
{
	printf("%d\n",getpid());//executed 1 time: p1
	fork();
	printf("%d\n",getpid());//executed 2 times: p1, p2

	fork();
	printf("%d\n",getpid());//executed 4 times: p1, p2, p3, p4

	fork();
	printf("%d\n",getpid());//executed 8 times: p1 p5 p3 p6 p2 p7 p4 p8

	return 0;
}
/*
					   p1
					 /    \
				   /       \
				  p1        p2
				 / \      /   \
			   p1  p3    p2    p4
			  / \  / \   / \   / \
			 p1 p5 p3 p6 p2 p7 p4 p8
*/