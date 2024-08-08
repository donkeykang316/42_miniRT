/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:21:18 by kaan              #+#    #+#             */
/*   Updated: 2024/08/08 18:22:19 by kaan             ###   ########.fr       */
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
    camera->vfov = 90;
    camera->lookfrom = vec_init(0, 2, 9);
    camera->lookat = vec_init(0, 0, 0);
    camera->vup = vec_init(0, 10, 0);
    theta = degrees_to_radians(camera->vfov);
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
    light->albedo = vec_init(0.0 + intensity, 0.0 + intensity, 0.0 + intensity);
}

t_quad  *quad_init(t_vector coord, t_vector normal, t_vector color, t_material_type material)
{
    t_quad  *quad;

    quad = malloc(sizeof(t_quad));
    quad->q = vec_init(coord.x, coord.y, coord.z);
    quad->u = vec_init(normal.x, normal.y, normal.z);
    quad->v = vec_init(0, 4, 0);
    quad->material = malloc(sizeof(t_material));
    quad->material->albedo = vec_init(color.x, color.y, color.z);
    quad->material->type = material;
    quad->material->fuzz = 0.0;
    quad->material->ref_idx = 0.0;
    return (quad);
}

t_tri   *tri_init(t_vector coord, t_vector normal, t_vector color, t_material_type material)
{
    t_tri   *tri;

    tri = malloc(sizeof(t_tri));
    tri->q = vec_init(coord.x, coord.y, coord.z);
    tri->u = vec_init(normal.x, normal.y, normal.z);
    tri->v = vec_init(1, 0, 4);
    tri->material = malloc(sizeof(t_material));
    tri->material->albedo = vec_init(color.x, color.y, color.z);
    tri->material->type = material;
    tri->material->fuzz = 0.0;
    tri->material->ref_idx = 0.0;
    return (tri);
}

t_sphere    *sphere_init(t_vector center, double diameter, t_vector color, t_material_type material)
{
    t_sphere    *sphere;

    sphere = malloc(sizeof(t_sphere));
    sphere->center = vec_init(center.x, center.y, center.z);
    sphere->radius = diameter;
    sphere->material = malloc(sizeof(t_material));
    sphere->material->albedo = vec_init(color.x, color.y, color.z);
    sphere->material->type = material;
    sphere->material->fuzz = 0.0;
    sphere->material->ref_idx = 1.5;
    return (sphere);
}

t_cylinder  *cylinder_init(t_vector center, t_vector normal, double diameter, double height, t_vector color, t_material_type material)
{
    t_cylinder  *cylinder;

    cylinder = malloc(sizeof(t_cylinder));
    cylinder->center = vec_init(center.x, center.y, center.z);
    cylinder->axis = vec_init(normal.x, normal.y, normal.z);
    cylinder->radius = diameter;
    cylinder->height = height;
    cylinder->material = malloc(sizeof(t_material));
    cylinder->material->albedo = vec_init(color.x, color.y, color.z);
    cylinder->material->type = material;
    cylinder->material->fuzz = 0.0;
    cylinder->material->ref_idx = 0.0;
    return (cylinder);
}

void    world_init(t_object_list **world)
{
    world[0] = malloc(sizeof(t_object_list));
    world[0]->type = QUAD;
    world[0]->quad = quad_init(vec_init(-3,-2, 5), vec_init(0, 0, -4), vec_init(1, 0.2, 0.2), LAMBERTIAN);
    world[0]->sphere = NULL;
    world[0]->tri = NULL;
    world[0]->cyl = NULL;
    world[1] = malloc(sizeof(t_object_list));
    world[1]->type = QUAD;
    world[1]->quad = quad_init(vec_init(-2,-2, 0), vec_init(4, 0, 0), vec_init(0.2, 1.0, 0.2), LAMBERTIAN);
    world[1]->sphere = NULL;
    world[1]->tri = NULL;
    world[1]->cyl = NULL;
    world[2] = malloc(sizeof(t_object_list));
    world[2]->type = QUAD;
    world[2]->quad = quad_init(vec_init(3,-2, 1), vec_init(0, 0, 4), vec_init(0.2, 0.2, 1.0), LAMBERTIAN);
    world[2]->sphere = NULL;
    world[2]->tri = NULL;
    world[2]->cyl = NULL;
    world[3] = malloc(sizeof(t_object_list));
    world[3]->type = TRIANGLE;
    world[3]->tri = tri_init(vec_init(0, 1, 2), vec_init(-1, 0, 4), vec_init(1.0, 0.5, 0.0), LAMBERTIAN);
    world[3]->sphere = NULL;
    world[3]->quad = NULL;
    world[3]->cyl = NULL;
    world[4] = malloc(sizeof(t_object_list));    
    world[4]->type = SPHERE;
    world[4]->sphere = sphere_init(vec_init(0.0, -100.5, 2.0), 100.0, vec_init(0.8, 0.8, 0.0), LAMBERTIAN);
    world[4]->quad = NULL;
    world[4]->tri = NULL;
    world[4]->cyl = NULL;
    world[5] = malloc(sizeof(t_object_list));
    world[5]->type = SPHERE;
    world[5]->sphere = sphere_init(vec_init(0.0, 0.0, 5.0), 0.5, vec_init(0.1, 0.2, 0.5), LAMBERTIAN);
    world[5]->quad = NULL;
    world[5]->tri = NULL;
    world[5]->cyl = NULL;
    world[6] = malloc(sizeof(t_object_list));
    world[6]->type = SPHERE;
    world[6]->sphere = sphere_init(vec_init(-1.0, 0.0, 5.0), 0.4, vec_init(0.8, 0.8, 0.8), METAL);
    world[6]->quad = NULL;
    world[6]->tri = NULL;
    world[6]->cyl = NULL;
    world[7] = malloc(sizeof(t_object_list));
    world[7]->type = SPHERE;
    world[7]->sphere = sphere_init(vec_init(1.0, 0.0, 5.0), 0.5, vec_init(1.0, 1.0, 1.0), METAL);
    world[7]->quad = NULL;
    world[7]->tri = NULL;
    world[7]->cyl = NULL;
    world[8] = malloc(sizeof(t_object_list));
    world[8]->type = CYLINDER;
    world[8]->cyl = cylinder_init(vec_init(3.0, 0.0, 3.0), vec_init(0.0, 1.0, 0.0), 1.0, 1.0, vec_init(0.5, 0.2, 0.1), LAMBERTIAN);
    world[8]->quad = NULL;
    world[8]->tri = NULL;
    world[8]->sphere = NULL;
    world[9] = malloc(sizeof(t_object_list));
    world[9]->type = SPHERE;
    world[9]->sphere = sphere_init(vec_init(0.0, 3.0, 0.0), 1.0, vec_init(1.0, 1.0, 1.0), LAMBERTIAN);
    world[9]->quad = NULL;
    world[9]->tri = NULL;
    world[9]->cyl = NULL;
    world[10] = NULL;
}
