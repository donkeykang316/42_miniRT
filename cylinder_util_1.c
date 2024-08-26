/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_util_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 15:41:14 by kaan              #+#    #+#             */
/*   Updated: 2024/08/26 16:08:42 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_matrix	rotation_matrix(t_vec turn_vec, t_vec into_vec)
{
	t_vec		v;
	double		s;
	double		c;
	t_matrix	v_cross;
	t_matrix	r;

	v = cross_vec(turn_vec, into_vec);
	s = length(v);
	c = dot_vec(turn_vec, into_vec);
	v_cross.col0.x = 0;
	v_cross.col0.y = v.z;
	v_cross.col0.z = -v.y;
	v_cross.col1.x = -v.z;
	v_cross.col1.y = 0;
	v_cross.col1.z = v.x;
	v_cross.col2.x = v.y;
	v_cross.col2.y = -v.x;
	v_cross.col2.z = 0;
	r = add_matrix_matrix(add_matrix_matrix(identity(), v_cross),
			mul_matrix_double(mul_matrix_matrix(v_cross, v_cross),
				(1 - c) / pow(s, 2)));
	return (r);
}

t_vec	mul_matrix_vec(t_matrix m, t_vec v)
{
	return (vec(m.col0.x * v.x + m.col1.x * v.y + m.col2.x * v.z,
			m.col0.y * v.x + m.col1.y * v.y + m.col2.y * v.z,
			m.col0.z * v.x + m.col1.z * v.y + m.col2.z * v.z));
}

bool	root1(double a, double b, double c, double *root)
{
	double	d;

	d = b * b - 4 * a * c;
	if (d < 0)
		return (false);
	*root = (-b - sqrt(d)) / 2 / a;
	return (true);
}

bool	root2(double a, double b, double c, double *root)
{
	double	d;

	d = b * b - 4 * a * c;
	if (d < 0)
		return (false);
	*root = (-b + sqrt(d)) / 2 / a;
	return (true);
}

bool	compute_cap_intersection(t_ray ray, t_object *obj,
	t_raycascyltmp *ray_ca, t_rndcapstmp *tmp)
{
	tmp->delta = obj->u_value.cylinder.height / 2;
	tmp->i = 1;
	if (dot_vec(obj->u_value.cylinder.axis, ray.direction) > 0)
		tmp->i = -1;
	tmp->vertical_speed = projection_length(normalize(ray.direction),
			obj->u_value.cylinder.axis);
	tmp->vertical_distance = projection_length(sub_vec_vec(
				obj->u_value.cylinder.center, ray.origin),
			obj->u_value.cylinder.axis) + tmp->delta * tmp->i;
	tmp->times = tmp->vertical_distance / tmp->vertical_speed;
	if (tmp->times < 0)
		return (false);
	tmp->intersection_2d = add_vec_vec(ray_ca->source_rotated,
			mul_vec_double(ray_ca->ray_hat_rotated, tmp->times));
	if (hypot(tmp->intersection_2d.x, tmp->intersection_2d.y)
		> obj->u_value.cylinder.radius)
		return (false);
	return (true);
}
