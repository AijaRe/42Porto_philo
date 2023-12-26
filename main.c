/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arepsa <arepsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 14:30:44 by arepsa            #+#    #+#             */
/*   Updated: 2023/12/26 15:26:07 by arepsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int ft_strlen(char *str)
{
    int i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int    ft_error(char *str)
{
    write(2, str, ft_strlen(str));
    return(1);
}

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
			if (argv[i][j] == '-' || argv[i][j] == '+')
				j++;
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (1);
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}
static int  check_negatives(int argc, char **argv)
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

int check_init_errors(int argc, char **argv)
{
    if (check_non_numeric(argc, argv) == 1)
        return(ft_error("Input is not numeric!\n"));
    if (check_negatives(argc, argv) == 1)
        return(ft_error("Input is negative!\n"));
    if (out_of_max_range(argc, argv) == 1)
        return(ft_error("Input bigger than MAX_INT!\n"));
    return (0);
}

int main(int argc, char **argv)
{
    if (argc < 5 || argc > 6)
        return(ft_error("Wrong number of args!\n"));
    if (check_init_errors(argc, argv) == 1)
        return(1);
}