/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_input_valid_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 21:48:22 by kaan              #+#    #+#             */
/*   Updated: 2024/08/09 22:00:32 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int plane_valid(char *line)
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
    return (0);
}

int cylinder_valid(char *line)
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
    return (0);
}