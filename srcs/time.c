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
	{
		write(2, "gettimeofday error\n", 20);
		return -1;
	}
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

// upgraded usleep
int	ft_usleep(int usec)
{
	struct timeval start; 
	struct timeval current;
	long	elapsed_usec;

    if (gettimeofday(&start, NULL) == -1)
    {
        write(2, "gettimeofday error\n", 20);
        return -1;
    }

    while (1)
    {
        if (gettimeofday(&current, NULL) == -1)
        {
            write(2, "gettimeofday error\n", 20);
            return -1;
        }
        elapsed_usec = (current.tv_sec - start.tv_sec) * 1000000 +
                            (current.tv_usec - start.tv_usec);
        if (elapsed_usec >= usec)
            break;
        usleep(100);
    }
    return 0;
}
