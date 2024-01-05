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

bool	dinner_finished(t_prog *prog)
{
	pthread_mutex_lock(&prog->prog_mtx);
	prog->end_prog = true;
	pthread_mutex_unlock(&prog->prog_mtx);
	return (true);
}

/* spinlock until threads are ready */
void	sync_threads(t_prog *prog)
{
	pthread_mutex_lock(&prog->prog_mtx);
	while (prog->all_threads_ready != true)
		;
	pthread_mutex_unlock(&prog->prog_mtx);
}

void  *lone_diner(t_prog *prog)
{
	long	start_time;
	long	time;

	start_time = get_time();
	time = 0;

	printf("%ld %d is eating\n", time, prog->philos[0].philo_id);
	usleep(prog->input.time_to_die);
	time = (get_time() - start_time);
	printf("%ld %d is dead\n", time, prog->philos[0].philo_id);
	return (NULL);
}

/* void dinner_time(t_philo *philo)
{
	sync_threads();

} */

/* Thread create args: thread, thread attributes, function, function argument */
void  *start_dinner(t_prog *prog)
{
	int i;

	i = 0;
	if (prog->input.nbr_philos == 1)
		lone_diner(prog);
	else
	{
		while (i < prog->input.nbr_philos)
		{
			//pthread_create(&prog->philos[i].thread_id, NULL, dinner_time, &prog->philos[i]);
			i++;
		}
	}
	pthread_mutex_lock(&prog->prog_mtx);
	prog->all_threads_ready = true;
	pthread_mutex_unlock(&prog->prog_mtx);
	return (NULL);
}