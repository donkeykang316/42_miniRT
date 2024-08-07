/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:23:00 by kaan              #+#    #+#             */
/*   Updated: 2024/08/07 23:24:02 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector    ray_color_util(t_ray scattered, t_hit_rec *rec, int depth, t_object_list **world)
{
    t_vector    r_color;
    t_vector    albedo;
    t_vector    r_col_tmp;

    albedo = vec_init(rec->material->albedo.x, rec->material->albedo.y, rec->material->albedo.z);
    r_col_tmp = ray_color(&scattered, rec, depth - 1, world);
    r_color = multi_vec_vec(albedo, r_col_tmp);
    return (r_color);
}

t_vector    ray_quad(t_ray *ray, t_hit_rec *rec, int depth, t_object_list **world)
{
    t_ray       scattered;
    t_vector    attenuation;
    
    (void)attenuation;
    if (world[rec->object_index]->quad->material->type == LAMBERTIAN)
    {
            if (scatter_lambertian(ray, rec, attenuation, &scattered, rec->material))
                return (ray_color_util(scattered, rec, depth, world));
    }
    else if (world[rec->object_index]->quad->material->type == METAL)
    {
        if (scatter_metal(ray, rec, attenuation, &scattered, rec->material))
            return (ray_color_util(scattered, rec, depth, world));
    }
    else if (world[rec->object_index]->quad->material->type == DIELECTRIC)
    {
        if (scatter_dieletric(ray, rec, attenuation, &scattered, rec->material))
            return (ray_color_util(scattered, rec, depth, world));
    }
    return (vec_init(0, 0, 0));
}

t_vector    ray_sphere(t_ray *ray, t_hit_rec *rec, int depth, t_object_list **world)
{
    t_ray       scattered;
    t_vector    attenuation;
    
    (void)attenuation;
    if (world[rec->object_index]->sphere->material->type == LAMBERTIAN)
    {
            if (scatter_lambertian(ray, rec, attenuation, &scattered, rec->material))
                return (ray_color_util(scattered, rec, depth, world));
    }
    else if (world[rec->object_index]->sphere->material->type == METAL)
    {
        if (scatter_metal(ray, rec, attenuation, &scattered, rec->material))
            return (ray_color_util(scattered, rec, depth, world));
    }
    else if (world[rec->object_index]->sphere->material->type == DIELECTRIC)
    {
        if (scatter_dieletric(ray, rec, attenuation, &scattered, rec->material))
            return (ray_color_util(scattered, rec, depth, world));
    }
    return (vec_init(0, 0, 0));
}

t_vector    ray_cyl(t_ray *ray, t_hit_rec *rec, int depth, t_object_list **world)
{
    t_ray       scattered;
    t_vector    attenuation;
    
    (void)attenuation;
    if (world[rec->object_index]->cyl->material->type == LAMBERTIAN)
    {
            if (scatter_lambertian(ray, rec, attenuation, &scattered, rec->material))
                return (ray_color_util(scattered, rec, depth, world));
    }
    else if (world[rec->object_index]->cyl->material->type == METAL)
    {
        if (scatter_metal(ray, rec, attenuation, &scattered, rec->material))
            return (ray_color_util(scattered, rec, depth, world));
    }
    else if (world[rec->object_index]->cyl->material->type == DIELECTRIC)
    {
        if (scatter_dieletric(ray, rec, attenuation, &scattered, rec->material))
            return (ray_color_util(scattered, rec, depth, world));
    }
    return (vec_init(0, 0, 0));
}

t_vector    ray_tri(t_ray *ray, t_hit_rec *rec, int depth, t_object_list **world)
{
    t_ray       scattered;
    t_vector    attenuation;
    
    (void)attenuation;
    if (world[rec->object_index]->tri->material->type == LAMBERTIAN)
    {
            if (scatter_lambertian(ray, rec, attenuation, &scattered, rec->material))
                return (ray_color_util(scattered, rec, depth, world));
    }
    else if (world[rec->object_index]->tri->material->type == METAL)
    {
        if (scatter_metal(ray, rec, attenuation, &scattered, rec->material))
            return (ray_color_util(scattered, rec, depth, world));
    }
    else if (world[rec->object_index]->tri->material->type == DIELECTRIC)
    {
        if (scatter_dieletric(ray, rec, attenuation, &scattered, rec->material))
            return (ray_color_util(scattered, rec, depth, world));
    }
    return (vec_init(0, 0, 0));
}

t_vector    ray_color(t_ray *ray, t_hit_rec *rec, int depth, t_object_list **world)
{
    t_vector    r_color;
    t_interval  interval;
    double       a;
    t_light     light;
    t_vector    light_direction;
    t_ray       light_ray;

    if (depth <= 0)
        return (vec_init(0, 0, 0));
    interval.min = 0.001;
    interval.max = INFINITY;

    if (hit_objects(*ray, interval, rec, world))
    {
        if (world[rec->object_index]->type == QUAD)
            return (ray_quad(ray, rec, depth, world));
        else if (world[rec->object_index]->type == TRIANGLE)
            return (ray_tri(ray, rec, depth, world));
        else if (world[rec->object_index]->type == SPHERE)
            return (ray_sphere(ray, rec, depth, world));
        else if (world[rec->object_index]->type == CYLINDER)
            return (ray_cyl(ray, rec, depth, world));
    }
    light_init(&light);
    light_direction = normalize_vec(subtrac_vec_vec(light.position, rec->p));
    light_ray.origin = add_vec_vec(rec->p, vec_init(0, 0, 0));
    light_ray.direction = vec_init(light_direction.x, light_direction.y, light_direction.z);
    if (hit_objects(light_ray, interval, rec, world))
        return (vec_init(0.0, 0.0, 0.0));
    a =  length_squared(light_direction);
    if (a < 0.0)
        a = 0.0;
    r_color = multi_vec_doub(light.albedo, a);
    return (r_color);
}
