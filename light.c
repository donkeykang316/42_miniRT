/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrei <andrei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 14:16:34 by kaan              #+#    #+#             */
/*   Updated: 2024/08/19 18:38:09 by andrei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool hit_point_light(t_vector source, t_hit_rec* hit, t_light* light, t_world* world) {
    t_hit_rec fake_hit = *hit;

    t_ray ray;
    ray.origin = source;
    ray.direction = normalize_vec(subtrac_vec_vec(light->position, source));

    double distance = vec_length(subtrac_vec_vec(ray.origin, light->position));

    t_interval interval;
    interval.min = 0.001;
    interval.max = distance;
    
    if (hit_objects(ray, interval, &fake_hit, world))
        return false;
    double probability = 100*light->intensity / distance / distance;
    if (random_double() < probability) {
        hit->hit_point = light->position;
        hit->hit_distance = distance;
        hit->material.albedo = light->color;
        return true;
    }
    return false;
}