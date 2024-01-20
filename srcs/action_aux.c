/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_aux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arepsa <arepsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 10:11:28 by arepsa            #+#    #+#             */
/*   Updated: 2024/01/20 18:15:05 by arepsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/* return the end_prog flag */
bool	dinner_finished(t_prog *prog)
{
	bool	value;

	pthread_mutex_lock(&prog->prog_mtx);
	value = prog->end_prog;
	pthread_mutex_unlock(&prog->prog_mtx);
	return (value);
}

bool	all_philos_full(t_prog *prog)
{
	int	i;

	i = 0;
	while (i < prog->input.nbr_philos)
	{
		pthread_mutex_lock(&prog->philos[i].philo_mtx);
		if (!prog->philos[i].full)
		{
			pthread_mutex_unlock(&prog->philos[i].philo_mtx);
			return (false);
		}
		pthread_mutex_unlock(&prog->philos[i].philo_mtx);
		i++;
	}
	return (true);
}

/* Check if all philosophers are full */
void	check_if_all_full(t_prog *prog)
{
	while (!dinner_finished(prog))
	{
		if (all_philos_full(prog))
		{
			pthread_mutex_lock(&prog->print_mtx);
			printf(PINK"All philos are full!\U0001F44C\n"RESET);
			pthread_mutex_unlock(&prog->print_mtx);
			pthread_mutex_lock(&prog->prog_mtx);
			prog->end_prog = true;
			pthread_mutex_unlock(&prog->prog_mtx);
			break ;
		}
	}
}

void	lone_diner(t_philo	*philo)
{
	print_msg(philo, HAS_TAKEN_A_FORK);
	while (!dinner_finished(philo->prog))
		usleep(100);
}
