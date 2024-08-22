/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrei <andrei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:23:14 by kaan              #+#    #+#             */
/*   Updated: 2024/08/23 00:28:28 by andrei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool    is_interior_tri(double alpha, double beta)
{
    if (alpha < 0 || beta < 0 || (alpha + beta) > 1)
        return (false);
    return (true);
}

bool    hit_tri(t_ray ray, t_interval ray_t, t_hit_rec *rec, t_triangle tri)
{
    t_vec    n;
    double      denom;
    double      t;
    t_vec    intersection;
    t_vec    planar_hitpt_vector;
    double      alpha;
    double      beta;

    n = cross_vec(tri.u, tri.v);
    tri.normal = normalize(n);
    tri.d = dot_vec(tri.normal, tri.q);
    tri.w = div_vec_double(n, length_squared(n));
    denom = dot_vec(tri.normal, ray.direction);
    if (fabs(denom) < EPSILON)
        return (false);
    t = (tri.d - dot_vec(tri.normal, ray.origin)) / denom;
    if (!contains(&ray_t, t))
        return (false);
    intersection = at_ray(ray, t);
    planar_hitpt_vector = sub_vec_vec(intersection, tri.q);
    alpha = dot_vec(tri.w, cross_vec(planar_hitpt_vector, tri.v));
    beta = dot_vec(tri.w, cross_vec(tri.u, planar_hitpt_vector));
    if (!is_interior_tri(alpha, beta))
        return (false);
    rec->hit_distance = t;
    rec->hit_point = vec(intersection.x, intersection.y, intersection.z);
    set_face_normal(ray, tri.normal, rec);
    return (true);
}
