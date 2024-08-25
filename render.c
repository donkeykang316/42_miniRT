/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apago <apago@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:51:30 by andrei            #+#    #+#             */
/*   Updated: 2024/08/25 20:05:54 by apago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_hit	no_hit(void)
{
	t_hit	hit;

	ft_memset(&hit, 0, sizeof(hit));
	return (hit);
}

t_hit	hit_object(t_object *object, double distance, t_vec point, t_vec normal)
{
	t_hit	hit;

	hit.hit = true;
	hit.distance = distance;
	hit.point = point;
	hit.normal = normal;
	hit.object = object;
	return (hit);
}

t_hit	ray_cast_at(t_ray ray, t_interval interval, t_object *object)
{
	if (object->type == OBJECT_TYPE_SPHERE)
		return (ray_cast_sphere(ray, interval, object));
	if (object->type == OBJECT_TYPE_PLANE)
		return (ray_cast_plane(ray, interval, object));
	if (object->type == OBJECT_TYPE_CYLINDER)
		return (ray_cast_cylinder(ray, interval, object));
	return (no_hit());
}

t_hit	ray_cast(t_ray ray, t_interval interval, t_world *world)
{
	t_hit	closest;
	t_hit	hit;
	int		i;

	i = 0;
	closest = no_hit();
	closest.distance = INFINITY;
	while (i < world->objects_len)
	{
		hit = ray_cast_at(ray, interval, &world->objects[i]);
		if (hit.hit && (hit.distance < closest.distance))
			closest = hit;
		i++;
	}
	return (closest);
}


double	brdf(t_vec incident, t_vec reflected, t_vec normal)
{
	double	matt;
	double	angle;
	double	specular;

	if (dot_vec(reflected, normal) < 0)
		return (0);
	matt = 1 / (PHONG_GLOSS + 1);
	angle = angle_between(reflected, reflect(incident, normal));
	if (angle >= PHONG_MAX_ANGLE)
		return (matt);
	specular = (1 - angle / PHONG_MAX_ANGLE) * PHONG_GLOSS / (PHONG_GLOSS + 1);
	return (matt + specular);
}
