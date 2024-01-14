/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 16:40:38 by marvin            #+#    #+#             */
/*   Updated: 2024/01/14 16:40:38 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/philo.h"

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

// upgraded usleep
int	ft_usleep(int usec)
{
	int	start;

	start = get_time();
	while ((get_time() - start) < usec)
		usleep(500);
	return (0);
}

/* int		ft_usleep(t_prog *prog, int time_usec)
{
	int	start;
	int	time_ms;

	time_ms = time_usec / 1000;
	start = get_time();
	while ((get_time() - start) < time_ms)
	{
		pthread_mutex_lock(&prog->prog_mtx);
		if (!dinner_finished(prog))
		{
			pthread_mutex_unlock(&prog->prog_mtx);
			usleep(500);
		}
		else
		{
			pthread_mutex_unlock(&prog->prog_mtx);
			break ;
		}
	}
	return (0);
} */