/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arepsa <arepsa@student.42porto.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 14:33:27 by arepsa            #+#    #+#             */
/*   Updated: 2024/06/30 18:11:07 by arepsa           ###   ########.fr       */
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

# define RESET  "\033[0m"
# define RED    "\033[1;31m"
# define GREEN  "\033[1;32m"
# define PINK   "\033[1;35m"
# define BLUE   "\033[1;34m"

typedef struct s_prog t_prog;

typedef enum e_msg
{
    HAS_TAKEN_A_FORK,
    IS_EATING,
    IS_SLEEPING,
    IS_THINKING,
    DIED     
}       t_msg;

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
	pthread_t   philo_th;
	int			philo_id;
	t_fork		*fork_1st;
	t_fork		*fork_2nd;
	long		last_meal_time;
	int			meal_count;
    bool        full;
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
   bool     all_philos_full;
   bool		all_threads_ready;
   int      nbr_ready_threads;
   pthread_t    monitor_th;
   pthread_mutex_t prog_mtx;
   pthread_mutex_t print_mtx;
}				t_prog;

int check_init_errors(int argc, char **argv);

/* prog_init */
long	get_time(void);
void    prog_init(t_prog *prog);

/* action */
void  *start_dinner(t_prog *prog);
bool	dinner_finished(t_prog *prog);

/* monitor */
void	*ft_monitor(void *prog_data);

/* printer */
void    print_msg(t_philo *philo, t_msg msg);

/* clean */
void	clean_all(t_prog *prog);

/* time */
long	get_time(void);
int     ft_usleep(long time_usec);

/* utils */
int     ft_strlen(char *str);
bool    ft_isspace(char c);
int     ft_error(char *str);
long	ft_atol(char *str);
void	*safe_malloc(t_prog *prog, size_t bytes);

/* utils_mtx */
bool    get_all_threads_ready(t_prog *prog);
bool get_philo_is_full(t_philo *philo);
bool get_all_philos_are_full(t_prog *prog);
void    set_last_meal_time(t_philo *philo);
void    increase_nbr_ready_threads(t_prog *prog);

/* print_stuff */
void    print_s_input(t_input *input);
void    print_philo(t_philo *philo);

# endif