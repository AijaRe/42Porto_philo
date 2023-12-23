#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int num = 0;
pthread_mutex_t mutex;

void	*routine()
{
	for (int i = 0; i < 1000; i++)
	{
		pthread_mutex_lock(&mutex); 
		num++;
		pthread_mutex_unlock(&mutex); 
	}
	return (NULL);
}

int	main (void)
{
	pthread_t threads[4];
	pthread_mutex_init(&mutex, NULL); 

	//create threads in a loop
	for (int i = 0; i < 4; i++)
	{
		if (pthread_create(&threads[i], NULL, &routine, NULL) != 0)
		{
			perror ("thread create error: ");
			return (1);
		}
		printf ("Thread %d has started\n", i);
	}
	//close threads in a separate loop
	for (int i = 0; i < 4; i++)
	{
		if (pthread_join(threads[i], NULL) != 0) 
		{
			perror ("thread join error: ");
			return (2);
		}
		printf ("Thread %d has finished\n", i);
	}
	pthread_mutex_destroy(&mutex); 
	printf("Num: %d\n", num);
	return (0);
}

//compile with -pthread