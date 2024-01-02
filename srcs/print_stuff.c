#include "../includes/philo.h"

void    print_s_input(t_input *input)
{
    printf("nbr philos: %d\n", input->nbr_philos);
    printf("time to die: %d\n", input->time_to_die);
    printf("time to eat: %d\n", input->time_to_eat);
    printf("time to sleep: %d\n", input->time_to_sleep);
    printf("nbr meals: %d\n", input->nbr_meals);
}

void    print_philo(t_philo *philo)
{
    printf("philo id: %d\n", philo->philo_id);
    printf("1st fork id: %d\n", philo->fork_1st.fork_id);
    printf("2nd fork id: %d\n", philo->fork_2nd.fork_id);
    //pthread_t	thread_id;
    printf("last meal time: %ld\n", philo->last_meal_time);
    printf("meal count: %d\n", philo->meal_count);
    //printf("mutex lock: %d\n", philo->philo_mtx.__lock);
}