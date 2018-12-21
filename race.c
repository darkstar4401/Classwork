//demonstration of race conditions
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

//global array shared by the two threads created in main
int c[2] = {0,0};//initialization with 0

void *RaceC(void *arg)
{
	int i;
	for(i=0;i<10000;i++)//you might need to change 10000 to a value up to 1,000,000,000 to observe non-deterministic behavior due to race conditions
	{   
		c[0]=(c[0]+1)%2;//c[0] and c[1] were initialized to 0;
		c[1]=(c[1]+1)%2;//after an even number (10000) of updates, c[0] and c[1] are supposed to be 0
	}
	return NULL;
}

int main(int argc, char *argv[])
{
	int rt,i;
	pthread_t t[2];
	
	for(i=0;i<2;i++)/* Create two threads */
	{
		rt=pthread_create( &t[i], NULL, RaceC, NULL);
		if( rt!=0 )
		{	fprintf(stderr,"Thread %d creation failed: %d\n", i,rt); exit(0);}
	}

	for(i=0;i<2;i++)/* Wait for both threads to finish */
	{
		rt=pthread_join( t[i], NULL);
		if( rt!=0 )
		{	fprintf(stderr,"Wait for thread %d failed: %d\n", i,rt); exit(0);}
	}
	printf ("\t%d\t%d\n",c[0],c[1]);//due to race conditions, c[0] or c[1] could be 1
	return 0;
}