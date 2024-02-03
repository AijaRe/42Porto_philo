# 42Cursus - Philosophers

## Resources

- [Code Vault Playlist](https://www.youtube.com/watch?v=d9s_d28yJq0&list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2)
- [Philosophers Visualiser - your friendly debugger](https://nafuka11.github.io/philosophers-visualizer/)
- [Jamshidbek's Materials and Video Tutorial](https://github.com/Jamshidbek2000/philosophers_42)
- [Oceano on Threads](https://medium.com/@jalal92/lets-discuss-threads-grab-a-coffee-ad4d4ebf7181)

## Program Arguments

```bash
./philo 3 800 200 200 [5]
```
`prog — nbr_of_philosophers — time_to_die — time_to_sleep — time_to_eat — [nbr_of_meals]`


number of meals - optional (in square brackets)

Time input is in miliseconds, usleep uses microseconds. Convert num * 1000.

All timestamps have to be > 60ms.

Program finishes when all philos are full (if nbr of meals are present) or when one dies.

## Time to Die

- For even philosophers (2-4-6..): `time_to_die = time_to_eat * 2 + 10` 
- For odd philosophers (1-3-5..): `time_to_die = time_to_eat + time_to_sleep + (time_to_eat * 2 - time_to_sleep aka time_to_think) + 10`
  
## Plan

1. Error check the argument count.
2. Read input from the argument line:
    - Error check for negatives and non-numeric.
        
        (make atoi style - trim spaces and one + sign, take into account numbers and ignore what follows)
        
    - Parse char to int
    - Error check int for > INT_MAX and < 0.
    - Fill the input data struct
3. Initialize data structs - prog, philos and forks (nulls and mallocs)
4. Protect forks with mutex
5. Assign forks to philosophers
6. Create threads (philosopher = thread). Wait for all threads to be created before starting dinner.
7. Start timer.
8. The eat - sleep - think sequence.
9. Create referee thread that monitors death or full philos. Also do thread syncro here.
10. Write precise timestamp_in_ms
11. Clean data on program finish.

## Norminette
This project has to be written in accordance with the Norm, which is the coding standard of the school 42.

The Norm includes:
- Forbidden: for, do...while, switch, case, goto, ternary operators and variable-length arrays 
- Maximum of 25 lines per function
- Maximum line length: 80 columns
- Maximum 4 parameters per function 
- Variable assignments and declarations must be on separate lines
- etc...
    
## Functions

- `printf`, `malloc`, `free`, `write`
- `memset`
   - **Purpose:** Sets a block of memory to a specific value.
   - **Example:** `memset(buffer, 0, sizeof(buffer));`
- `usleep`
   - **Purpose:** Suspends program execution for a specified number of microseconds.
   - **Example:** `usleep(1000000); // Sleep for 1 second`
- `gettimeofday`
   - **Purpose:** Retrieves the current date and time with microsecond precision.
   - **Example:** `gettimeofday(&timeval, NULL);`
- `pthread_create`
   - **Purpose:** Creates a new thread for concurrent execution.
   - **Example:** `pthread_create(&thread, NULL, myFunction, arg);`
- `pthread_detach`
   - **Purpose:** Marks a thread as detached, allowing its resources to be automatically released when it exits. With `pthread_detach()`, you set a thread to 'auto-clean' mode.
   - **Example:** `pthread_detach(thread);`
- `pthread_join`
   - **Purpose:** Waits for a specific thread to finish execution.
   - **Example:** `pthread_join(thread, NULL);`
When you call `pthread_join(tid, &result)`, the calling thread will be blocked until the thread with ID `tid` completes its execution. If the thread was terminated with `pthread_exit()` or just returned, it might have produced a result. This result is stored, and `pthread_join()` allows another thread to fetch this result.
If the result isn't fetched, it might be leaked (`pthread_detach()` also can be used to free the result). You can think of joining as a handshake between the finished thread and another thread.

- `pthread_mutex_init`
   - **Purpose:** Initializes a mutex (mutual exclusion) for synchronizing access to shared resources.
   - **Example:** `pthread_mutex_init(&mutex, NULL);`
- `pthread_mutex_destroy`
   - **Purpose:** Destroys a mutex, releasing associated resources.
   - **Example:** `pthread_mutex_destroy(&mutex);`
- `pthread_mutex_lock`
   - **Purpose:** Acquires a lock on a mutex, preventing other threads from entering a critical section.
   - **Example:** `pthread_mutex_lock(&mutex);`
- `pthread_mutex_unlock`
   - **Purpose:** Releases a previously acquired lock on a mutex, allowing other threads to enter a critical section.
   - **Example:** `pthread_mutex_unlock(&mutex);`


## Processes vs Threads

Processes have their own dedicated memory, while threads share the same memory space as the parent process. Threads are lightweight compared to processes.

- Thread Header: `#include <pthread.h>`
- Compile with `-lpthread`, e.g., `gcc your_source_file.c -o output_file -lpthread`

## Thread Management

- Threads run functions, so define the function before creating a thread.
- Use `pthread_join` to ensure proper termination.

## Challenges with Threads

While threads offer speed and shared memory advantages, they come with the challenge of potential data corruption if not handled properly. Mutual exclusion (Mutexes), semaphores, and other synchronization techniques are essential to avoid "race conditions."

A Mutex, short for Mutual EXclusion, acts like a lock, ensuring that only one thread can access the critical section at a time.

Flags to detect data races:

- The `-fsanitize=thread -g` flag can be added at compilation.

