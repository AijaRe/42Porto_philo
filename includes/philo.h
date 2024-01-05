/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arepsa <arepsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 14:33:27 by arepsa            #+#    #+#             */
/*   Updated: 2024/01/05 19:11:21 by arepsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include <limits.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_prog t_prog;

typedef struct s_input
{
    int nbr_philos;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int nbr_meals;
}               t_input;

typedef struct s_fork
{
	pthread_mutex_t	fork_mtx;
	int	fork_id;
}				t_fork;

typedef struct s_philo
{
	pthread_t	thread_id;
	int			philo_id;
	t_fork		fork_1st;
	t_fork		fork_2nd;
	long		last_meal_time;
	int			meal_count;
	pthread_mutex_t	philo_mtx;
	t_prog		*prog;
}				t_philo;

typedef struct s_prog
{
   t_input  input;
   t_philo	*philos;
   t_fork	*forks;
   long		start_time;
   bool		end_prog;
   bool		all_threads_ready;
   pthread_mutex_t prog_mtx;
}				t_prog;

int check_init_errors(int argc, char **argv);

/* prog_init */
long	get_time(void);
void    prog_init(t_prog *prog);

/* action */
void  *start_dinner(t_prog *prog);

/* utils */
int     ft_strlen(char *str);
bool    ft_isspace(char c);
int     ft_error(char *str);
long	ft_atol(char *str);
void	*safe_malloc(size_t bytes);

/* print_stuff */
void    print_s_input(t_input *input);
void    print_philo(t_philo *philo);

# endif