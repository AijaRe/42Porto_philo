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

/* return the end_prog flag */
bool	dinner_finished(t_prog *prog)
{
	bool value;

	//pthread_mutex_lock(&prog->prog_mtx);
	value = prog->end_prog;
	//pthread_mutex_unlock(&prog->prog_mtx);
	return (value);
}

/* wait until threads are created */
void	sync_threads(t_prog *prog)
{
	bool result;

	while (1)
	{
		pthread_mutex_lock(&prog->prog_mtx);
		result = prog->all_threads_ready;
		pthread_mutex_unlock(&prog->prog_mtx);
		if (result == true)
			break;
	}
}

void  *lone_diner(t_prog *prog)
{
	long	start_time;
	long	time;

	start_time = get_time();
	time = 0;

	printf("%ld %d has taken a fork\n", time, prog->philos[0].philo_id);
	usleep(prog->input.time_to_die);
	time = (get_time() - start_time);
	printf("%ld %d died\n", time, prog->philos[0].philo_id);
	printf("Philo can't live alone...");
	return (NULL);
}

/* void dinner_time(t_philo *philo)
{
	sync_threads(philo->prog);
	while (!dinner_finished(philo->prog))
	{
		if (prog->all_philos_full)
			break;
		eat()
		sleep()
		think()
	}

} */

/*  
** Thread create args: thread, thread attributes, function, function argument
** Dinner beginning time in milliseconds
*/
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
	//pthread_mutex_lock(&prog->prog_mtx);
	prog->all_threads_ready = true;
	//pthread_mutex_unlock(&prog->prog_mtx);
	prog->start_time = get_time();
	i = 0;
	while (i < prog->input.nbr_philos)
	{
		pthread_join(prog->philos[i].philo_id, NULL);
		i++;
	}
	return (NULL);
}