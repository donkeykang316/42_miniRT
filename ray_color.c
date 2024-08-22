/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrei <andrei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:23:00 by kaan              #+#    #+#             */
/*   Updated: 2024/08/23 00:28:28 by andrei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec    ray_color_util(t_ray scattered, t_hit_rec *rec, int depth, t_world *world)
{
    t_vec    r_color;
    t_vec    albedo;
    t_vec    r_col_tmp;

    albedo = rec->material.albedo;
    
    r_col_tmp = ray_color(&scattered, rec, depth - 1, world);
    r_color = mul_vec_vec(albedo, r_col_tmp);
    return (r_color);
}

t_vec ambient_light(t_amblight light) {
    return mul_vec_double(light.color, light.intensity);
}

t_vec    ray_scatter(t_ray *ray, t_hit_rec *rec, int depth, t_world *world)
{
    t_ray       scattered;
    t_vec    attenuation;

    rec->last_hit_direction = ray->direction;
    attenuation = vec(0,0,0);
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
    t_vec res = mul_vec_vec(rec->material.albedo, lighting(*rec, world, ray->direction));
    // res = vec_init(1,0,0);
    return res;
}

t_vec    ray_color(t_ray *ray, t_hit_rec *rec, int depth, t_world *world)
{
    t_interval  interval;
    interval.min = 0.001;
    interval.max = INFINITY;

    t_vec res = lighting(*rec, world, ray->direction);
    if (depth <= 0)
        return res;

    if (hit_objects(*ray, interval, rec, world)) {
        res = ray_scatter(ray, rec, depth, world);
    }

    return res;
}
