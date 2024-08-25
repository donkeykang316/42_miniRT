/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:23:07 by kaan              #+#    #+#             */
/*   Updated: 2024/08/25 19:10:41 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	find_root1(double discriminant, double h, double a)
{
	double	sqrtd;
	double	root;

	sqrtd = sqrt(discriminant);
	root = (h - sqrtd) / a;
	return (root);
}

double	find_root2(double discriminant, double h, double a)
{
	double	sqrtd;
	double	root;

	sqrtd = sqrt(discriminant);
	root = (h + sqrtd) / a;
	return (root);
}

t_hit	ray_cast_sphere(t_ray ray, t_interval interval, t_object *object)
{
	t_raycassphtmp	tmp;

	tmp.oc = sub_vec_vec(object->u_value.sphere.center, ray.origin);
	tmp.a = length_squared(ray.direction);
	tmp.h = dot_vec(ray.direction, tmp.oc);
	tmp.c = length_squared(tmp.oc) - (object->u_value.sphere.radius
			* object->u_value.sphere.radius);
	tmp.discriminant = (tmp.h * tmp.h) - (tmp.a * tmp.c);
	if (tmp.discriminant < 0)
		return (no_hit());
	tmp.root = find_root1(tmp.discriminant, tmp.h, tmp.a);
	if (!surrounds(interval, tmp.root))
	{
		tmp.root = find_root2(tmp.discriminant, tmp.h, tmp.a);
		if (!surrounds(interval, tmp.root))
			return (no_hit());
	}
	tmp.hit_point = at_ray(ray, tmp.root);
	return (hit_object(object,
			tmp.root,
			tmp.hit_point,
			div_vec_double(sub_vec_vec(tmp.hit_point,
					object->u_value.sphere.center),
				object->u_value.sphere.radius)
		));
}
