/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrei <andrei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:51:30 by andrei            #+#    #+#             */
/*   Updated: 2024/08/22 13:12:19 by andrei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector vec_neg(t_vector vec) {
    return subtrac_vec_vec(vec_init(0,0,0), vec);
}
typedef struct s_hit {
    bool hit;
    t_vector point;
    t_vector normal;
    t_object* object;
    double distance;
} t_hit;

t_hit no_hit() {
    t_hit hit;
    ft_memset(&hit, 0, sizeof(hit));
    return hit;
}

t_hit hit_object(t_object* object, double distance, t_vector point, t_vector normal) {
    t_hit       hit;
    hit.hit = true;
    hit.distance = distance;
    hit.point = point;
    hit.normal = normal;
    hit.object = object;
    return hit;
}

t_hit ray_cast_sphere(t_ray ray, t_interval interval, t_object* object) {
    t_vector    oc;
    double      a;
    double      h;
    double      c;
    double      discriminant;
    double      root;


    oc = subtrac_vec_vec(object->value.sphere.center, ray.origin);
    a = length_squared(ray.direction);
    h = dot_vec(ray.direction, oc);
    c = length_squared(oc) - (object->value.sphere.radius * object->value.sphere.radius);
    discriminant = (h * h) - (a * c);
    if (discriminant < 0)
        return no_hit();
    root = find_root1(discriminant, h, a);
    if (!surrounds(interval, root))
    {
        root = find_root2(discriminant, h, a);
        if (!surrounds(interval, root))
            return no_hit();
    }
    t_vector hit_point = at_vec(ray, root);
    return hit_object(
        object,
        root,
        hit_point,
        divi_vec_doub(subtrac_vec_vec(hit_point, object->value.sphere.center), object->value.sphere.radius)
    );
}

t_hit ray_cast_plane(t_ray ray, t_interval interval, t_object* object) {
    t_plane plane = object->value.plane;

    t_vector to_point = subtrac_vec_vec(plane.point, ray.origin);
    t_vector normal_to_plane = projection(to_point, plane.normal);
    if (dot_vec(normal_to_plane, ray.direction) <= 0) {
        return no_hit();
    }
    
    double distance = vec_length(ray.direction) * projection_length(to_point, plane.normal) / projection_length(ray.direction, plane.normal);
    if (!surrounds(interval, distance))
        return no_hit();
    t_hit hit;
    hit.hit = true;
    hit.distance = distance;
    hit.point = add_vec_vec(ray.origin, multi_vec_doub(normalize_vec(ray.direction),distance));
    hit.normal = plane.normal;
    if (dot_vec(ray.direction, hit.normal) > 0) {
        hit.normal = vec_neg(plane.normal);
    }
    hit.object = object;
    return hit;
}

t_hit ray_cast_at(t_ray ray, t_interval interval, t_object* object) {
    if (object->type == SPHERE)
        return ray_cast_sphere(ray, interval, object);
    if (object->type == PLANE)
        return ray_cast_plane(ray, interval, object);
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

double brdf(t_vector incident, t_vector reflected, t_vector normal) {
    if (dot_vec(reflected, normal) < 0) // TODO  || dot_vec(incident, normal) > 0
        return 0;

    double max_specular_angle = 0.1;
    double glossiness = 0.2;

    double matt = cos(angle_between(reflected, normal));

    double angle = angle_between(reflected, reflect(incident, normal));
    if (angle > max_specular_angle) 
        return matt;
    double specular = pow(1 - angle / max_specular_angle, 2)*glossiness;
    return specular + matt;
}

t_ray new_ray(t_vector origin, t_vector direction) {
    t_ray ray;
    ray.origin = origin;
    ray.direction = direction;
    return ray;
}

t_ray ray_from_to(t_vector from, t_vector to) {
    return new_ray(from, subtrac_vec_vec(to, from));
}


t_vector lighting_color(t_ray ray, t_hit hit, t_world* world) {
    t_vector res = multi_vec_vec(hit.object->material.albedo, ambient_light(world->ambient_light));
    for(int i = 0; i < world->point_lights_len; i++) {
        t_light* light = &world->point_lights[i];
        
        t_ray light_ray = ray_from_to(hit.point, light->position);
        t_interval interval;
        interval.min = 0.01;
        interval.max = vec_length(light_ray.direction);
        t_hit obstacle = ray_cast(light_ray,interval, world);
        if (obstacle.hit) {
            continue;
        }

        const double r_px = 0.1; // FIXME
        double intensity = pow(r_px, 2) / (length_squared(light_ray.direction)) * 255.*tan(light->intensity*PI/2);
        double point_brdf = brdf(vec_neg(light_ray.direction), vec_neg(ray.direction), hit.normal);
        res = add_vec_vec(res, multi_vec_doub(multi_vec_vec(multi_vec_doub(hit.object->material.albedo, point_brdf), light->color), intensity));
    }
    return res;
}

t_vector    ray_trace(t_ray ray, int depth, t_world *world)
{
    if (depth <= 0)
        return vec_init(0,0,0);

    t_interval interval;
    interval.min = 0.01;
    interval.max = 1000;

    t_hit hit = ray_cast(ray, interval, world);
    if (!hit.hit) {
        return ambient_light(world->ambient_light);
    }
    // TODO we don't need to recalculate it every frame
    t_vector lighting = lighting_color(ray, hit, world);
     // TODO instead of multiplying by brdf, sample brdf to get a better random vector?
    t_vector to_reflect = ray_trace(new_ray(hit.point, normalize_vec(random_on_hemisphere(hit.normal))), depth - 1, world);
    t_vector reflected = multi_vec_doub(multi_vec_vec(to_reflect, hit.object->material.albedo), brdf(vec_neg(to_reflect), vec_neg(ray.direction), hit.normal));
    return add_vec_vec(lighting, reflected);
    // return lighting;
}