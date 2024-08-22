/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrei <andrei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:22:06 by kaan              #+#    #+#             */
/*   Updated: 2024/08/23 00:28:28 by andrei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool    scatter_lambertian(t_ray *r_in, t_hit_rec *rec, t_vec attenuation, t_ray *scattered, t_material material)
{
    t_vec    scatter_direction;

    (void)attenuation;
    (void)material;
    (void)scattered;
    (void)r_in;
    scatter_direction = add_vec_vec(rec->normal, random_normalize_vec());
    scattered->origin = rec->hit_point;
    scattered->direction = scatter_direction;
    // attenuation = vec_init(material->albedo.x, material->albedo.y, material->albedo.z);
    return (true);
}

bool    scatter_metal(t_ray *r_in, t_hit_rec *rec, t_vec attenuation, t_ray *scattered, t_material material)
{
    t_vec    reflected;

    (void)attenuation;
    reflected = add_vec_vec(normalize(reflect(r_in->direction, rec->normal)), mul_vec_double(random_normalize_vec(), fuzz(material.fuzz)));
    if (random_double() < 0.5) {
        reflected = add_vec_vec(rec->normal, random_normalize_vec());
    }
    scattered->origin = vec(rec->hit_point.x, rec->hit_point.y, rec->hit_point.z);
    scattered->direction = vec(reflected.x, reflected.y, reflected.z);
    attenuation = vec(material.albedo.x, material.albedo.y, material.albedo.z);
    return (dot_vec(scattered->direction, rec->normal) > 0);
}

bool    scatter_dieletric(t_ray *r_in, t_hit_rec *rec, t_vec attenuation, t_ray *scattered, t_material material)
{
    double      ri;
    t_vec    unit_direction;
    double      cos_theta;
    double      sin_theta;
    bool        cannot_refract;
    t_vec    direction;
    double      refla;

    (void)attenuation;
    attenuation = vec(1.0, 1.0, 1.0);
    if (rec->front_face)
        ri = 1.0 / material.ref_idx;
    else
        ri = material.ref_idx;
    unit_direction = normalize(r_in->direction);
    cos_theta = fmin(dot_vec(mul_vec_int(unit_direction, -1), rec->normal), 1.0);
    sin_theta = sqrt(1.0 - cos_theta * cos_theta);
    cannot_refract = ri * sin_theta > 1.0;
    refla = reflectance(cos_theta, ri);
    if (cannot_refract || refla > random_double())
        direction = reflect(unit_direction, rec->normal);
    else
        direction = refract(unit_direction, rec->normal, ri);
    scattered->origin = vec(rec->hit_point.x, rec->hit_point.y, rec->hit_point.z);
    scattered->direction = vec(direction.x, direction.y, direction.z);
    return (true);
}

void    set_face_normal(t_ray r, t_vec outward_normal, t_hit_rec *rec)
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
