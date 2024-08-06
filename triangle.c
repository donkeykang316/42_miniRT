/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:23:14 by kaan              #+#    #+#             */
/*   Updated: 2024/08/06 12:23:18 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool    is_interior_tri(double alpha, double beta)
{
    if (alpha < 0 || beta < 0 || (alpha + beta) > 1)
        return (false);
    return (true);
}

bool    hit_tri(t_ray ray, t_interval ray_t, t_hit_rec *rec, t_tri *tri)
{
    t_vector    n;
    double      denom;
    double      t;
    t_vector    intersection;
    t_vector    planar_hitpt_vector;
    double      alpha;
    double      beta;

    n = cross_vec(tri->u, tri->v);
    tri->normal = unit_vector(n);
    tri->d = dot_vec(tri->normal, tri->q);
    tri->w = divi_vec_doub(n, length_squared(n));
    denom = dot_vec(tri->normal, ray.direction);
    if (fabs(denom) < EPSILON)
        return (false);
    t = (tri->d - dot_vec(tri->normal, ray.origin)) / denom;
    if (!contains(&ray_t, t))
        return (false);
    intersection = at_vec(ray, t);
    planar_hitpt_vector = subtrac_vec_vec(intersection, tri->q);
    alpha = dot_vec(tri->w, cross_vec(planar_hitpt_vector, tri->v));
    beta = dot_vec(tri->w, cross_vec(tri->u, planar_hitpt_vector));
    if (!is_interior_tri(alpha, beta))
        return (false);
    rec->t = t;
    rec->p = vec_init(intersection.x, intersection.y, intersection.z); 
    rec->material->albedo = vec_init(tri->material->albedo.x, tri->material->albedo.y, tri->material->albedo.z);
    rec->material->fuzz = tri->material->fuzz;
    rec->material->type = tri->material->type;
    set_face_normal(ray, tri->normal, rec);
    return (true);
}