/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_util_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 17:26:14 by kaan              #+#    #+#             */
/*   Updated: 2024/08/25 19:05:24 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec	sample_phong_brdf(t_vec incident, t_vec normal)
{
	t_smpphong	tmp;

	tmp.em = 0.5 / (PHONG_GLOSS + 1);
	tmp.es = 2 * PHONG_GLOSS * PHONG_MAX_ANGLE / (PHONG_GLOSS + 1);
	tmp.n = normalize(normal);
	tmp.lambert = add_vec_vec(tmp.n, random_normalize_vec());
	tmp.r = normalize(reflect(vec_neg(incident), tmp.n));
	if (random_double() * (tmp.em + tmp.es) < tmp.em)
		return (tmp.lambert);
	tmp.specular = add_vec_vec(tmp.r,
			mul_vec_double(random_on_hemisphere(tmp.r), PHONG_MAX_ANGLE));
	return (tmp.specular);
}

t_ray	new_ray(t_vec origin, t_vec direction)
{
	t_ray	ray;

	ray.origin = origin;
	ray.direction = direction;
	return (ray);
}

t_ray	ray_from_to(t_vec from, t_vec to)
{
	return (new_ray(from, sub_vec_vec(to, from)));
}

void	licotmp_init(t_licotmp *tmp, t_world *world, t_hit hit)
{
	tmp->light = &world->point_lights[tmp->i];
	tmp->light_ray = ray_from_to(hit.point, tmp->light->position);
	tmp->interval.min = 0.01;
	tmp->interval.max = length(tmp->light_ray.direction);
	tmp->obstacle = ray_cast(tmp->light_ray, tmp->interval, world);
}

t_vec	lighting_color(t_ray ray, t_hit hit, t_world *world)
{
	t_licotmp	tmp;

	tmp.i = 0;
	tmp.res = mul_vec_vec(hit.object->material.albedo,
			ambient_light(world->ambient_light));
	while (tmp.i < world->point_lights_len)
	{
		licotmp_init(&tmp, world, hit);
		if (tmp.obstacle.hit)
		{
			tmp.i++;
			continue ;
		}
		tmp.r_px = 0.1;
		tmp.intensity = pow(tmp.r_px, 2)
			/ (length_squared(tmp.light_ray.direction))
			* 255. * tan(tmp.light->intensity * M_PI / 2);
		tmp.point_brdf = cos_angle_between(vec_neg(ray.direction), hit.normal);
		tmp.res = add_vec_vec(tmp.res,
				mul_vec_double(mul_vec_vec(
						mul_vec_double(hit.object->material.albedo,
							tmp.point_brdf), tmp.light->color), tmp.intensity));
		tmp.i++;
	}
	return (tmp.res);
}
