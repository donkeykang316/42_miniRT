/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nbr_valid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 18:44:57 by kaan              #+#    #+#             */
/*   Updated: 2024/08/09 19:42:11 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	ft_isfloat(char *str)
{
	int	i;
	int	dot;

	i = 0;
	dot = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && str[i] != '.')
			return (false);
		if (str[i] == '.')
			dot++;
		i++;
	}
	if (dot > 1)
		return (false);
	return (true);
}

static double    atof_util(char *str, int i)
{
    double	res;
	double	dec;

    res = 0;
	dec = 0;
	while (str[i] && str[i] != '.')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	if (str[i] == '.')
		i++;
	while (str[i])
	{
		dec = dec * 10 + str[i] - '0';
		i++;
	}
    while (dec >= 1)
		dec /= 10;
	return (res += dec);
}

double	ft_atof(char *str)
{
	int		i;
	int		sign;

	i = 0;
	sign = 1;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;	
	return (sign * atof_util(str, i));
}
