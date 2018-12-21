#include <pthread.h>
#include <assert.h>
#include <stdio.h>

int numitems = 60;
char arr[61];
int numThreads=3;
void *gen_string(void *arg){
	int i;
	for(i=0;i<60;i++){
		arr[i]= i;
	}
}
void print_usage(void *arg){
	fprintf(stderr, "using:%s threads\n", arg);
}
void *split_work(){
	//numthread*numitems/numthreads
	int i = (numitems*numThreads)/numThreads;
	int j;
	for (j=0; j<i; i++){
		arr[j]=(int)arr[j]*2;
	}

}
int main(int argc, char **argv){
	numThreads = 3;
	pthread_t tid[numThreads];=
	for(i=0;i<numThreads; i++)
		pthread_create(&tid[i],NULL,split_work, NULL);
	for(i=0; i<numThreads; i++)
		pthread_join(tid[i],NULL);
	return 0;
}


