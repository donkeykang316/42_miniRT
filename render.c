/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apago <apago@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:51:30 by andrei            #+#    #+#             */
/*   Updated: 2024/08/25 18:34:50 by apago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_hit no_hit() {
    t_hit hit;
    ft_memset(&hit, 0, sizeof(hit));
    return hit;
}

t_hit hit_object(t_object* object, double distance, t_vec point, t_vec normal) {
    t_hit       hit;
    hit.hit = true;
    hit.distance = distance;
    hit.point = point;
    hit.normal = normal;
    hit.object = object;
    return hit;
}

t_hit ray_cast_at(t_ray ray, t_interval interval, t_object* object) {
    if (object->type == OBJECT_TYPE_SPHERE)
        return ray_cast_sphere(ray, interval, object);
    if (object->type == OBJECT_TYPE_PLANE)
        return ray_cast_plane(ray, interval, object);
    if (object->type == OBJECT_TYPE_CYLINDER)
        return ray_cast_cylinder(ray, interval, object);
    return no_hit();
}

t_hit ray_cast(t_ray ray, t_interval interval, t_world* world) {
    t_hit closest = no_hit();
    closest.distance = INFINITY;

    for(int i = 0; i < world->objects_len; i++) {
        t_hit hit = ray_cast_at(ray, interval, &world->objects[i]);
        if (hit.hit && (hit.distance < closest.distance)) {
            closest = hit;
        }
    }

    return closest;
}


double brdf(t_vec incident, t_vec reflected, t_vec normal) {
    if (dot_vec(reflected, normal) < 0) // TODO || dot_vec(incident, normal) < 0
        return 0;

    double matt =1 / (PHONG_GLOSS + 1);

    double angle = angle_between(reflected, reflect(incident, normal));
    if (angle >= PHONG_MAX_ANGLE)
        return matt;
    double specular = (1 - angle / PHONG_MAX_ANGLE) * PHONG_GLOSS / (PHONG_GLOSS + 1);
    return matt + specular;
}

t_vec sample_phong_brdf(t_vec incident, t_vec normal) {
    double Em = 0.5/(PHONG_GLOSS + 1);
    double Es = 2*PHONG_GLOSS*PHONG_MAX_ANGLE/(PHONG_GLOSS+1);

    t_vec n = normalize(normal);
    t_vec lambert = add_vec_vec(n, random_normalize_vec());
    t_vec r = normalize(reflect(vec_neg(incident), n));
    if (random_double() * (Em + Es) < Em)
        return lambert;
    t_vec specular = add_vec_vec(r, mul_vec_double(random_on_hemisphere(r), PHONG_MAX_ANGLE));
    return specular;
}

t_ray new_ray(t_vec origin, t_vec direction) {
    t_ray ray;
    ray.origin = origin;
    ray.direction = direction;
    return ray;
}

t_ray ray_from_to(t_vec from, t_vec to) {
    return new_ray(from, sub_vec_vec(to, from));
}

t_vec lighting_color(t_ray ray, t_hit hit, t_world* world) {
    t_vec res = mul_vec_vec(hit.object->material.albedo, ambient_light(world->ambient_light));
    for(int i = 0; i < world->point_lights_len; i++) {
        t_light* light = &world->point_lights[i];

        t_ray light_ray = ray_from_to(hit.point, light->position);
        t_interval interval;
        interval.min = 0.01;
        interval.max = length(light_ray.direction);
        t_hit obstacle = ray_cast(light_ray,interval, world);
        if (obstacle.hit) {
            continue;
        }

        const double r_px = 0.1; // FIXME
        double intensity = pow(r_px, 2) / (length_squared(light_ray.direction)) * 255.*tan(light->intensity*M_PI/2);
        double point_brdf = cos_angle_between(vec_neg(ray.direction), hit.normal);
        res = add_vec_vec(res, mul_vec_double(mul_vec_vec(mul_vec_double(hit.object->material.albedo, point_brdf), light->color), intensity));
    }
    return res;
}

t_vec    ray_trace(t_ray ray, int depth, t_world *world)
{
    if (depth <= 0)
        return vec(0,0,0);

    t_interval interval;
    interval.min = 0.01;
    interval.max = 1000;

    t_hit hit = ray_cast(ray, interval, world);
    if (!hit.hit) {
        return ambient_light(world->ambient_light);
    }

    // TODO we don't need to recalculate it every frame
    t_vec lighting = lighting_color(ray, hit, world);
     // TODO instead of multiplying by brdf, sample brdf to get a better random vector?
    t_ray secondary_ray = new_ray(hit.point, sample_phong_brdf(ray.direction, hit.normal));
    t_vec to_reflect = ray_trace(secondary_ray, depth - 1, world);
    t_vec reflected = mul_vec_double(mul_vec_vec(to_reflect, hit.object->material.albedo), cos_angle_between(vec_neg(ray.direction), hit.normal));
    return add_vec_vec(lighting, reflected);
    // return lighting;
}
