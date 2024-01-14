/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 19:04:06 by marvin            #+#    #+#             */
/*   Updated: 2024/01/13 19:04:06 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/* 
** wait for all threads to be ready before starting monitoring
** otherwise last meal time is not set yet and they die
*/
bool	get_all_threads_running(pthread_mutex_t *prog_mtx, int *nbr_threads,
		int nbr_philos)
{
	bool	value;

	value = false;
	pthread_mutex_lock(prog_mtx);
	if (*nbr_threads == nbr_philos)
		value = true;
	pthread_mutex_unlock(prog_mtx);
	return (value);
}

bool	philo_is_dead(t_philo *philo)
{
	long	time_passed;
	long	time_to_die;

	pthread_mutex_lock(&philo->philo_mtx);
	if (philo->full)
	{
		pthread_mutex_unlock(&philo->philo_mtx);
		return (false);
	}
	time_to_die = philo->prog->input.time_to_die / 1000;
	time_passed = get_time() - philo->last_meal_time;
	pthread_mutex_unlock(&philo->philo_mtx);
	if (time_passed > time_to_die)
		return (true);
	return (false);
}

/* 
** check if all philo threads are running
** if threads are not running, last meal time is not set yet
** check if anyone is dead
** check if all are full
*/
void	*ft_monitor(void *prog_data)
{
	t_prog	*prog;
	int		i;

	prog = (t_prog *)prog_data;
	
	while (!get_all_threads_running(&prog->prog_mtx,
			&prog->nbr_ready_threads, prog->input.nbr_philos))
		;
	while (!dinner_finished(prog))
	{
		i = 0;
		while (i < prog->input.nbr_philos && !dinner_finished(prog))
		{
			if (philo_is_dead(&prog->philos[i]))
			{
				pthread_mutex_lock(&prog->prog_mtx);
				prog->end_prog = true;
				pthread_mutex_unlock(&prog->prog_mtx);
				print_msg(&prog->philos[i], DIED);
			}
			i++;
		}
	}

	return (NULL);
}