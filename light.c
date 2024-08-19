/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrei <andrei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 14:16:34 by kaan              #+#    #+#             */
/*   Updated: 2024/08/20 00:11:06 by andrei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double angle_between(t_vector a, t_vector b) {
    float len = vec_length(a) * vec_length(b);
    if (len == 0)
        return 0;
    return acos(dot_vec(a, b) / len);
}

double brdf_density(t_hit_rec hit, t_vector direction, t_vector incident_direction) {
    if (dot_vec(hit.normal, direction) < 0)
        return 0;

    if (hit.material.type == METAL) {
        t_vector reflection = reflect(incident_direction, hit.normal);
        double max_angle = 2*asin(hit.material.fuzz);
        double angle = angle_between(direction, reflection);
        if (angle >= max_angle)
            return 0.0;
        return pow((max_angle - angle)/max_angle, 2);
    }
    return 1.0;
}

t_vector light_from(t_hit_rec hit, t_light* light, t_world* world, t_vector incident_direction) {
    t_hit_rec fake_hit;
    ft_memset(&fake_hit, 0, sizeof(fake_hit));

    t_ray ray;
    ray.origin = hit.hit_point;
    ray.direction = normalize_vec(subtrac_vec_vec(light->position, hit.hit_point));

    double distance =  vec_length(subtrac_vec_vec(ray.origin, light->position));
    
    t_interval interval;
    interval.min = 0.1;
    interval.max = distance;
    
    if (hit_objects(ray, interval, &fake_hit, world)) {
        return vec_init(0,0,0);
    }

    double brdf = brdf_density(hit, subtrac_vec_vec(light->position, hit.hit_point), incident_direction);
    return multi_vec_doub(light->color, 255.*brdf * tan(light->intensity*PI/2) / powf(distance + hit.total_hit_distance, 2));
}

t_vector lighting(t_hit_rec hit, t_world* world, t_vector incident_direction) {
    t_vector res = ambient_light(world->ambient_light);
    for(int i = 0; i < world->point_lights_len; i++) {
        res = add_vec_vec(res, light_from(hit, &world->point_lights[i], world, incident_direction));
    }
    return res;
}