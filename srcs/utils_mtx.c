/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_mtx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arepsa <arepsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 18:05:33 by arepsa            #+#    #+#             */
/*   Updated: 2024/01/15 19:40:36 by arepsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

bool    get_all_threads_ready(t_prog *prog)
{
    bool    value;

    pthread_mutex_lock(&prog->prog_mtx);
    value = prog->all_threads_ready;
    pthread_mutex_unlock(&prog->prog_mtx);
    return (value);
}

bool get_philo_is_full(t_philo *philo)
{
    bool    value;

    pthread_mutex_lock(&philo->philo_mtx);
    value = philo->full;
    pthread_mutex_unlock(&philo->philo_mtx);
    return (value);
}

bool get_all_philos_are_full(t_prog *prog)
{
    bool    value;

    pthread_mutex_lock(&prog->prog_mtx);
    value = prog->all_philos_full;
    pthread_mutex_unlock(&prog->prog_mtx);
    return (value);
}

void    set_last_meal_time(t_philo *philo)
{
    pthread_mutex_lock(&philo->philo_mtx);
    philo->last_meal_time = get_time();
    pthread_mutex_unlock(&philo->philo_mtx);
}

void    increase_nbr_ready_threads(t_prog *prog)
{
    pthread_mutex_lock(&prog->prog_mtx);
    prog->nbr_ready_threads++;
    pthread_mutex_unlock(&prog->prog_mtx);
} 