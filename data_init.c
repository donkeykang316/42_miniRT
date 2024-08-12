/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrei <andrei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:21:18 by kaan              #+#    #+#             */
/*   Updated: 2024/08/12 20:04:07 by andrei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void    camera_init(t_camera *camera, int width, int height)
{
    double      focal_length;
    t_vector    viewport_u;
    t_vector    viewport_v;
    double      viewport_height;
    double      viewport_width;
    t_vector    viewport_upper_left;
    double      theta;
    double      h;
    t_vector    u;
    t_vector    v;
    t_vector    w;

    camera->image_width = width;
    camera->samples_per_pixel = 100;
    camera->image_height = height;
    camera->aspect_ratio = (float)(width) / (float)(height);
    if (camera->image_height < 1)
        camera->image_height = 1;
    camera->hfov = 90;
    camera->lookfrom = vec_init(0, 2, 9);
    camera->lookat = vec_init(0, 0, 0);
    camera->vup = vec_init(0, 10, 0);
    theta = degrees_to_radians(camera->hfov / camera->aspect_ratio);
    h = tan(theta / 2);
    camera->center = camera->lookfrom;
    focal_length = vec_length(subtrac_vec_vec(camera->lookfrom, camera->lookat));
    viewport_height = 2.0 * h * focal_length;
    viewport_width = viewport_height * (double)(camera->image_width / camera->image_height);
    w = unit_vector(subtrac_vec_vec(camera->lookfrom, camera->lookat));
    u = unit_vector(cross_vec(camera->vup, w));
    v = cross_vec(w, u);
    viewport_u = multi_vec_doub(u, viewport_width);
    viewport_v = multi_vec_doub(multi_vec_int(v, -1), viewport_height);
    camera->pixel_samples_scale = 1.0 / camera->samples_per_pixel;
    camera->max_depth = 50;
    viewport_upper_left = subtrac_vec_vec(camera->center, add_vec_vec(multi_vec_doub(w, focal_length), add_vec_vec(divi_vec_int(viewport_u, 2), divi_vec_int(viewport_v, 2))));
    camera->pixel_delta_u = divi_vec_int(viewport_u, camera->image_width);
    camera->pixel_delta_v = divi_vec_int(viewport_v, camera->image_height);
    camera->pixel00_loc = add_vec_vec(viewport_upper_left, multi_vec_doub(add_vec_vec(camera->pixel_delta_u, camera->pixel_delta_v), 0.5));
}

void    light_init(t_light *light)
{
    t_vector position = vec_init(-2, 5, 0);
    double intensity = 1.0;

    light->position = vec_init(position.x, position.y, position.z);
    light->intensity = intensity;
    light->color = vec_init(0.0 + intensity, 0.0 + intensity, 0.0 + intensity);
}

t_object  quad_init(t_vector coord, t_vector normal, t_vector color, t_material material)
{
    t_object  quad;

    quad.type = QUAD;
    quad.value.quad.q = coord;
    quad.value.quad.u = normal;
    quad.value.quad.v = vec_init(0, 4, 0);
    quad.material = material;
    quad.material.albedo = color;
    return (quad);
}

t_object   tri_init(t_vector coord, t_vector normal, t_vector color, t_material material)
{
    t_object   tri;

    tri.type = TRIANGLE;
    tri.value.triangle.q = coord;
    tri.value.triangle.u = normal;
    tri.value.triangle.v = vec_init(1, 0, 4);
    tri.material = material;
    tri.material.albedo = color;
    return (tri);
}

t_object    sphere_init(t_vector center, double diameter, t_vector color, t_material material)
{
    t_object  sphere;

    sphere.type = SPHERE;
    sphere.value.sphere.center = center;
    sphere.value.sphere.radius = diameter;
    sphere.material = material;
    sphere.material.albedo = color;
    return (sphere);
}

t_object  cylinder_init(t_vector center, t_vector normal, double diameter, double height, t_vector color, t_material material)
{
    t_object  cylinder;

    cylinder.type = CYLINDER;
    cylinder.value.cyllinder.center = center;
    cylinder.value.cyllinder.axis = normal;
    cylinder.value.cyllinder.radius = diameter;
    cylinder.value.cyllinder.height = height;
    cylinder.material = material;
    cylinder.material.albedo = color;
    return (cylinder);
}

t_material material_init(t_material_type type) {
    t_material res;
    res.type = type;
    res.albedo = vec_init(0.5,0.5,0.5);
    res.fuzz = 0.1;
    res.ref_idx = 0.5;
    return res;
}

t_object*    world_init()
{
    t_material lambertian = material_init(LAMBERTIAN);
    t_material metal = material_init(METAL);

    t_object* world = calloc(11, sizeof(t_object));
    world[0] = quad_init(vec_init(-3,-2, 5), vec_init(0, 0, -4), vec_init(1, 0.2, 0.2), lambertian);
    world[1] = quad_init(vec_init(-2,-2, 0), vec_init(4, 0, 0), vec_init(0.2, 1.0, 0.2), lambertian);
    world[2] = quad_init(vec_init(3,-2, 1), vec_init(0, 0, 4), vec_init(0.2, 0.2, 1.0), lambertian);
    world[3] = tri_init(vec_init(0, 1, 2), vec_init(-1, 0, 4), vec_init(1.0, 0.5, 0.0), lambertian);
    world[4] = sphere_init(vec_init(0.0, -100.5, 2.0), 100.0, vec_init(0.8, 0.8, 0.0), lambertian);
    world[5] = sphere_init(vec_init(0.0, 0.0, 5.0), 0.5, vec_init(0.1, 0.2, 0.5), lambertian);
    world[6] = sphere_init(vec_init(-1.0, 0.0, 5.0), 0.4, vec_init(0.8, 0.8, 0.8), metal);
    world[7] = sphere_init(vec_init(1.0, 0.0, 5.0), 0.5, vec_init(1.0, 1.0, 1.0), metal);
    world[8] = cylinder_init(vec_init(3.0, 0.0, 3.0), vec_init(0.0, 1.0, 0.0), 1.0, 1.0, vec_init(0.5, 0.2, 0.1), lambertian);
    world[9] = sphere_init(vec_init(0.0, 3.0, 0.0), 1.0, vec_init(1.0, 1.0, 1.0), lambertian);
    return world;
}
