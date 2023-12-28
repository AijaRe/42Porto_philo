#include "../includes/philo.h"

void    print_prog(t_prog *prog)
{
    printf("nbr philos: %d\n", prog->nbr_philos);
    printf("time to die: %d\n", prog->time_to_die);
    printf("time to eat: %d\n", prog->time_to_eat);
    printf("time to sleep: %d\n", prog->time_to_sleep);
    printf("mbr meals: %d\n", prog->nbr_meals);
}