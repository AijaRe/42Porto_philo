#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// create mutex - initialize - lock - unlock - destroy

int num = 0;
pthread_mutex_t mutex;

void	*routine()
{
	for (int i = 0; i < 1000000; i++)
	{
		//mutex lock - no other thread can do the action until 
		//the previous thread has finished
		pthread_mutex_lock(&mutex); 
		num++;
		//release the hold of action and let the next thread access it
		pthread_mutex_unlock(&mutex); 
	}
	return (NULL);
}

int	main (void)
{
	pthread_t t1, t2;
	pthread_mutex_init(&mutex, NULL); //initialize mutex
	
	if (pthread_create(&t1, NULL, &routine, NULL) != 0) //returns 0 on success
		return (1);
	if (pthread_create(&t2, NULL, &routine, NULL) != 0)
		return (2);
	if (pthread_join(t1, NULL) != 0) //wait for thread to finish execution
		return (3);
	if (pthread_join(t2, NULL) != 0)
		return (4);
	pthread_mutex_destroy(&mutex); //free mutex memory
	printf("Num: %d\n", num);
	return (0);
}

//compile with -pthread -fsanitize=thread