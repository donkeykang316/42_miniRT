/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:20:46 by kaan              #+#    #+#             */
/*   Updated: 2024/08/25 14:31:57 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec	random_in_unit_sphere(void)
{
	t_vec	p;

	while (1)
	{
		p = random_vec_range(-1, 1);
		if (length_squared(p) < 1)
			return (p);
	}
}

t_vec	random_normalize_vec(void)
{
	return (normalize(random_in_unit_sphere()));
}

t_vec	random_on_hemisphere(t_vec normal)
{
	t_vec	on_unit_sphere;

	on_unit_sphere = random_in_unit_sphere();
	if (dot_vec(on_unit_sphere, normal) > 0.0)
		return (on_unit_sphere);
	return (vec(on_unit_sphere.x * -1,
			on_unit_sphere.y * -1, on_unit_sphere.z * -1));
}

double	linear_to_gamma(double linear_component)
{
	if (linear_component > 0)
		return (sqrt(linear_component));
	return (0);
}

void	write_color(int fd, t_vec pixel_color)
{
	t_vec	rgb;

	rgb = gamma_correct(pixel_color);
	dprintf(fd, "%d %d %d\n", (int)(rgb.x * 256),
		(int)(rgb.y * 256), (int)(rgb.z * 256));
}
