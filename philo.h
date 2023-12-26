/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arepsa <arepsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 14:33:27 by arepsa            #+#    #+#             */
/*   Updated: 2023/12/26 15:25:00 by arepsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>

typedef struct s_prog
{
    int philos_nbr;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int meals_nbr;
}				t_prog;

int    ft_error(char *str);
long	ft_atol(char *str);

# endif