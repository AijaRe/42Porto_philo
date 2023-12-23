#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int odds[5] = {1,3,5,7,9};

void    *func(void *arg) {
    int i = *(int *)arg; // cast to int * and dereference
    printf("%d ", odds[i]);
    free (arg); // allocated in main
    return (NULL);
}

int main(void) {
    pthread_t thread[5];

    for (int i = 0; i < 5; i++) {
        int *x = malloc(sizeof(int));
        if (x == NULL) {
            perror("Memory allocation failed");
            exit(EXIT_FAILURE);
        }
        *x = i;
        // last parameter is pointer to an argument for function
        if (pthread_create(&thread[i], NULL, &func, x) != 0) {
            perror("Thread create error");
            exit(EXIT_FAILURE);
        }
    }
    for (int i = 0; i < 5; i++) {
        if (pthread_join(thread[i], NULL) != 0) {
            perror("Thread join error");
            exit(EXIT_FAILURE);
        }
    }
    return (0);
}

//compile with -pthread -fsanitize=thread
