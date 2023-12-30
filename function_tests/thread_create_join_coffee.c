#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void *make_coffee(void *arg)
{
 printf("Making coffee...\n");
 sleep(2);
 printf("Coffee ready!\n");
 return (NULL);
}

void *make_pastry(void *arg)
{
 printf("Baking pastry...\n");
 sleep(3);
 printf("Pastry ready!\n");
 return (NULL);
}

int main(void)
{
 pthread_t coffee_thread;
 pthread_t pastry_thread;

 pthread_create(&coffee_thread, NULL, make_coffee, NULL);
 pthread_create(&pastry_thread, NULL, make_pastry, NULL);
 
 //Before handing the order to customer, i need to WAIT both threads
 pthread_join(coffee_thread, NULL);
 pthread_join(pastry_thread, NULL);
 
 printf("\n\tThx for coming to Starbucks!\n"
     "\there's the ☕️ 'n 🥐\n");
 return (0);
}