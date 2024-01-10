/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_mtx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 18:05:33 by arepsa            #+#    #+#             */
/*   Updated: 2024/01/10 20:36:39 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

bool get_full_status(t_philo *philo)
{
    bool    value;

    pthread_mutex_lock(&philo->philo_mtx);
    value = philo->full;
    pthread_mutex_unlock(&philo->philo_mtx);
    return (value);
}

bool get_all_full_status(t_prog *prog)
{
    bool    value;

    //pthread_mutex_lock(&prog->prog_mtx);
    value = prog->all_philos_full;
    //pthread_mutex_unlock(&prog->prog_mtx);
    return (value);
}