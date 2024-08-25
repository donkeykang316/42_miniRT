/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_util_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 16:28:32 by kaan              #+#    #+#             */
/*   Updated: 2024/08/25 18:04:35 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_light(char **_scene, t_world *world, int *total)
{
	char	*scene;
	int		parsed;
	t_light	light;

	scene = *_scene;
	parsed = 0;
	if (!parse_char(&scene, 'L', &parsed))
		return (0);
	if (!parse_space(&scene, &parsed))
		return (0);
	if (!parse_vector(&scene, &light.position, &parsed))
		return (0);
	if (!parse_space(&scene, &parsed))
		return (0);
	if (!parse_double(&scene, &light.intensity, &parsed))
		return (0);
	if (!parse_space(&scene, &parsed))
		return (0);
	if (!parse_color(&scene, &light.color, &parsed))
		return (0);
	if (light.intensity < 0 || light.intensity > 1)
		return (0);
	add_light(world, light);
	*total += parsed;
	*_scene += parsed;
	return (parsed);
}

int	parse_string(char **scene, char *str, int *total)
{
	int	parsed;

	parsed = 0;
	while (str[parsed] && (*scene)[parsed] && str[parsed] == (*scene)[parsed])
		parsed++;
	if (str[parsed])
		return (0);
	*scene += parsed;
	*total += parsed;
	return (parsed);
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
	if (!parse_string(&scene, "sp", &parsed))
		return (0);
	if (!parse_space(&scene, &parsed))
		return (0);
	if (!parse_vector(&scene, &obj.u_value.sphere.center, &parsed))
		return (0);
	if (!parse_space(&scene, &parsed))
		return (0);
	if (!parse_double(&scene, &diameter, &parsed))
		return (0);
	if (!parse_space(&scene, &parsed))
		return (0);
	if (!parse_color(&scene, &obj.material.albedo, &parsed))
		return (0);
	if (diameter < 0)
		return (0);
	obj.u_value.sphere.radius = diameter / 2;
	add_object(world, obj);
	*total += parsed;
	*_scene += parsed;
	return (parsed);
}

int	parse_cylinder(char **_scene, t_world *world, int *total)
{
	char		*scene;
	int			parsed;
	double		diameter;
	t_object	obj;

	scene = *_scene;
	parsed = 0;
	obj.type = OBJECT_TYPE_CYLINDER;
	obj.material = default_material();
	if (!parse_string(&scene, "cy", &parsed))
		return (0);
	if (!parse_space(&scene, &parsed))
		return (0);
	if (!parse_vector(&scene, &obj.u_value.cyllinder.center, &parsed))
		return (0);
	if (!parse_space(&scene, &parsed))
		return (0);
	if (!parse_vector(&scene, &obj.u_value.cyllinder.axis, &parsed))
		return (0);
	if (!parse_space(&scene, &parsed))
		return (0);
	if (!parse_double(&scene, &diameter, &parsed))
		return (0);
	if (!parse_space(&scene, &parsed))
		return (0);
	if (!parse_double(&scene, &obj.u_value.cyllinder.height, &parsed))
		return (0);
	if (!parse_space(&scene, &parsed))
		return (0);
	if (!parse_color(&scene, &obj.material.albedo, &parsed))
		return (0);
	if (diameter < 0 || obj.u_value.cyllinder.height < 0
		|| length(obj.u_value.cyllinder.axis) != 1.)
		return (0);
	obj.u_value.cyllinder.radius = diameter / 2;
	add_object(world, obj);
	*total += parsed;
	*_scene += parsed;
	return (parsed);
}
