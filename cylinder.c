/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apago <apago@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:21:11 by kaan              #+#    #+#             */
/*   Updated: 2024/08/25 14:04:00 by apago            ###   ########.fr       */
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

t_hit    ray_cast_cylinder(t_ray ray, t_interval interval, t_object* obj)
{
    t_vec    oc;
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
    t_vec    intersection;
    t_vec    cy_ax;

    oc = sub_vec_vec(ray.origin, obj->value.cylinder.center);
    cad = dot_vec(obj->value.cylinder.axis, ray.direction);
    caoc = dot_vec(obj->value.cylinder.axis, oc);
    a = dot_vec(ray.direction, ray.direction) - (cad * cad);
    h = dot_vec(oc, ray.direction) - (cad * caoc);
    c = length_squared(oc) - (caoc * caoc) - (obj->value.cylinder.radius * obj->value.cylinder.radius);
    discriminant = (h * h) - (a * c);
    if (discriminant < 0)
        return (no_hit());
    root1 = (-h - sqrt(discriminant)) / a;
    root2 = (-h + sqrt(discriminant)) / a;
    if (root1 > root2)
        swap_double(&root1, &root2);
    cap_top = caoc + root1 * cad;
    cap_botom = caoc + root2 * cad;
    if (cap_top < 0)
    {
        if (cap_botom < 0)
            return (no_hit());
        root1 = root2;
        cap_top = cap_botom;
    }
    if (cap_top > obj->value.cylinder.height)
    {
        if (cap_botom > obj->value.cylinder.height)
            return (no_hit());
        root1 = root2;
    }

    if (!surrounds(interval, root1))
        return (no_hit());

    t_hit hit;
    hit.hit = true;
    hit.distance = root1;
    hit.object = obj;

    intersection = at_ray(ray, root1);
    cy_ax = mul_vec_double(obj->value.cylinder.axis, dot_vec(sub_vec_vec(intersection, obj->value.cylinder.center), obj->value.cylinder.axis));
    hit.point = sub_vec_vec(sub_vec_vec(intersection, obj->value.cylinder.center), cy_ax);
    hit.normal = normalize(hit.point);
    return (hit);
}
