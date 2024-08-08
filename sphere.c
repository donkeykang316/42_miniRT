/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apago <apago@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:23:07 by kaan              #+#    #+#             */
/*   Updated: 2024/08/08 19:34:02 by apago            ###   ########.fr       */
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

bool    hit_sphere(t_ray ray, t_interval ray_t, t_hit_rec *rec, t_sphere sphere, t_material material)
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
    if (!surrounds(ray_t, root))
    {
        root = find_root2(discriminant, h, a);
        if (!surrounds(ray_t, root))
            return (false);
    }
    rec->t = root;
    rec->p = at_vec(ray, rec->t);
    rec->normal = divi_vec_doub(subtrac_vec_vec(rec->p, sphere.center), sphere.radius);
    outward_normal = divi_vec_doub(subtrac_vec_vec(rec->p, sphere.center), sphere.radius);
    set_face_normal(ray, outward_normal, rec);
    rec->material->albedo = vec_init(material.albedo.x, material.albedo.y, material.albedo.z);
    return (true);
}
