/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arepsa <arepsa@student.42porto.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 11:04:06 by arepsa            #+#    #+#             */
/*   Updated: 2024/06/30 18:58:40 by arepsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int	ft_error(char *str)
{
	write (2, str, ft_strlen(str));
	return (1);
}

bool	ft_isspace(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

void	*safe_malloc(t_prog *prog, size_t bytes)

void	*safe_malloc(size_t bytes)
{
	void	*result;

	result = malloc(bytes);
	if (!result)
	{
		clean_all(prog);
		exit(EXIT_FAILURE);
		return (NULL);
	}
	return (result);
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
