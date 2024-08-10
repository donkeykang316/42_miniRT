/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_input_valid_0.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 20:33:50 by kaan              #+#    #+#             */
/*   Updated: 2024/08/10 05:37:56 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int    acl_counter(char alph)
{
	static int	a = 0;
	static int	c = 0;
	static int	l = 0;

    if (alph == 'A')
		a++;
	else if (alph == 'C')
		c++;
	else if (alph == 'L')
		l++;
	if (a > 1 || c > 1 || l > 1)
		return (error_msg("Ambient, Camera and Light can only be defined once"));
    return (0);
}

int	input_valid(char *line, int *nbr)
{
	if (acl_counter(line[0]))
		return (1);
	if (ft_strncmp(line, "A", 1) == 0)
		return (ambient_valid(line));
	else if (ft_strncmp(line, "C", 1) == 0)
		return (camera_valid(line));
	else if (ft_strncmp(line, "L", 1) == 0)
		return (light_valid(line));
	else if (ft_strncmp(line, "pl", 2) == 0)
		return (plane_valid(line, nbr));
	else if (ft_strncmp(line, "tr", 2) == 0)
		return (plane_valid(line, nbr));
	else if (ft_strncmp(line, "sp", 2) == 0)
		return (sphere_valid(line, nbr));
	else if (ft_strncmp(line, "cy", 2) == 0)
		return (cylinder_valid(line, nbr));
	else if (ft_strncmp(line, " ", 1) != 0)
		return (error_msg("invalid input"));
	return (-1);
}

int	ambient_valid(char *line)
{
	char		**token;

	token = ft_split(line, ' ');
	if (!param_nbr_valid(token, 3))
		return (doubleptr_error(token, "Ambient light must have 2 parameters"));
	if (ft_atof(token[1]) < 0 || ft_atof(token[1]) > 1)
		return (doubleptr_error(token, "Ambient light ratio must be between 0.0 and 1.0"));
	if (color_valid(token[2]))
	{
		free_double(token);
		return (1);
	}
	free_double(token);
	return (0);
}

int	camera_valid(char *line)
{
	char		**token;

	token = ft_split(line, ' ');
	if (!param_nbr_valid(token, 4))
		return (doubleptr_error(token, "Camera must have 3 parameters"));
	if (coord_valid(token[1]))
	{
		free_double(token);
		return (1);
	}
	if (orien_valid(token[2]))
	{
		free_double(token);
		return (1);
	}
	if (!ft_isfloat(token[3]))
		return (doubleptr_error(token, "FOV must be a number"));
	if (ft_atof(token[3]) < 0 || ft_atof(token[3]) > 180)
		return (doubleptr_error(token, "FOV must be between 0 and 180"));
	free_double(token);
	return (0);
}

int	light_valid(char *line)
{
	char		**token;

	token = ft_split(line, ' ');
	if (!param_nbr_valid(token, 4))
		return (doubleptr_error(token, "Light must have 3 parameters"));
	if (coord_valid(token[1]))
	{
		free_double(token);
		return (1);
	}
	if (!ft_isfloat(token[2]))
		return (doubleptr_error(token, "Light intensity must be a number"));
	if (ft_atof(token[2]) < 0 || ft_atof(token[2]) > 1)
		return (doubleptr_error(token, "Light intensity must be between 0.0 and 1.0"));
	if (color_valid(token[3]))
	{
		free_double(token);
		return (1);
	}
	free_double(token);
	return (0);
}
