/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:20:58 by kaan              #+#    #+#             */
/*   Updated: 2024/08/25 17:49:38 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec	sample_square(void)
{
	t_vec	square;

	square = vec(random_double() - 0.5, random_double() - 0.5, 0);
	return (square);
}

t_ray	get_ray(t_camera camera, int i, int j)
{
	t_vec	offset;
	t_ray	ray;
	t_vec	pixel_sample;

	offset = sample_square();
	pixel_sample = add_vec_vec(camera.pixel00_loc,
			add_vec_vec(mul_vec_double(camera.pixel_delta_u, (i + offset.x)),
				mul_vec_double(camera.pixel_delta_v, (j + offset.y))));
	ray.origin = camera.center;
	ray.direction = sub_vec_vec(pixel_sample, ray.origin);
	return (ray);
}

t_vec	gamma_correct(t_vec pixel_color)
{
	double		r;
	double		g;
	double		b;
	t_interval	intensity;
	t_vec		result;

	r = linear_to_gamma(pixel_color.x);
	g = linear_to_gamma(pixel_color.y);
	b = linear_to_gamma(pixel_color.z);
	intensity.min = 0.000;
	intensity.max = 0.999;
	result.x = clamp(intensity, r);
	result.y = clamp(intensity, g);
	result.z = clamp(intensity, b);
	return (result);
}

t_vec	contrast(double value)
{
	return (vec(fmax(0, value), 0, fmax(0, -value)));
}

void	render(t_world *world, t_camera camera, t_image image)
{
	t_vec	pixel_color;
	t_ray	ray;
	int		i;
	int		j;

	i = 0;
	j = 0;

	world->camera.view_point = camera.center;
	camera_init(&camera, world->camera,
		camera.image_width, camera.image_height);
	camera.max_depth = 4;
	while (j < image.height)
	{
		i = 0;
		while (i < image.width)
		{
			ray = get_ray(camera, i, j);
			pixel_color = ray_trace(ray, camera.max_depth, world);
			image.data[j * image.width + i] = add_vec_vec(image.data[j
					* image.width + i], pixel_color);
			i++;
		}
		j++;
	}
}
