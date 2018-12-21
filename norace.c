//adaptation from race.c; using mutex to remove race conditions
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

//see http://pubs.opengroup.org/onlinepubs/007908775/xsh/pthread_mutex_init.html
//see http://pubs.opengroup.org/onlinepubs/007908775/xsh/pthread_mutex_lock.html
pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;
int c[2] = {0,0};

void *UpdateC(void *arg)
{
	int i;
	for(i=0;i<10000;i++)
	{
		pthread_mutex_lock(&count_mutex);//use mutex to ensure only one thread is allowed in the critical section at a time
		c[0]=(c[0]+1)%2;//c[0], c[1] will never be updated by more than one thread simultaneously
		c[1]=(c[1]+1)%2;
		pthread_mutex_unlock(&count_mutex);
	}
	return NULL;
}

int main(int argc, char *argv[])
{
	int rt,i;
	pthread_t t[2]; 
	
	for(i=0;i<2;i++)/* Create two threads */
	{
		rt=pthread_create( &t[i], NULL, UpdateC, NULL);
		if( rt!=0 )
		{	fprintf(stderr,"Thread %d creation failed: %d\n", i,rt); exit(0);}
	}

	for(i=0;i<2;i++)/* Wait for both threads to finish */
	{
		rt=pthread_join( t[i], NULL);
		if( rt!=0 )
		{	fprintf(stderr,"Wait for thread %d failed: %d\n", i,rt); exit(0);}
	}

	printf ("\t%d\t%d\n",c[0],c[1]);//due to removal of race conditions, c[0] and c[1] are guaranteed to be 0
	return 0;
}