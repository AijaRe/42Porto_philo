#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void	*routine()
{
	printf("Test from thread\n");
	sleep (3); //test to see if threads run in parralel. should print 2 tests twice first
	printf("Ending thread\n");
	return (NULL);
}

int	main (void)
{
	pthread_t t1, t2;
	
	if (pthread_create(&t1, NULL, &routine, NULL) != 0) //returns 0 on success
		return (1);
	if (pthread_create(&t2, NULL, &routine, NULL) != 0)
		return (2);
	if (pthread_join(t1, NULL) != 0) //wait for thread to finish execution
		return (3);
	if (pthread_join(t2, NULL) != 0)
		return (4);
	return (0);
}

//compile with -pthread