/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboulkri <kboulkri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:34:51 by kboulkri          #+#    #+#             */
/*   Updated: 2024/01/30 14:55:40 by kboulkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	long	result;
	int	y;

	sign = 1;
	result = 0;
	i = 0;
	y = 1;
	while ((str[i] >= 8 && str[i] <= 13) || str[i] == 32 || str[i] == 13)
		i++;
	if (str[i] == 45 || str[i] == 43)
	{
		if (str[i] == 45)
			sign *= -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		result = result * 10 + str[i] - 48;
		i++;
	}
	if ((y * result) > 2147483647 || (y * result) < -2147483648)
		return(printf("Error : INT_MAX or INT_MIN"), 0);
	return (result * sign);
}

int ft_parse(char **argv)
{
	int i;
	int j;

	i = 1;
	while (argv[i])
	{	
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
				return (printf("Error on Argv[%d][%d]", i, j), 1);
			j++;

		}
		i++;
	}
	return (0);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
	{
		return (1);
	}
	return (0);
}
