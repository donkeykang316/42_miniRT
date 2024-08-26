/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_util_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 15:45:03 by kaan              #+#    #+#             */
/*   Updated: 2024/08/26 16:09:01 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_hit	construct_cap_hit(t_ray ray, t_object *obj,
	t_rndcapstmp *tmp, t_interval interval)
{
	tmp->hit.hit = true;
	tmp->hit.object = obj;
	tmp->hit.point = add_vec_vec(ray.origin,
			mul_vec_double(normalize(ray.direction), tmp->times));
	tmp->hit.distance = length(sub_vec_vec(tmp->hit.point, ray.origin));
	tmp->hit.normal = obj->u_value.cylinder.axis;
	if (dot_vec(tmp->hit.normal, ray.direction) > 0)
		tmp->hit.normal = vec_neg(tmp->hit.normal);
	if (!surrounds(interval, tmp->hit.distance))
		return (no_hit());
	return (tmp->hit);
}

t_hit	render_caps(t_ray ray, t_object *obj,
	t_raycascyltmp *ray_ca, t_interval interval)
{
	t_rndcapstmp	tmp;

	if (!compute_cap_intersection(ray, obj, ray_ca, &tmp))
		return (no_hit());
	return (construct_cap_hit(ray, obj, &tmp, interval));
}

bool	calculate_cylinder_intersection(t_ray ray,
		t_object *obj, t_raycascyltmp *tmp)
{
	tmp->ray_source_tick = sub_vec_vec(ray.origin,
			obj->u_value.cylinder.center);
	tmp->d_hat = normalize(obj->u_value.cylinder.axis);
	tmp->r = rotation_matrix(tmp->d_hat, vec(0, 0, 1));
	tmp->ray_hat_rotated = mul_matrix_vec(tmp->r, normalize(ray.direction));
	tmp->source_rotated = mul_matrix_vec(tmp->r, tmp->ray_source_tick);
	tmp->a = pow(tmp->ray_hat_rotated.x, 2) + pow(tmp->ray_hat_rotated.y, 2);
	tmp->b = 2 * (tmp->source_rotated.x * tmp->ray_hat_rotated.x
			+ tmp->source_rotated.y * tmp->ray_hat_rotated.y);
	tmp->c = pow(tmp->source_rotated.x, 2) + pow(tmp->source_rotated.y, 2)
		- pow(obj->u_value.cylinder.radius, 2);
	if (!root1(tmp->a, tmp->b, tmp->c, &tmp->distance))
		return (false);
	if (tmp->distance <= 0)
		root2(tmp->a, tmp->b, tmp->c, &tmp->distance);
	if (tmp->distance <= 0)
		return (false);
	return (true);
}

t_hit	compute_hit_data(t_ray ray, t_object *obj,
	t_raycascyltmp *tmp, t_interval interval)
{
	tmp->intersect_tick = vec(tmp->source_rotated.x + tmp->ray_hat_rotated.x
			* tmp->distance, tmp->source_rotated.y
			+ tmp->ray_hat_rotated.y * tmp->distance, 0);
	tmp->normal = mul_matrix_vec(rotation_matrix(vec(0, 0, 1),
				tmp->d_hat), tmp->intersect_tick);
	if (dot_vec(tmp->normal, ray.direction) > 0)
		tmp->normal = vec_neg(tmp->normal);
	tmp->hit.hit = true;
	tmp->hit.object = obj;
	tmp->hit.point = add_vec_vec(ray.origin,
			mul_vec_double(normalize(ray.direction), tmp->distance));
	tmp->hit.distance = length(sub_vec_vec(tmp->hit.point, ray.origin));
	tmp->hit.normal = normalize(tmp->normal);
	if (hypot(obj->u_value.cylinder.radius, obj->u_value.cylinder.height / 2)
		< length(sub_vec_vec(tmp->hit.point, obj->u_value.cylinder.center)))
		return (render_caps(ray, obj, tmp, interval));
	if (!surrounds(interval, tmp->hit.distance))
		return (no_hit());
	return (tmp->hit);
}

t_hit	ray_cast_cylinder(t_ray ray, t_interval interval, t_object *obj)
{
	t_raycascyltmp	tmp;

	if (!calculate_cylinder_intersection(ray, obj, &tmp))
		return (no_hit());
	return (compute_hit_data(ray, obj, &tmp, interval));
}
