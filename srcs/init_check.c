/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arepsa <arepsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 11:02:28 by arepsa            #+#    #+#             */
/*   Updated: 2024/01/20 10:42:36 by arepsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/* 
** Numeric arguments similar to atoi: can contain whitespaces,
** can contain one + or - sign and can contain
** non-numeric chars after the digits
*/
static int	check_non_numeric(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (i < argc)
	{
		if (argv[i][j] == '\0')
			return (1);
		while (argv[i][j] != '\0') 
		{
			while (ft_isspace(argv[i][j]))
				j++;
			if (argv[i][j] == '-' || argv[i][j] == '+')
				j++;
			if (argv[i][j] >= '0' && argv[i][j] <= '9')
				break ;
			else if (argv[i][j] < '0' || argv[i][j] > '9')
				return (1);
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}

static int	check_negatives(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (i < argc)
	{
		if (argv[i][j] == '\0')
			return (1);
		while (argv[i][j] != '\0') 
		{
			if (argv[i][j] == '-')
				return (1);
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}

static int	out_of_max_range(int argc, char **argv)
{
	long	num;
	int		i;

	i = 1;
	while (i < argc)
	{
		num = ft_atol(argv[i]);
		if (num > 2147483647)
			return (1);
		i++;
	}
	return (0);
}

int	check_init_errors(int argc, char **argv)
{
	if (check_non_numeric(argc, argv) == 1)
		return (ft_error("Input is not numeric!\n"));
	if (check_negatives(argc, argv) == 1)
		return (ft_error("Input is negative!\n"));
	if (out_of_max_range(argc, argv) == 1)
		return (ft_error("Input bigger than MAX_INT!\n"));
	return (0);
}
