/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_light.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 14:37:06 by kaan              #+#    #+#             */
/*   Updated: 2024/08/26 14:40:57 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_light_type_and_space(char **scene, int *parsed)
{
	if (!parse_char(scene, 'L', parsed))
		return (0);
	if (!parse_space(scene, parsed))
		return (0);
	return (1);
}

int	parse_light_position_and_space(char **scene, t_light *light, int *parsed)
{
	if (!parse_vector(scene, &light->position, parsed))
		return (0);
	if (!parse_space(scene, parsed))
		return (0);
	return (1);
}

int	parse_light_intensity_and_space(char **scene, t_light *light, int *parsed)
{
	if (!parse_double(scene, &light->intensity, parsed))
		return (0);
	if (!parse_space(scene, parsed))
		return (0);
	return (1);
}

int	parse_light_color(char **scene, t_light *light, int *parsed)
{
	if (!parse_color(scene, &light->color, parsed))
		return (0);
	return (1);
}

int	parse_light(char **_scene, t_world *world, int *total)
{
	char	*scene;
	int		parsed;
	t_light	light;

	scene = *_scene;
	parsed = 0;
	if (!parse_light_type_and_space(&scene, &parsed))
		return (0);
	if (!parse_light_position_and_space(&scene, &light, &parsed))
		return (0);
	if (!parse_light_intensity_and_space(&scene, &light, &parsed))
		return (0);
	if (!parse_light_color(&scene, &light, &parsed))
		return (0);
	if (light.intensity < 0 || light.intensity > 1)
		return (0);
	add_light(world, light);
	*total += parsed;
	*_scene += parsed;
	return (parsed);
}
