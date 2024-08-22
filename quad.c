/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quad.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrei <andrei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:22:30 by kaan              #+#    #+#             */
/*   Updated: 2024/08/23 00:28:28 by andrei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool    is_interior_quad(double alpha, double beta)
{
    t_interval  unit_interval;

    unit_interval.min = 0;
    unit_interval.max = 1;
    if (!contains(&unit_interval, alpha) || !contains(&unit_interval, beta))
        return (false);
    return (true);
}

bool    hit_quad(t_ray ray, t_interval ray_t, t_hit_rec *rec, t_quad quad)
{
    t_vec    n;
    double      denom;
    double      t;
    t_vec    intersection;
    t_vec    planar_hitpt_vector;
    double      alpha;
    double      beta;

    n = cross_vec(quad.u, quad.v);
    quad.normal = normalize(n);
    quad.d = dot_vec(quad.normal, quad.q);
    quad.w = div_vec_double(n, length_squared(n));
    denom = dot_vec(quad.normal, ray.direction);
    if (fabs(denom) < EPSILON)
        return (false);
    t = (quad.d - dot_vec(quad.normal, ray.origin)) / denom;
    if (!contains(&ray_t, t))
        return (false);
    intersection = at_ray(ray, t);
    planar_hitpt_vector = sub_vec_vec(intersection, quad.q);
    alpha = dot_vec(quad.w, cross_vec(planar_hitpt_vector, quad.v));
    beta = dot_vec(quad.w, cross_vec(quad.u, planar_hitpt_vector));
    if (!is_interior_quad(alpha, beta))
        return (false);
    rec->hit_distance = t;
    rec->hit_point = vec(intersection.x, intersection.y, intersection.z);
    set_face_normal(ray, quad.normal, rec);
    return (true);
}
