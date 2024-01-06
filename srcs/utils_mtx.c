/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_mtx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arepsa <arepsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 18:05:33 by arepsa            #+#    #+#             */
/*   Updated: 2024/01/06 18:09:38 by arepsa           ###   ########.fr       */
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