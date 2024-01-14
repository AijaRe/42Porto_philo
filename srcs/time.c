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
int	ft_usleep(long time_usec)
{
	long	start;
	
	start = get_time();
	while ((get_time() - start) < (time_usec / 1000))
		usleep(500);
	return (0);
}
