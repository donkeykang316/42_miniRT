/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrei <andrei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:21:11 by kaan              #+#    #+#             */
/*   Updated: 2024/08/15 18:20:59 by andrei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void    swap_double(double *a, double *b)
{
    double  temp;

    temp = *a;
    *a = *b;
    *b = temp;
}

bool    hit_cylinder(t_ray ray, t_interval interval, t_hit_rec *hit, t_cylinder cylinder)
{
    t_vector    oc;
    double      a;
    double      h;
    double      c;
    double      cad;
    double      caoc;
    double      discriminant;
    double      root1;
    double      root2;
    double      cap_botom;
    double      cap_top;
    t_vector    intersection;
    t_vector    cy_ax;

    oc = subtrac_vec_vec(ray.origin, cylinder.center);
    cad = dot_vec(cylinder.axis, ray.direction);
    caoc = dot_vec(cylinder.axis, oc);
    a = dot_vec(ray.direction, ray.direction) - (cad * cad);
    h = dot_vec(oc, ray.direction) - (cad * caoc);
    c = length_squared(oc) - (caoc * caoc) - (cylinder.radius * cylinder.radius);
    discriminant = (h * h) - (a * c);
    if (discriminant < 0)
        return (false);
    root1 = (-h - sqrt(discriminant)) / a;
    root2 = (-h + sqrt(discriminant)) / a;
    if (root1 > root2)
        swap_double(&root1, &root2);
    cap_top = caoc + root1 * cad;
    cap_botom = caoc + root2 * cad;
    if (cap_top < 0)
    {
        if (cap_botom < 0)
            return (false);
        root1 = root2;
        cap_top = cap_botom;
    }
    if (cap_top > cylinder.height)
    {
        if (cap_botom > cylinder.height)
            return (false);
        root1 = root2;
    }

    if (!surrounds(interval, root1))
        return (false);
    hit->hit_distance = root1;
    intersection = at_vec(ray, hit->hit_distance);
    cy_ax = multi_vec_doub(cylinder.axis, dot_vec(subtrac_vec_vec(intersection, cylinder.center), cylinder.axis));
    hit->hit_point = subtrac_vec_vec(subtrac_vec_vec(intersection, cylinder.center), cy_ax);
    hit->normal = normalize_vec(hit->hit_point);
    return (true);
}
