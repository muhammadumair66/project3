#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>


void* division();
const int divider = 97 ;

pthread_mutex_t mutex_val = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t* condition = NULL;

int thread_counts;
long int start;
long int ending;
int count;

int* array1;
int *array2;

volatile int counts = 0;

double time1()

{

struct timeval tval;

gettimeofday( &tval, ( struct timezone * ) 0 );

return ( (double) (tval.tv_sec + (tval.tv_usec / 1000000.0)) );

}

double time2()

{

return ( (double) time(NULL) );

}

int main(int argc, char *argv[])
{
  
double thread1, thread2, thread3, thread4;

thread1 = time1();

thread2 = time2();

pthread_t* thread_id;
if(strcmp("-hw", argv[1]) == 0)
{
      printf("Hello world");
      exit(0);
}

if(argc != 4)
{
printf("Invalid Command Line Argument! \n Existing");
return 0;
}

start = atoi(argv[1]);
ending = atoi(argv[2]);
thread_counts = atoi(argv[3]);


condition = (pthread_cond_t*)malloc(sizeof(pthread_cond_t) * thread_counts);
thread_id = (pthread_t*)malloc(sizeof(pthread_t) * thread_counts);
array1 = (int*)malloc(sizeof(int) * thread_counts);
array2 = (int*)malloc(sizeof(int) * thread_counts);

for(int i=0; i<thread_counts; i++)
{
array1[i] = i;
pthread_create(&thread_id[i], NULL, division, (void*)&array1[i]);

}

for(int i=0; i<thread_counts; i++)
{
pthread_join(thread_id[i], NULL);
}
long int sum = 0;
for(int i=0; i<thread_counts; i++)
{
  
printf("Thread %d : %d\n", i, array2[i]);

sum += array2[i];
}

printf("TOTAL : %ld\n", sum);

thread3 = time1();
thread4 = time2();

printf("TIME : %lf %lf\n",thread3-thread1,thread4-thread2);

return 0;
}
void* division(void *p)
{
  
  
int turns = *(int*)p;
  
  
while(ending > 97)
{
pthread_mutex_lock(&mutex_val);
  
if (turns != counts) {
  
pthread_cond_wait(&condition[turns], &mutex_val);
  
}
  
ending = ending - divider ;
array2[turns] += 1;
  
  
if (counts < thread_counts - 1) {
counts++;
}
else {
counts = 0;
}
  
pthread_cond_signal(&condition[counts]);
pthread_mutex_unlock(&mutex_val);
  
}
  
return NULL;
  
}
