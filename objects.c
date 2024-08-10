/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apago <apago@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:22:20 by kaan              #+#    #+#             */
/*   Updated: 2024/08/10 13:34:06 by apago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool hit_object(t_ray ray, t_hit_rec *rec, t_object *world, int object_index, t_interval interval) {
    t_object object = world[object_index];

    if (object.type == QUAD)
        return hit_quad(ray, interval, rec, object.value.quad);
    if (object.type == TRIANGLE)
        return hit_tri(ray, interval, rec, object.value.triangle);
    if (object.type == SPHERE)
        return hit_sphere(ray, interval, rec, object.value.sphere);
    if (object.type == CYLINDER)
        return hit_cylinder(ray, interval, rec, object.value.cyllinder);
    return false;
}

bool    hit_objects(t_ray ray, t_interval ray_t, t_hit_rec *rec, t_object *world)
{
    bool            hit_anything;
    t_interval      interval;
    double          closest_so_far;
    int             i;

    hit_anything = false;
    closest_so_far = ray_t.max;
    i = 0;
    while (world[i].type)
    {
        interval.min = ray_t.min;
        interval.max = closest_so_far;
        t_material material = world[i].material;
        if (hit_object(ray, rec, world, i, interval))
        {
            hit_anything = true;
            rec->object_index = i;
            rec->material = material;
            closest_so_far = rec->hit_distance;
        }
        i++;
    }
    return (hit_anything);
}
