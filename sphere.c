/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrei <andrei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:23:07 by kaan              #+#    #+#             */
/*   Updated: 2024/08/15 18:11:55 by andrei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double  find_root1(double discriminant, double h, double a)
{
    double      sqrtd;
    double      root;

    sqrtd = sqrt(discriminant);
    root = (h - sqrtd) / a;
    return (root);
}

double  find_root2(double discriminant, double h, double a)
{
    double      sqrtd;
    double      root;

    sqrtd = sqrt(discriminant);
    root = (h + sqrtd) / a;
    return (root);
}

bool    hit_sphere(t_ray ray, t_interval interval, t_hit_rec *hit, t_sphere sphere)
{
    t_vector    oc;
    t_vector    outward_normal;
    double      a;
    double      h;
    double      c;
    double      discriminant;
    double      root;


    oc = subtrac_vec_vec(sphere.center, ray.origin);
    a = length_squared(ray.direction);
    h = dot_vec(ray.direction, oc);
    c = length_squared(oc) - (sphere.radius * sphere.radius);
    discriminant = (h * h) - (a * c);
    if (discriminant < 0)
        return (false);
    root = find_root1(discriminant, h, a);
    if (!surrounds(interval, root))
    {
        root = find_root2(discriminant, h, a);
        if (!surrounds(interval, root))
            return (false);
    }
    hit->hit_distance = root;
    hit->hit_point = at_vec(ray, hit->hit_distance);
    hit->normal = divi_vec_doub(subtrac_vec_vec(hit->hit_point, sphere.center), sphere.radius);
    outward_normal = divi_vec_doub(subtrac_vec_vec(hit->hit_point, sphere.center), sphere.radius);
    set_face_normal(ray, outward_normal, hit);
    return (true);
}
