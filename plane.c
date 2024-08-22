/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrei <andrei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 18:26:44 by andrei            #+#    #+#             */
/*   Updated: 2024/08/23 00:28:28 by andrei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double projection_length(t_vec of, t_vec onto) {
    return dot_vec(of, onto) / dot_vec(onto, onto);
}

t_vec projection(t_vec of, t_vec onto) {
    return mul_vec_double(onto, projection_length(of, onto));
}

bool    hit_plane(t_ray ray, t_interval interval, t_hit_rec *hit, t_plane plane) {
    t_vec to_point = sub_vec_vec(plane.point, ray.origin);
    t_vec normal_to_plane = projection(to_point, plane.normal);
    if (dot_vec(normal_to_plane, ray.direction) <= 0) {
        return false;
    }
    
    double distance = length(ray.direction) * projection_length(to_point, plane.normal) / projection_length(ray.direction, plane.normal);
    if (!surrounds(interval, distance))
        return (false);
    hit->hit_distance = distance;
    hit->hit_point = add_vec_vec(ray.origin, mul_vec_double(normalize(ray.direction),distance));
    hit->front_face = true;
    hit->normal = plane.normal;
    if (dot_vec(ray.direction, hit->normal) > 0) {
        hit->normal = sub_vec_vec(vec(0,0,0), plane.normal);
    }
    return true;
}