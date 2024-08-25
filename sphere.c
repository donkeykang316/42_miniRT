/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apago <apago@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:23:07 by kaan              #+#    #+#             */
/*   Updated: 2024/08/25 18:18:12 by apago            ###   ########.fr       */
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

t_hit ray_cast_sphere(t_ray ray, t_interval interval, t_object* object) {
    t_vec    oc;
    double      a;
    double      h;
    double      c;
    double      discriminant;
    double      root;


    oc = sub_vec_vec(object->value.sphere.center, ray.origin);
    a = length_squared(ray.direction);
    h = dot_vec(ray.direction, oc);
    c = length_squared(oc) - (object->value.sphere.radius * object->value.sphere.radius);
    discriminant = (h * h) - (a * c);
    if (discriminant < 0)
        return no_hit();
    root = find_root1(discriminant, h, a);
    if (!surrounds(interval, root))
    {
        root = find_root2(discriminant, h, a);
        if (!surrounds(interval, root))
            return no_hit();
    }
    t_vec hit_point = at_ray(ray, root);
    return hit_object(
        object,
        length(sub_vec_vec(hit_point, ray.origin)),
        hit_point,
        div_vec_double(sub_vec_vec(hit_point, object->value.sphere.center), object->value.sphere.radius)
    );
}
