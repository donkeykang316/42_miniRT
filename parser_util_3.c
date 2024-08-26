/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_util_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 16:28:32 by kaan              #+#    #+#             */
/*   Updated: 2024/08/26 15:02:36 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

int	parse_cylinder_color(char **scene, t_vec *color, int *parsed)
{
	if (!parse_color(scene, color, parsed))
		return (0);
	return (1);
}

int	parse_cylinder_properties(char **scene,
	t_object *obj, double *diameter, int *parsed)
{
	if (!parse_cylinder_type_and_space(scene, parsed))
		return (0);
	if (!parse_cylinder_center_and_space(scene,
			&obj->u_value.cylinder.center, parsed))
		return (0);
	if (!parse_cylinder_axis_and_space(scene,
			&obj->u_value.cylinder.axis, parsed))
		return (0);
	if (!parse_cylinder_diameter_and_space(scene, diameter, parsed))
		return (0);
	if (!parse_cylinder_height_and_space(scene,
			&obj->u_value.cylinder.height, parsed))
		return (0);
	if (!parse_cylinder_color(scene, &obj->material.albedo, parsed))
		return (0);
	return (1);
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
	if (!parse_cylinder_properties(&scene, &obj, &diameter, &parsed))
		return (0);
	if (diameter < 0 || obj.u_value.cylinder.height < 0)
		return (0);
	obj.u_value.cylinder.axis = normalize(obj.u_value.cylinder.axis);
	obj.u_value.cylinder.radius = diameter / 2;
	add_object(world, obj);
	*total += parsed;
	*_scene += parsed;
	return (parsed);
}
