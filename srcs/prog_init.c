/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prog_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arepsa <arepsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 13:52:16 by arepsa            #+#    #+#             */
/*   Updated: 2024/01/05 20:01:12 by arepsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/* 
** The current time is expressed in elapsed seconds and microseconds 
** since 00:00:00, January 1, 1970 (Unix Epoch).
** On success, the gettimeofday() returns 0, failure -1
** Returns time in miliseconds
*/
long	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday error\n", 20);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void    init_forks(t_prog *prog)
{
    int i;

    i = 0;
    while (i < prog->input.nbr_philos)    
    {
        pthread_mutex_init(&prog->forks[i].fork_mtx, NULL);
        prog->forks[i].fork_id = i;
        i++;
    }
}
/* 
** For odd index philos first fork is the one with highest index
** For even index philos - opposite
** Solves roundtable last philosopher issue
** avoids deadlocks
*/
void    assign_forks(t_philo *philo, t_fork *forks, int i)
{
    int nbr_philos;

    nbr_philos = philo->prog->input.nbr_philos;
    philo->fork_1st = forks[(i + 1) % nbr_philos];
    philo->fork_2nd = forks[i];
    if (philo->philo_id % 2 == 0)
    {
        philo->fork_1st = forks[i];
        philo->fork_2nd = forks[(i + 1) % nbr_philos];   
    }
}

void    init_philos(t_prog *prog)
{
    int i;
    t_philo *philo;
    
    i = 0;
    while (i < prog->input.nbr_philos)
    {
        philo = prog->philos + i;
        philo->philo_id = i + 1;
        philo->meal_count = 0;
        philo->last_meal_time = 0;
        pthread_mutex_init(&philo->philo_mtx, NULL);
        philo->prog = prog;
        assign_forks(philo, prog->forks, i);
        i++;   
    }
}

void    prog_init(t_prog *prog)
{
    prog->end_prog = false;
    prog->all_threads_ready = false;
    pthread_mutex_init(&prog->prog_mtx, NULL);
    prog->philos = safe_malloc(prog->input.nbr_philos * sizeof(t_philo));
    prog->forks = safe_malloc(prog->input.nbr_philos * sizeof(t_fork));
    init_forks(prog);
    init_philos(prog);
}