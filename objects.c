/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:22:20 by kaan              #+#    #+#             */
/*   Updated: 2024/08/08 15:24:46 by kaan             ###   ########.fr       */
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

bool    hit_objects(t_ray ray, t_interval ray_t, t_hit_rec *rec, t_object_list **object)
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
    while (object[i])
    {
        interval.min = ray_t.min;
        interval.max = closest_so_far;
        if (object[i]->type == QUAD)
        {
            if (hit_quad(ray, interval, rec, object[i]->quad))
            {
                hit_anything = obj_intersec(rec, object[i]->quad->material->fuzz, object[i]->quad->material->ref_idx, i);
                closest_so_far = rec->t;
            }
        }
        else if (object[i]->type == TRIANGLE)
        {
            if (hit_tri(ray, interval, rec, object[i]->tri))
            {
                hit_anything = obj_intersec(rec, object[i]->tri->material->fuzz, object[i]->tri->material->ref_idx, i);
                closest_so_far = rec->t;
            }
        }
        else if (object[i]->type == SPHERE)
        {
            if (hit_sphere(ray, interval, rec, object[i]->sphere))
            {
                hit_anything = obj_intersec(rec, object[i]->sphere->material->fuzz, object[i]->sphere->material->ref_idx, i);
                closest_so_far = rec->t;
            }
        }
        else if (object[i]->type == CYLINDER)
        {
            if (hit_cylinder(ray, interval, rec, object[i]->cyl))
            {
                hit_anything = obj_intersec(rec, object[i]->cyl->material->fuzz, object[i]->cyl->material->ref_idx, i);
                closest_so_far = rec->t;
            }
        }
        i++;
    }
    return (hit_anything);
}