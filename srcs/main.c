/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arepsa <arepsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 14:30:44 by arepsa            #+#    #+#             */
/*   Updated: 2023/12/28 16:14:37 by arepsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/* 
** convert times from milisec to microsec 
** if no meals are present, flag -1
*/
int    parse_input(t_prog *prog, char **argv)
{
    prog->nbr_philos = ft_atol(argv[1]);
    if ( prog->nbr_philos == 0)
        return (ft_error("Invalid philo number\n"));
    prog->time_to_die = ft_atol(argv[2]) * 1000;
    prog->time_to_eat = ft_atol(argv[3]) * 1000;
    prog->time_to_sleep = ft_atol(argv[4]) * 1000;
    if ((prog->time_to_die < 60000 || prog->time_to_die > 2147483) ||
        (prog->time_to_eat < 60000 || prog->time_to_eat > 2147483) ||
        (prog->time_to_sleep < 60000 || prog->time_to_sleep > 2147483))
        return (ft_error("Invalid time input\n"));
    if (argv[5])
	{
        prog->nbr_meals = ft_atol(argv[5]);
    	if (argv[5] == 0)
			return (ft_error("Invalid meal number\n"));
	}
	else
        prog->nbr_meals = -1;
	return (0);
}

int main(int argc, char **argv)
{
    t_prog  prog;
    
    if (argc < 5 || argc > 6)
		return(ft_error("Wrong number of args!\n"));
    if (check_init_errors(argc, argv) == 1)
		return(1);
	if (parse_input(&prog, argv) == 1)
        return (1);
	print_prog(&prog);
    return (0);
}