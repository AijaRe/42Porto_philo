/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 21:10:10 by marvin            #+#    #+#             */
/*   Updated: 2024/01/04 21:10:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/* 
** Odd number forced to think
** to ensure even distribution of eating times
*/
void	ft_think(t_philo *philo)
{
	long	t_eat;
	long	t_sleep;
	long	t_think;

	print_msg(philo, IS_THINKING);
	if (philo->prog->input.nbr_philos % 2 == 0)
		return ;
	t_eat = philo->prog->input.time_to_eat;
	t_sleep = philo->prog->input.time_to_sleep;
	t_think = (t_eat * 2) - t_sleep;
	if (t_think < 0)
		t_think = 0;
	ft_usleep(t_think * 0.5);
}

/* lock the forks
** update meal time -> restart time_to_die counter
** print the status and eat for estimated time
** update meal counter and check if full
** unlock the forks
 */
void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork_1st->fork_mtx);
	print_msg(philo, HAS_TAKEN_A_FORK);
	pthread_mutex_lock(&philo->fork_2nd->fork_mtx);
	print_msg(philo, HAS_TAKEN_A_FORK);
	pthread_mutex_lock(&philo->philo_mtx);
	philo->last_meal_time = get_time();
	philo->meal_count++;
	pthread_mutex_unlock(&philo->philo_mtx);
	print_msg(philo, IS_EATING);
	ft_usleep(philo->prog->input.time_to_eat);
	if (philo->prog->input.nbr_meals != -1 
		&& philo->meal_count == philo->prog->input.nbr_meals)
	{
		pthread_mutex_lock(&philo->philo_mtx);
		philo->full = true;
		pthread_mutex_unlock(&philo->philo_mtx);
	}
	pthread_mutex_unlock(&philo->fork_1st->fork_mtx);
	pthread_mutex_unlock(&philo->fork_2nd->fork_mtx);
}

void	dinner_sequence(t_philo *philo)
{
	while (!dinner_finished(philo->prog))
	{
		if (get_philo_is_full(philo))
			break ;
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);
	}
}

/* 
** small delay for even philos to give odds chance to grab forks
** update ready thread number to start the monitor
*/
void	*dinner_prep(void *philo_data)
{
	t_philo	*philo;

	philo = (t_philo *)philo_data;
	sync_threads(philo->prog);
	set_last_meal_time(philo);
	increase_nbr_ready_threads(philo->prog);
	if (philo->prog->input.nbr_philos == 1)
		lone_diner(philo);
	if (philo->philo_id % 2 == 0)
		usleep(philo->prog->input.time_to_eat / 2);
	dinner_sequence(philo);
	return (NULL);
}

/*  
** Thread create args: thread, thread attributes, function, function argument
** Dinner beginning time in milliseconds
*/
void	*start_dinner(t_prog *prog)
{
	int	i;

	i = 0;
	while (i < prog->input.nbr_philos)
	{
		pthread_create(&prog->philos[i].philo_th, NULL, 
			dinner_prep, &prog->philos[i]);
		i++;
	}
	pthread_mutex_lock(&prog->prog_mtx);
	prog->start_time = get_time();
	prog->all_threads_ready = true;
	pthread_mutex_unlock(&prog->prog_mtx);
	pthread_create(&prog->monitor_th, NULL, ft_monitor, prog);
	if (prog->input.nbr_meals != -1)
		check_if_all_full(prog);
	i = 0;
	while (i < prog->input.nbr_philos)
	{
		pthread_join(prog->philos[i].philo_th, NULL);
		i++;
	}
	pthread_join(prog->monitor_th, NULL);
	return (NULL);
}
