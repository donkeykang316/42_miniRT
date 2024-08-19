/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrei <andrei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 18:26:44 by andrei            #+#    #+#             */
/*   Updated: 2024/08/19 21:45:38 by andrei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double projection_length(t_vector of, t_vector onto) {
    return dot_vec(of, onto) / dot_vec(onto, onto);
}

t_vector projection(t_vector of, t_vector onto) {
    return multi_vec_doub(onto, projection_length(of, onto));
}

bool    hit_plane(t_ray ray, t_interval interval, t_hit_rec *hit, t_plane plane) {
    t_vector to_point = subtrac_vec_vec(plane.point, ray.origin);
    t_vector normal_to_plane = projection(to_point, plane.normal);
    if (dot_vec(normal_to_plane, ray.direction) <= 0) {
        return false;
    }
    
    double distance = vec_length(ray.direction) * projection_length(to_point, plane.normal) / projection_length(ray.direction, plane.normal);
    if (!surrounds(interval, distance))
        return (false);
    hit->hit_distance = distance;
    hit->hit_point = add_vec_vec(ray.origin, multi_vec_doub(normalize_vec(ray.direction),distance));
    hit->front_face = true;
    hit->normal = plane.normal;
    if (dot_vec(ray.direction, hit->normal) > 0) {
        hit->normal = subtrac_vec_vec(vec_init(0,0,0), plane.normal);
    }
    return true;
}