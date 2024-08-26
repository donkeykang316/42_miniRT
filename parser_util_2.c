/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_util_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 16:26:43 by kaan              #+#    #+#             */
/*   Updated: 2024/08/26 16:16:15 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_ambient_light(char **_scene, t_amblight *light, int *total)
{
	char	*scene;
	int		parsed;

	scene = *_scene;
	parsed = 0;
	if (!parse_char(&scene, 'A', &parsed))
		return (0);
	if (!parse_space(&scene, &parsed))
		return (0);
	if (!parse_double(&scene, &light->intensity, &parsed))
		return (0);
	if (!parse_space(&scene, &parsed))
		return (0);
	if (!parse_color(&scene, &light->color, &parsed))
		return (0);
	*_scene += parsed;
	*total += parsed;
	return (parsed);
}

int	parse_camera(char **_scene, t_camera_spec *camera, int *total)
{
	char	*scene;
	int		parsed;

	scene = *_scene;
	parsed = 0;
	if (!parse_char(&scene, 'C', &parsed))
		return (0);
	if (!parse_space(&scene, &parsed))
		return (0);
	if (!parse_vector(&scene, &camera->view_point, &parsed))
		return (0);
	if (!parse_space(&scene, &parsed))
		return (0);
	if (!parse_vector(&scene, &camera->direction, &parsed))
		return (0);
	if (!parse_space(&scene, &parsed))
		return (0);
	if (!parse_double(&scene, &camera->hfov, &parsed))
		return (0);
	*total += parsed;
	*_scene += parsed;
	return (parsed);
}

void	add_light(t_world *world, t_light light)
{
	t_light	*lights;

	lights = ft_calloc(world->point_lights_len + 1, sizeof(t_light));
	ft_memcpy(lights, world->point_lights,
		world->point_lights_len * sizeof(t_light));
	lights[world->point_lights_len] = light;
	if (world->point_lights)
		free(world->point_lights);
	world->point_lights = lights;
	world->point_lights_len++;
}

void	add_object(t_world *world, t_object object)
{
	t_object	*objects;

	objects = ft_calloc(world->objects_len + 1, sizeof(t_object));
	ft_memcpy(objects, world->objects, world->objects_len * sizeof(t_object));
	objects[world->objects_len] = object;
	if (world->objects)
		free(world->objects);
	world->objects = objects;
	world->objects_len++;
}
