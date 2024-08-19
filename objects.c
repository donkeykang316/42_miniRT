/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrei <andrei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:22:20 by kaan              #+#    #+#             */
/*   Updated: 2024/08/20 00:02:59 by andrei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool hit_object(t_ray ray, t_hit_rec *rec, t_object object, t_interval interval) {
    if (object.type == QUAD)
        return hit_quad(ray, interval, rec, object.value.quad);
    if (object.type == TRIANGLE)
        return hit_tri(ray, interval, rec, object.value.triangle);
    if (object.type == SPHERE)
        return hit_sphere(ray, interval, rec, object.value.sphere);
    if (object.type == CYLINDER)
        return hit_cylinder(ray, interval, rec, object.value.cyllinder);
    if (object.type == PLANE)
        return hit_plane(ray, interval, rec, object.value.plane);
    return false;
}

bool    hit_objects(t_ray ray, t_interval ray_t, t_hit_rec *rec, t_world *world)
{
    bool            hit_anything;
    t_interval      interval;
    double          closest_so_far;
    int             i;

    hit_anything = false;
    closest_so_far = ray_t.max;
    i = 0;
    while (i < world->objects_len)
    {
        interval.min = ray_t.min;
        interval.max = closest_so_far;
        t_material material = world->objects[i].material;
        if (hit_object(ray, rec, world->objects[i], interval))
        {
            hit_anything = true;
            rec->object_index = i;
            rec->material = material;
            closest_so_far = rec->hit_distance;
        }
        i++;
    }
    if (hit_anything) {
        rec->total_hit_distance += rec->hit_distance;
    }
    return (hit_anything);
}
