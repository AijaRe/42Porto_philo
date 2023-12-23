#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define THREAD_NUM 5

void    *roll_dice() {
    int value;
    int *result;

    // dynamic allocation to be able to return pointer to value
    result = malloc(sizeof(int)); 
    if (result == NULL) {
        perror("Memory allocation failed");
        return (NULL);
    }
    value = (rand() % 6) + 1;
    *result = value;
    printf("Thread pointer: %p\n", result);
    printf("Rolled: %d\n", value);
    return ((void *)result);
}
    

int     main(void) {
    int *result[THREAD_NUM];
    pthread_t thread[THREAD_NUM];
    srand(time(NULL));

    for (int i = 0; i < THREAD_NUM; i++){
        if (pthread_create(&thread[i], NULL, &roll_dice, NULL) != 0){
            return (1);
        }
        printf("Thread %d has started\n", i);
    }
    for (int i = 0; i < THREAD_NUM; i++) {
        //pthread_join second argument is void ** to result
        if (pthread_join(thread[i], (void **)&result[i]) != 0){
            return (2);
        }
        printf("Thread %d pointer: %p\n", i, result[i]);
        printf("Result thread %d: %d\n", i, *result[i]); // print value of the pointer
        free (result[i]); // allocated in roll_dice
    }
    return 0;
}

//compile with -pthread -fsanitize=thread