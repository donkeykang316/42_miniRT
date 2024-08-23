/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrei <andrei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 18:26:44 by andrei            #+#    #+#             */
/*   Updated: 2024/08/23 17:31:26 by andrei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double projection_length(t_vec of, t_vec onto) {
    return dot_vec(of, onto) / dot_vec(onto, onto);
}

t_vec projection(t_vec of, t_vec onto) {
    return mul_vec_double(onto, projection_length(of, onto));
}

t_hit ray_cast_plane(t_ray ray, t_interval interval, t_object* object) {
    t_plane plane = object->value.plane;

    t_vec to_point = sub_vec_vec(plane.point, ray.origin);
    t_vec normal_to_plane = projection(to_point, plane.normal);
    if (dot_vec(normal_to_plane, ray.direction) <= 0) {
        return no_hit();
    }
    
    double distance = length(ray.direction) * projection_length(to_point, plane.normal) / projection_length(ray.direction, plane.normal);
    if (!surrounds(interval, distance))
        return no_hit();
    t_hit hit;
    hit.hit = true;
    hit.distance = distance;
    hit.point = add_vec_vec(ray.origin, mul_vec_double(normalize(ray.direction),distance));
    hit.normal = plane.normal;
    if (dot_vec(ray.direction, hit.normal) > 0) {
        hit.normal = vec_neg(plane.normal);
    }
    hit.object = object;
    return hit;
}