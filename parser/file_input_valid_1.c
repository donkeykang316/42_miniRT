/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_input_valid_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 21:48:22 by kaan              #+#    #+#             */
/*   Updated: 2024/08/10 05:36:47 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	sphere_valid(char *line, int *nbr)
{
	char		**token;

	token = ft_split(line, ' ');
	if (!param_nbr_valid(token, 4))
		return (doubleptr_error(token, "Sphere must have 3 parameters"));
	if (coord_valid(token[1]))
	{
		free_double(token);
		return (1);
	}
	if (!ft_isfloat(token[2]))
		return (doubleptr_error(token, "Sphere radius must be a number"));
	if (ft_atof(token[2]) < 0)
		return (doubleptr_error(token, "Sphere radius must be positive"));
	if (color_valid(token[3]))
	{
		free_double(token);
		return (1);
	}
	free_double(token);
    *nbr += 1;
	return (0);
}

int plane_valid(char *line, int *nbr)
{
    char        **token;

    token = ft_split(line, ' ');
    if (!param_nbr_valid(token, 4))
        return (doubleptr_error(token, "Plane must have 3 parameters"));
    if (coord_valid(token[1]) && orien_valid(token[2]) && color_valid(token[3]))
    {
        free_double(token);
        return (1);
    }
    free_double(token);
    *nbr += 1;
    return (0);
}

int cylinder_valid(char *line, int *nbr)
{
    char        **token;

    token = ft_split(line, ' ');
    if (!param_nbr_valid(token, 6))
        return (doubleptr_error(token, "Cylinder must have 4 parameters"));
    if (coord_valid(token[1]) && orien_valid(token[2]) && color_valid(token[5]))
    {
        free_double(token);
        return (1);
    }
    if (!ft_isfloat(token[3]) && !ft_isfloat(token[4]))
    {
        free_double(token);
        return (1);
    }
    if (ft_atof(token[3]) < 0 || ft_atof(token[4]) < 0)
    	return (doubleptr_error(token, "Parameter must be positive"));
    free_double(token);
    *nbr += 1;
    return (0);
}