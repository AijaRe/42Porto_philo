#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int x = 42;
int main()
{
    pid_t pid = fork(); // Creates a new process
  // child
    if (0 == pid)
    {
        x++;
        printf("Child process: Value of x = %d\n", x);
    }
  //parent
    else
    {
        wait(NULL); // Wait for child to finish
        printf("Parent process: Value of x = %d\n", x);
    }
}