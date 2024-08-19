/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrei <andrei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:23:00 by kaan              #+#    #+#             */
/*   Updated: 2024/08/15 21:48:05 by andrei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector    ray_color_util(t_ray scattered, t_hit_rec *rec, int depth, t_world *world)
{
    t_vector    r_color;
    t_vector    albedo;
    t_vector    r_col_tmp;

    albedo = rec->material.albedo;
    r_col_tmp = ray_color(&scattered, rec, depth - 1, world);
    r_color = multi_vec_vec(albedo, r_col_tmp);
    return (r_color);
}

t_vector ambient_light(t_amblight light) {
    return multi_vec_doub(light.color, light.intensity);
}

t_vector    ray_scatter(t_ray *ray, t_hit_rec *rec, int depth, t_world *world)
{
    t_ray       scattered;
    t_vector    attenuation;

    attenuation = vec_init(0,0,0);
    if (world->objects[rec->object_index].material.type == LAMBERTIAN)
    {
            if (scatter_lambertian(ray, rec, attenuation, &scattered, rec->material))
                return (ray_color_util(scattered, rec, depth, world));
    }
    else if (world->objects[rec->object_index].material.type == METAL)
    {
        if (scatter_metal(ray, rec, attenuation, &scattered, rec->material))
            return (ray_color_util(scattered, rec, depth, world));
    }
    else if (world->objects[rec->object_index].material.type == DIELECTRIC)
    {
        if (scatter_dieletric(ray, rec, attenuation, &scattered, rec->material))
            return (ray_color_util(scattered, rec, depth, world));
    }
    return ambient_light(world->ambient_light);
}

t_vector    ray_color(t_ray *ray, t_hit_rec *rec, int depth, t_world *world)
{
    t_interval  interval;

    if (depth <= 0)
        return ambient_light(world->ambient_light);
    interval.min = 0.001;
    interval.max = INFINITY;
    if (hit_objects(*ray, interval, rec, world))
        return (ray_scatter(ray, rec, depth, world));
    return ambient_light(world->ambient_light);
}
