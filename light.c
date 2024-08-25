/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 14:16:34 by kaan              #+#    #+#             */
/*   Updated: 2024/08/25 18:16:40 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	light_init(t_light *light)
{
	t_vec	position;
	double	intensity;

	position = vec(-2, 5, 0);
	intensity = 1.0;
	light->position = vec(position.x, position.y, position.z);
	light->intensity = intensity;
	light->color = vec(0.0 + intensity, 0.0 + intensity, 0.0 + intensity);
}

double	cos_angle_between(t_vec a, t_vec b)
{
	float	len;

	len = length(a) * length(b);
	if (len == 0)
		return (1);
	return (dot_vec(a, b) / len);
}

double	angle_between(t_vec a, t_vec b)
{
	return (acos(cos_angle_between(a, b)));
}
