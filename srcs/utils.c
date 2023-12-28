/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arepsa <arepsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 11:04:06 by arepsa            #+#    #+#             */
/*   Updated: 2023/12/28 15:46:44 by arepsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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

bool    ft_isspace(char c)
{
    return((c >= 9 && c <= 13) || c == 32);
}

/* atol only for positive nbr */
long	ft_atol(char *str)
{
	int		i;
	long	nb;

	i = 0;
	nb = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			break ;
		nb = nb * 10;
		nb = nb + (str[i] - '0');
		i++;
	}
	return (nb);
}