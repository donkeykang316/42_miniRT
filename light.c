/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apago <apago@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 14:16:34 by kaan              #+#    #+#             */
/*   Updated: 2024/08/08 18:51:27 by apago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*bool    obj_shadow(t_ray ray, t_interval ray_t, t_hit_rec *rec, t_object_list **object)
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
            if (hit_quad(ray, interval, rec, object[i]->value.quad))
            {
                hit_anything = hit_obj_util(rec, object[i]->value.quad->material->fuzz, object[i]->value.quad->material->ref_idx, i);
                closest_so_far = rec->t;
            }
        }
        else if (object[i]->type == TRIANGLE)
        {
            if (hit_tri(ray, interval, rec, object[i]->value.triangle))
            {
                hit_anything = hit_obj_util(rec, object[i]->value.triangle->material->fuzz, object[i]->value.triangle->material->ref_idx, i);
                closest_so_far = rec->t;
            }
        }
        else if (object[i]->type == SPHERE)
        {
            if (hit_sphere(ray, interval, rec, object[i]->value.sphere))
            {
                hit_anything = hit_obj_util(rec, object[i]->value.sphere->material->fuzz, object[i]->value.sphere->material->ref_idx, i);
                closest_so_far = rec->t;
            }
        }
        else if (object[i]->type == CYLINDER)
        {
            if (hit_cylinder(ray, interval, rec, object[i]->value.cyllinder))
            {
                hit_anything = hit_obj_util(rec, object[i]->value.cyllinder->material->fuzz, object[i]->value.cyllinder->material->ref_idx, i);
                closest_so_far = rec->t;
            }
        }
        i++;
    }
    return (hit_anything);
}*/
