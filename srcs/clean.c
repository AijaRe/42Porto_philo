/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 12:32:09 by marvin            #+#    #+#             */
/*   Updated: 2024/01/14 12:32:09 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	clean_all(t_prog *prog)
{
	int	i;

	i = 0;
	while (i < prog->input.nbr_philos)
	{
		pthread_mutex_destroy(&prog->philos[i].philo_mtx);
		pthread_mutex_destroy(&prog->forks[i].fork_mtx);
		i++;
	}
	pthread_mutex_destroy(&prog->prog_mtx);
	pthread_mutex_destroy(&prog->print_mtx);
	free(prog->philos);
	free(prog->forks);
}
