/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arepsa <arepsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 17:28:20 by arepsa            #+#    #+#             */
/*   Updated: 2024/01/18 18:00:13 by arepsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/* 
** timestamp_in_ms X has taken a fork
** timestamp_in_ms X is eating
** timestamp_in_ms X is sleeping
** timestamp_in_ms X is thinking
** timestamp_in_ms X died
*/

void    print_msg(t_philo *philo, t_msg msg)
{
    long timestamp;

    if (get_philo_is_full(philo))
        return ;
    timestamp = get_time() - philo->prog->start_time;
    pthread_mutex_lock(&philo->prog->print_mtx);
    if (!dinner_finished(philo->prog)) //probably need to be on each if condition
    {
        if (msg == HAS_TAKEN_A_FORK)
            printf("%ld %d has taken a fork\n", timestamp, philo->philo_id);
        else if (msg == IS_EATING)
            printf(GREEN"%ld %d is eating\n"RESET, timestamp, philo->philo_id);
        else if (msg == IS_SLEEPING)
            printf("%ld %d is sleeping\n", timestamp, philo->philo_id);
        else if (msg == IS_THINKING)
            printf("%ld %d is thinking\n", timestamp, philo->philo_id);
    }
    else if (msg == DIED)
        printf("%ld %d died\n", timestamp, philo->philo_id);
    pthread_mutex_unlock(&philo->prog->print_mtx);
}

