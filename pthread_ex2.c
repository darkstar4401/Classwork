/****************************************************************
This is a sample threaded program in C.  The main thread creates
4 child threads.  Each child thread simply prints out a message
before exiting.  Notice that the thread attributes have been set to joinable and
of system scope.
****************************************************************/
#include <stdio.h>
#include <pthread.h>
 
#define NUM_THREADS 4
 
void *thread_function( void *arg );
 
int main( void )
{
	int i, tmp;
	int arg[NUM_THREADS] = {0,1,2,3};

	pthread_t thread[NUM_THREADS];
	pthread_attr_t attr;

	// initialize and set the thread attributes
	pthread_attr_init( &attr );
	pthread_attr_setdetachstate( &attr, PTHREAD_CREATE_JOINABLE );
	pthread_attr_setscope( &attr, PTHREAD_SCOPE_SYSTEM );
	// creating threads
	for ( i=0; i<NUM_THREADS; i++ )
	{
		tmp = pthread_create( &thread[i], &attr, thread_function, (void *)&arg[i] );
		if ( tmp != 0 )
		{
			printf("Creating thread %d failed\n", i);
			return 1;
		}
	}

	// joining threads
	for ( i=0; i<NUM_THREADS; i++ )
	{
		tmp = pthread_join( thread[i], NULL );
		if ( tmp != 0 )
		{
			printf("Joing thread %d failed\n", i);
			return 1;
		}
	}
	return 0;
}

//***********************************************************
// 	This is the function each thread is going to run.  It simply asks
// 	the thread to print out a message.  Notice the pointer acrobatics.
//***********************************************************
void *thread_function( void *arg )
{
	int id;

	id = *((int *)arg);
	printf( "Hello from thread %d!\n", id );
	pthread_exit( NULL );
}
