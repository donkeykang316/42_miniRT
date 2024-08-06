/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:23:00 by kaan              #+#    #+#             */
/*   Updated: 2024/08/06 12:38:48 by kaan             ###   ########.fr       */
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
    else if (world[rec->object_index]->quad->material->type == LIGHT)
    {
        if (scatter_light(ray, rec, attenuation, &scattered, rec->material))
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
    else if (world[rec->object_index]->sphere->material->type == LIGHT)
    {
        if (scatter_light(ray, rec, attenuation, &scattered, rec->material))
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
    else if (world[rec->object_index]->cyl->material->type == LIGHT)
    {
        if (scatter_light(ray, rec, attenuation, &scattered, rec->material))
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
    else if (world[rec->object_index]->tri->material->type == LIGHT)
    {
        if (scatter_light(ray, rec, attenuation, &scattered, rec->material))
            return (ray_color_util(scattered, rec, depth, world));
    }
    return (vec_init(0, 0, 0));
}

t_vector    ray_color(t_ray *ray, t_hit_rec *rec, int depth, t_object_list **world)
{
    t_vector    r_color;
    t_vector    bg_color1;
    t_vector    bg_color2;
    t_vector    unit_direction;
    t_interval  interval;
    double       a;

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
    bg_color1 = vec_init(0.0, 0.0, 0.0);
    bg_color2 = vec_init(0.20, 0.30, 0.50);

    /*bg_color1 = vec_init(1.0, 1.0, 1.0);
    bg_color2 = vec_init(0.5, 0.7, 1.0);*/

    unit_direction = normalize_vec(ray->direction);
    a = 0.5 * (unit_direction.y + 1.0);
    r_color = add_vec_vec(multi_vec_doub(bg_color1, (1.0 - a)), multi_vec_doub(bg_color2, a));
    return (r_color);
}
