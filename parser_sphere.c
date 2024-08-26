/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_sphere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 14:43:05 by kaan              #+#    #+#             */
/*   Updated: 2024/08/26 14:49:31 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_sphere_type_and_space(char **scene, int *parsed)
{
	if (!parse_string(scene, "sp", parsed))
		return (0);
	if (!parse_space(scene, parsed))
		return (0);
	return (1);
}

int	parse_sphere_center_and_space(char **scene, t_vec *center, int *parsed)
{
	if (!parse_vector(scene, center, parsed))
		return (0);
	if (!parse_space(scene, parsed))
		return (0);
	return (1);
}

int	parse_sphere_diameter_and_space(char **scene, double *diameter, int *parsed)
{
	if (!parse_double(scene, diameter, parsed))
		return (0);
	if (!parse_space(scene, parsed))
		return (0);
	return (1);
}

int	parse_sphere_color(char **scene, t_vec *color, int *parsed)
{
	if (!parse_color(scene, color, parsed))
		return (0);
	return (1);
}

int	parse_sphere(char **_scene, t_world *world, int *total)
{
	char		*scene;
	int			parsed;
	double		diameter;
	t_object	obj;

	scene = *_scene;
	parsed = 0;
	obj.type = OBJECT_TYPE_SPHERE;
	obj.material = default_material();
	if (!parse_sphere_type_and_space(&scene, &parsed))
		return (0);
	if (!parse_sphere_center_and_space(&scene,
			&obj.u_value.sphere.center, &parsed))
		return (0);
	if (!parse_sphere_diameter_and_space(&scene, &diameter, &parsed))
		return (0);
	if (!parse_sphere_color(&scene, &obj.material.albedo, &parsed))
		return (0);
	if (diameter < 0)
		return (0);
	obj.u_value.sphere.radius = diameter / 2;
	add_object(world, obj);
	*total += parsed;
	*_scene += parsed;
	return (parsed);
}
