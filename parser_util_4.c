/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_util_4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 16:29:45 by kaan              #+#    #+#             */
/*   Updated: 2024/08/25 18:04:49 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_plane(char **_scene, t_world *world, int *total)
{
	char		*scene;
	int			parsed;
	t_object	obj;

	scene = *_scene;
	parsed = 0;
	obj.type = OBJECT_TYPE_PLANE;
	obj.material = default_material();
	if (!parse_string(&scene, "pl", &parsed))
		return (0);
	if (!parse_space(&scene, &parsed))
		return (0);
	if (!parse_vector(&scene, &obj.u_value.plane.point, &parsed))
		return (0);
	if (!parse_space(&scene, &parsed))
		return (0);
	if (!parse_vector(&scene, &obj.u_value.plane.normal, &parsed))
		return (0);
	if (!parse_space(&scene, &parsed))
		return (0);
	if (!parse_color(&scene, &obj.material.albedo, &parsed))
		return (0);
	add_object(world, obj);
	*total += parsed;
	*_scene += parsed;
	return (parsed);
}

int	parse_world(char *scene, t_world *world)
{
	int	parsed;

	parsed = 0;
	ft_memset(world, 0, sizeof(t_world));
	while (1)
	{
		parse_space(&scene, &parsed);
		if (parse_ambient_light(&scene, &world->ambient_light, &parsed))
			continue ;
		if (parse_camera(&scene, &world->camera, &parsed))
			continue ;
		if (parse_light(&scene, world, &parsed))
			continue ;
		if (parse_sphere(&scene, world, &parsed))
			continue ;
		if (parse_cylinder(&scene, world, &parsed))
			continue ;
		if (parse_plane(&scene, world, &parsed))
			continue ;
		if (*scene == 0)
			break ;
		return (0);
	}
	return (parsed);
}

double	make_double(int whole, int fraction, int position)
{
	double	f;

	f = fraction;
	while (position > 0)
	{
		f /= 10.;
		position--;
	}
	return ((double)(whole) + f);
}
