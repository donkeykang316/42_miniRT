/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_util_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 19:03:18 by kaan              #+#    #+#             */
/*   Updated: 2024/08/25 19:03:35 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec	ray_trace(t_ray ray, int depth, t_world *world)
{
	t_raytracetmp	tmp;

	if (depth <= 0)
		return (vec(0, 0, 0));
	tmp.interval.min = 0.01;
	tmp.interval.max = 1000;
	tmp.hit = ray_cast(ray, tmp.interval, world);
	if (!tmp.hit.hit)
		return (ambient_light(world->ambient_light));
	tmp.lighting = lighting_color(ray, tmp.hit, world);
	tmp.secondary_ray = new_ray(tmp.hit.point,
			sample_phong_brdf(ray.direction, tmp.hit.normal));
	tmp.to_reflect = ray_trace(tmp.secondary_ray, depth - 1, world);
	tmp.reflected = mul_vec_double(
			mul_vec_vec(tmp.to_reflect, tmp.hit.object->material.albedo),
			cos_angle_between(vec_neg(ray.direction), tmp.hit.normal));
	return (add_vec_vec(tmp.lighting, tmp.reflected));
}
