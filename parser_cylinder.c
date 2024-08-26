/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cylinder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 14:51:25 by kaan              #+#    #+#             */
/*   Updated: 2024/08/26 15:02:17 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_cylinder_type_and_space(char **scene, int *parsed)
{
	if (!parse_string(scene, "cy", parsed))
		return (0);
	if (!parse_space(scene, parsed))
		return (0);
	return (1);
}

int	parse_cylinder_center_and_space(char **scene, t_vec *center, int *parsed)
{
	if (!parse_vector(scene, center, parsed))
		return (0);
	if (!parse_space(scene, parsed))
		return (0);
	return (1);
}

int	parse_cylinder_axis_and_space(char **scene, t_vec *axis, int *parsed)
{
	if (!parse_vector(scene, axis, parsed))
		return (0);
	if (!parse_space(scene, parsed))
		return (0);
	return (1);
}

int	parse_cylinder_diameter_and_space(char **scene,
	double *diameter, int *parsed)
{
	if (!parse_double(scene, diameter, parsed))
		return (0);
	if (!parse_space(scene, parsed))
		return (0);
	return (1);
}

int	parse_cylinder_height_and_space(char **scene, double *height, int *parsed)
{
	if (!parse_double(scene, height, parsed))
		return (0);
	if (!parse_space(scene, parsed))
		return (0);
	return (1);
}
