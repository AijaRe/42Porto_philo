#include <stdio.h>
#include <pthread.h>

/*
* The RACE_CONDITION value is proportional to the Probability of it happening
* Try to run the code with different values
*/
#define RACE_CONDITION 100000
// 0 by default
int g_drinks_served;
/* uncomment mutex lines to see the impact */
//pthread_mutex_t mutex; 

void *serve_drink(void *arg)
{
 int i;
 i = 0;
 while (i++ < RACE_CONDITION)
 {
	//pthread_mutex_lock(&mutex); 
  	g_drinks_served++; 
	//pthread_mutex_unlock(&mutex); 
 }
 return (NULL);
}
int main(void)
{
 pthread_t waiter1;
 pthread_t waiter2;
 
 /* if(pthread_mutex_init(&mutex, NULL) != 0)
 {
  printf("Mutex initialization failed!\\n");
  return 1;
 } */
 pthread_create(&waiter1, NULL, serve_drink, NULL);
 pthread_create(&waiter2, NULL, serve_drink, NULL);
 pthread_join(waiter1, NULL);
 pthread_join(waiter2, NULL);
 //pthread_mutex_destroy(&mutex);
 printf("Total drinks served: %d\n", g_drinks_served);
 return (0);
}

//compile with -pthread -fsanitize=thread