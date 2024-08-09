/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_input_util.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 19:00:06 by kaan              #+#    #+#             */
/*   Updated: 2024/08/09 21:43:16 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	doubleptr_error(char **token, char *msg)
{
	free_double(token);
	return (error_msg(msg));
}

bool	param_nbr_valid(char **token, int nbr)
{
	int	i;

	i = 0;
	while (token[i])
		i++;
	if (i != nbr)
		return (false);
	return (true);
}

int	color_valid(char *line)
{
	char		**token;
	int			i;

	i = 0;
	token = ft_split(line, ',');
	while (token[i])
	{
		if (!ft_isfloat(token[i]))
			return (doubleptr_error(token, "Color input must be numbers"));
		i++;
	}
	if (i != 3)
		return (doubleptr_error(token, "Color must have 3 parameters"));
	i = 0;
	while (token[i])
	{
		if (ft_atof(token[i]) < 0 || ft_atof(token[i]) > 255)
			return (doubleptr_error(token, "Color parameters must be between 0 and 255"));
		i++;
	}
	free_double(token);
	return (0);
}

int	coord_valid(char *line)
{
	char		**token;
	int			i;

	i = 0;
	token = ft_split(line, ',');
	while (token[i])
	{
		if (!ft_isfloat(token[i]))
			return (doubleptr_error(token, "Coordinate input must be numbers"));
		i++;
	}
	if (i != 3)
		return (doubleptr_error(token, "Coordinate must have 3 parameters"));
	free_double(token);
	return (0);
}

int	orien_valid(char *line)
{
	char		**token;
	int			i;

	i = 0;
	token = ft_split(line, ',');
	while (token[i])
	{
		if (!ft_isfloat(token[i]))
			return (doubleptr_error(token, "Orientation input must be numbers"));
		i++;
	}
	if (i != 3)
		return (doubleptr_error(token, "Orientation must have 3 parameters"));
	i = 0;
	while (token[i])
	{
		if (ft_atof(token[i]) < -1 || ft_atof(token[i]) > 1)
			return (doubleptr_error(token, "Orientation parameters must be between -1 and 1"));
		i++;
	}
	free_double(token);
	return (0);
}
