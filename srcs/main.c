/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arepsa <arepsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 14:30:44 by arepsa            #+#    #+#             */
/*   Updated: 2024/01/20 10:47:02 by arepsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/* 
** convert times from milisec to microsec 
** if no meals are present, flag -1
*/
int	parse_input(t_input *input, char **argv)
{
	input->nbr_philos = ft_atol(argv[1]);
	if (input->nbr_philos == 0)
		return (ft_error("Invalid philo number\n"));
	input->time_to_die = ft_atol(argv[2]) * 1000;
	input->time_to_eat = ft_atol(argv[3]) * 1000;
	input->time_to_sleep = ft_atol(argv[4]) * 1000;
	if ((input->time_to_die < 0 || input->time_to_die > INT_MAX) 
		|| (input->time_to_eat < 0 || input->time_to_eat > INT_MAX)
		|| (input->time_to_sleep < 0 || input->time_to_sleep > INT_MAX))
		return (ft_error("Invalid time input\n"));
	if (argv[5])
	{
		input->nbr_meals = ft_atol(argv[5]);
		if (input->nbr_meals == 0)
			return (ft_error("Invalid meal number\n"));
	}
	else
		input->nbr_meals = -1;
	return (0);
}

int	main(int argc, char **argv)
{
	t_prog	prog;

	if (argc < 5 || argc > 6)
		return (ft_error("Wrong number of args!\n"));
	if (check_init_errors(argc, argv) == 1)
		return (1);
	if (parse_input(&prog.input, argv) == 1)
		return (1);
	prog_init(&prog);
	start_dinner(&prog);
	clean_all(&prog);
	return (0);
}
