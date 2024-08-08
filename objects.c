/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apago <apago@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:22:20 by kaan              #+#    #+#             */
/*   Updated: 2024/08/08 19:34:43 by apago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool    obj_intersec(t_hit_rec *rec, double fuzz, double ref_idx, int i)
{
    rec->object_index = i;
    rec->material->fuzz = fuzz;
    rec->material->ref_idx = ref_idx;
    return (true);
}

bool    hit_objects(t_ray ray, t_interval ray_t, t_hit_rec *rec, t_object *world)
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
    while (world[i].type)
    {
        interval.min = ray_t.min;
        interval.max = closest_so_far;
        t_material material = world[i].material;
        if (world[i].type == QUAD)
        {
            if (hit_quad(ray, interval, rec, world[i].value.quad, material))
            {
                hit_anything = obj_intersec(rec, material.fuzz, material.ref_idx, i);
                closest_so_far = rec->t;
            }
        }
        else if (world[i].type == TRIANGLE)
        {
            if (hit_tri(ray, interval, rec, world[i].value.triangle, material))
            {
                hit_anything = obj_intersec(rec, material.fuzz, material.ref_idx, i);
                closest_so_far = rec->t;
            }
        }
        else if (world[i].type == SPHERE)
        {
            if (hit_sphere(ray, interval, rec, world[i].value.sphere, material))
            {
                hit_anything = obj_intersec(rec, material.fuzz, material.ref_idx, i);
                closest_so_far = rec->t;
            }
        }
        else if (world[i].type == CYLINDER)
        {
            if (hit_cylinder(ray, interval, rec, world[i].value.cyllinder, material))
            {
                hit_anything = obj_intersec(rec, material.fuzz, material.ref_idx, i);
                closest_so_far = rec->t;
            }
        }
        i++;
    }
    return (hit_anything);
}
