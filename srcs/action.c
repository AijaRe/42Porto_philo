/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 21:10:10 by marvin            #+#    #+#             */
/*   Updated: 2024/01/04 21:10:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/* return the end_prog flag */
bool	dinner_finished(t_prog *prog)
{
	bool value;

	pthread_mutex_lock(&prog->prog_mtx);
	value = prog->end_prog;
	pthread_mutex_unlock(&prog->prog_mtx);
	return (value);
}

bool	all_philos_full(t_prog *prog)
{
	int i;

	i = 0;
	while (i < prog->input.nbr_philos)
	{
		pthread_mutex_lock(&prog->philos[i].philo_mtx);
		if (!prog->philos[i].full)
		{
			pthread_mutex_unlock(&prog->philos[i].philo_mtx);
			return (false);
		}
		pthread_mutex_unlock(&prog->philos[i].philo_mtx);
		i++;
	}
	return (true);
}

/* Check if all philosophers are full */
void check_if_all_full(t_prog *prog) 
{
	while (!dinner_finished(prog))
	{
		if (all_philos_full(prog))
		{
			pthread_mutex_lock(&prog->print_mtx);
			printf(PINK"All philos are full!\U0001F44C\n"RESET);
			pthread_mutex_unlock(&prog->print_mtx);
			pthread_mutex_lock(&prog->prog_mtx);
			prog->end_prog = true;
			pthread_mutex_unlock(&prog->prog_mtx);
			break ;
		}
	}	
}

/* wait until threads are created */
void	sync_threads(t_prog *prog)
{
	while (!get_all_threads_ready(prog))
		;
}

void	lone_diner(t_philo	*philo)
{
	print_msg(philo, HAS_TAKEN_A_FORK);
	while (!dinner_finished(philo->prog))
		usleep(100);
}

void	ft_think(t_philo *philo)
{
	print_msg(philo, IS_THINKING);
}

void	ft_sleep(t_philo *philo)
{
	print_msg(philo, IS_SLEEPING);
	usleep(philo->prog->input.time_to_sleep);
}

/* lock the forks
** update meal time -> restart time_to_die counter
** print the status and eat for estimated time
** update meal counter and check if full
** unlock the forks
 */
void ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork_1st->fork_mtx);
	print_msg(philo, HAS_TAKEN_A_FORK);
	pthread_mutex_lock(&philo->fork_2nd->fork_mtx);
	print_msg(philo, HAS_TAKEN_A_FORK);
	pthread_mutex_lock(&philo->philo_mtx);
	philo->last_meal_time = get_time();
	philo->meal_count++;
	pthread_mutex_unlock(&philo->philo_mtx);
	print_msg(philo, IS_EATING);
	usleep(philo->prog->input.time_to_eat);
	if (philo->prog->input.nbr_meals != -1 && philo->meal_count == philo->prog->input.nbr_meals)
	{
		pthread_mutex_lock(&philo->philo_mtx);
		philo->full = true;
		pthread_mutex_unlock(&philo->philo_mtx);
	}
	pthread_mutex_unlock(&philo->fork_1st->fork_mtx);
	pthread_mutex_unlock(&philo->fork_2nd->fork_mtx);
}

void	dinner_sequence(t_philo *philo)
{
	while (!dinner_finished(philo->prog))
	{
		if (get_philo_is_full(philo))
			break ;
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);
	}
}

/* 
** small delay for even philos to avoid deadlocks
** update ready thread number to start the monitor
*/
void	*dinner_prep(void *philo_data)
{
	t_philo *philo;
	philo = (t_philo *)philo_data;

	sync_threads(philo->prog);
	set_last_meal_time(philo);
	increase_nbr_ready_threads(philo->prog);
	if (philo->prog->input.nbr_philos == 1)
		lone_diner(philo);
	if(philo->philo_id % 2 == 0)
		usleep(philo->prog->input.time_to_eat / 2);
	dinner_sequence(philo);
	return (NULL);
}

/*  
** Thread create args: thread, thread attributes, function, function argument
** Dinner beginning time in milliseconds
*/
void  *start_dinner(t_prog *prog)
{
	int i;

	i = 0;
		while (i < prog->input.nbr_philos)
		{
			pthread_create(&prog->philos[i].philo_th, NULL, dinner_prep, &prog->philos[i]);
			i++;
		}
	pthread_mutex_lock(&prog->prog_mtx);
	prog->start_time = get_time();
	prog->all_threads_ready = true;
	pthread_mutex_unlock(&prog->prog_mtx);
	pthread_create(&prog->monitor_th, NULL, ft_monitor, prog);
	if (prog->input.nbr_meals != -1)
		check_if_all_full(prog);
	i = 0;
	while (i < prog->input.nbr_philos)
	{
		pthread_join(prog->philos[i].philo_th, NULL);
		i++;
	}
	pthread_join(prog->monitor_th, NULL);
	return (NULL);
}