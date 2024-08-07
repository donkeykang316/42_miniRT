/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:21:33 by kaan              #+#    #+#             */
/*   Updated: 2024/08/07 17:48:13 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void    light_init(t_light *light, t_vector position, t_vector direction, double intensity)
{
    light->position = vec_init(position.x, position.y, position.z);
    light->direction = vec_init(direction.x, direction.y, direction.z);
    light->intensity = intensity;
    light->albedo = vec_init(0 + intensity, 0 + intensity, 0 + intensity);
}

bool    hit_light(t_ray ray, t_interval ray_t, t_hit_rec *rec, t_sphere *light_source)
{
    bool            hit_anything;
    t_interval      interval;
    double          closest_so_far;
    int             i;

    (void)rec;
    hit_anything = false;
    closest_so_far = ray_t.max;
    i = 0;
    rec->material = malloc(sizeof(t_material));
    interval.min = ray_t.min;
    interval.max = closest_so_far;
    if (hit_sphere(ray, interval, rec, light_source))
    {
        hit_anything = true;
        closest_so_far = rec->t;
        rec->object_index = i;
        rec->material->fuzz = light_source->material->fuzz;
        rec->material->ref_idx = light_source->material->ref_idx;
    }
    return (hit_anything);
}

bool    scatter_light(t_ray *r_in, t_hit_rec *rec, t_vector attenuation, t_ray *scattered, t_material *material)
{
    t_vector    scatter_direction;

    (void)attenuation;
    (void)scattered;
    (void)r_in;
    scatter_direction = vec_init(rec->normal.x, rec->normal.y, rec->normal.z);
    scattered->origin = vec_init(rec->p.x, rec->p.y, rec->p.z);
    scattered->direction = vec_init(scatter_direction.x, scatter_direction.y, scatter_direction.z);
    attenuation = vec_init(material->albedo.x, material->albedo.y, material->albedo.z);
    return (true);
}
