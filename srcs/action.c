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

void  *lone_diner(t_prog *prog)
{
	printf("%ld %d is eating\n", get_time() - prog->start_time, prog->philos[0].philo_id);
	usleep(prog->input.time_to_die);
	printf("%ld %d is dead\n", get_time() - prog->start_time, prog->philos[0].philo_id);
	return (NULL);
}

void dinner_time(t_philo *philo)
{

}

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
			pthread_create(&prog->philos[i].thread_id, NULL, dinner_time, &prog->philos[i]);
			i++;
		}
	}
}