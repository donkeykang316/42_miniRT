/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrei <andrei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:51:30 by andrei            #+#    #+#             */
/*   Updated: 2024/08/23 00:30:01 by andrei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec vec_neg(t_vec v) {
    return vec(-v.x, -v.y, -v.z);
}
typedef struct s_hit {
    bool hit;
    t_vec point;
    t_vec normal;
    t_object* object;
    double distance;
} t_hit;

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

t_hit ray_cast_sphere(t_ray ray, t_interval interval, t_object* object) {
    t_vec    oc;
    double      a;
    double      h;
    double      c;
    double      discriminant;
    double      root;


    oc = sub_vec_vec(object->value.sphere.center, ray.origin);
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
    t_vec hit_point = at_ray(ray, root);
    return hit_object(
        object,
        root,
        hit_point,
        div_vec_double(sub_vec_vec(hit_point, object->value.sphere.center), object->value.sphere.radius)
    );
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

double brdf(t_vec incident, t_vec reflected, t_vec normal) {
    if (dot_vec(reflected, normal) < 0) // TODO || dot_vec(incident, normal) < 0
        return 0;

    double max_specular_angle = 0.5;
    double glossiness = 1;

    double matt = cos_angle_between(reflected, normal);

    double angle = angle_between(reflected, reflect(incident, normal));
    if (angle >= max_specular_angle) 
        return matt;
    double specular = pow(1 - angle / max_specular_angle, 2) * glossiness;
    return (specular + 1)* matt;
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
        double intensity = pow(r_px, 2) / (length_squared(light_ray.direction)) * 255.*tan(light->intensity*PI/2);
        double point_brdf = brdf(vec_neg(light_ray.direction), vec_neg(ray.direction), hit.normal);
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
    t_ray secondary_ray = new_ray(hit.point, normalize(random_on_hemisphere(hit.normal)));
    t_vec to_reflect = ray_trace(secondary_ray, depth - 1, world);
    t_vec reflected = mul_vec_double(mul_vec_vec(to_reflect, hit.object->material.albedo), brdf(secondary_ray.direction, vec_neg(ray.direction), hit.normal)); // FIXME potential bug -- -secondary_ray.direction
    return add_vec_vec(lighting, reflected);
    // return lighting;
}