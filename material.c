/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:22:06 by kaan              #+#    #+#             */
/*   Updated: 2024/08/10 15:18:32 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool    scatter_lambertian(t_ray *r_in, t_hit_rec *rec, t_vector attenuation, t_ray *scattered, t_material material)
{
    t_vector    scatter_direction;

    (void)attenuation;
    (void)material;
    (void)scattered;
    (void)r_in;
    scatter_direction = add_vec_vec(rec->normal, random_unit_vector());
    scattered->origin = vec_init(rec->hit_point.x, rec->hit_point.y, rec->hit_point.z);
    scattered->direction = vec_init(scatter_direction.x, scatter_direction.y, scatter_direction.z);
    // attenuation = vec_init(material->albedo.x, material->albedo.y, material->albedo.z);
    return (true);
}

bool    scatter_metal(t_ray *r_in, t_hit_rec *rec, t_vector attenuation, t_ray *scattered, t_material material)
{
    t_vector    reflected;

    (void)attenuation;
    reflected = add_vec_vec(unit_vector(reflect(r_in->direction, rec->normal)), multi_vec_doub(random_unit_vector(), fuzz(material.fuzz)));
    scattered->origin = vec_init(rec->hit_point.x, rec->hit_point.y, rec->hit_point.z);
    scattered->direction = vec_init(reflected.x, reflected.y, reflected.z);
    attenuation = vec_init(material.albedo.x, material.albedo.y, material.albedo.z);
    return (dot_vec(scattered->direction, rec->normal) > 0);
}

bool    scatter_dieletric(t_ray *r_in, t_hit_rec *rec, t_vector attenuation, t_ray *scattered, t_material material)
{
    double      ri;
    t_vector    unit_direction;
    double      cos_theta;
    double      sin_theta;
    bool        cannot_refract;
    t_vector    direction;
    double      refla;

    (void)attenuation;
    attenuation = vec_init(1.0, 1.0, 1.0);
    if (rec->front_face)
        ri = 1.0 / material.ref_idx;
    else
        ri = material.ref_idx;
    unit_direction = unit_vector(r_in->direction);
    cos_theta = fmin(dot_vec(multi_vec_int(unit_direction, -1), rec->normal), 1.0);
    sin_theta = sqrt(1.0 - cos_theta * cos_theta);
    cannot_refract = ri * sin_theta > 1.0;
    refla = reflectance(cos_theta, ri);
    if (cannot_refract || refla > random_double())
        direction = reflect(unit_direction, rec->normal);
    else
        direction = refract(unit_direction, rec->normal, ri);
    scattered->origin = vec_init(rec->hit_point.x, rec->hit_point.y, rec->hit_point.z);
    scattered->direction = vec_init(direction.x, direction.y, direction.z);
    return (true);
}

void    set_face_normal(t_ray r, t_vector outward_normal, t_hit_rec *rec)
{
    (void)outward_normal;
    rec->front_face = dot_vec(r.direction, rec->normal) < 0;
    if (rec->normal.x < 0)
        outward_normal.x = -rec->normal.x;
    if (rec->normal.y < 0)
        outward_normal.y = -rec->normal.y;
    if (rec->normal.z < 0)
        outward_normal.z = -rec->normal.z;
}
