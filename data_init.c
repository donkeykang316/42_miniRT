/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:21:18 by kaan              #+#    #+#             */
/*   Updated: 2024/08/06 12:53:49 by kaan             ###   ########.fr       */
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
    camera->lookfrom = vec_init(0, 1, 7);
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

void    world_init(t_object_list **world)
{
    world[0] = malloc(sizeof(t_object_list));
    world[0]->sphere = malloc(sizeof(t_sphere));
    world[0]->type = SPHERE;
    world[0]->quad = NULL;
    world[0]->tri = NULL;
    world[1] = malloc(sizeof(t_object_list));
    world[1]->sphere = malloc(sizeof(t_sphere));
    world[1]->type = SPHERE;
    world[1]->quad = NULL;
    world[1]->tri = NULL;
    world[0]->sphere->center = vec_init(0.0, -100.5, 2.0);
    world[0]->sphere->radius = 100.0;
    world[0]->sphere->material = malloc(sizeof(t_material));
    world[0]->sphere->material->albedo = vec_init(0.8, 0.8, 0.0);
    world[0]->sphere->material->type = LAMBERTIAN;
    world[0]->sphere->material->fuzz = 0.0;
    world[1]->sphere->center = vec_init(0.0, 0.0, 5.0);
    world[1]->sphere->radius = 0.5;
    world[1]->sphere->material = malloc(sizeof(t_material));
    world[1]->sphere->material->albedo = vec_init(1.0, 1.0, 1.0);
    world[1]->sphere->material->type = DIELECTRIC;
    world[1]->sphere->material->ref_idx = 1.5;
    world[2] = NULL;

    /*world[0] = malloc(sizeof(t_object_list));
    world[0]->sphere = NULL;
    world[0]->tri = NULL;
    world[0]->type = QUAD;
    world[0]->quad = malloc(sizeof(t_quad));
    world[0]->quad->q = vec_init(-3,-2, 5);
    world[0]->quad->u = vec_init(0, 0, -4);
    world[0]->quad->v = vec_init(0, 4, 0);
    world[0]->quad->material = malloc(sizeof(t_material));
    world[0]->quad->material->albedo = vec_init(5, 5, 5);
    world[0]->quad->material->type = LIGHT;
    world[0]->quad->material->fuzz = 0.0;
    world[1] = malloc(sizeof(t_object_list));
    world[1]->sphere = NULL;
    world[1]->quad = NULL;
    world[1]->type = QUAD;
    world[1]->quad = malloc(sizeof(t_quad));
    world[1]->quad->q = vec_init(-2,-2, 0);
    world[1]->quad->u = vec_init(4, 0, 0);
    world[1]->quad->v = vec_init(0, 4, 0);
    world[1]->quad->material = malloc(sizeof(t_material));
    world[1]->quad->material->albedo = vec_init(0.2, 1.0, 0.2);
    world[1]->quad->material->type = LAMBERTIAN;
    world[1]->quad->material->fuzz = 0.0;
    world[2] = malloc(sizeof(t_object_list));
    world[2]->sphere = NULL;
    world[2]->tri = NULL;
    world[2]->type = QUAD;
    world[2]->quad = malloc(sizeof(t_quad));
    world[2]->quad->q = vec_init(3,-2, 1);
    world[2]->quad->u = vec_init(0, 0, 4);
    world[2]->quad->v = vec_init(0, 4, 0);
    world[2]->quad->material = malloc(sizeof(t_material));
    world[2]->quad->material->albedo = vec_init(0.2, 0.2, 1.0);
    world[2]->quad->material->type = LAMBERTIAN;
    world[2]->quad->material->fuzz = 0.0;
    world[3] = malloc(sizeof(t_object_list));
    world[3]->sphere = NULL;
    world[3]->quad = NULL;
    world[3]->type = TRIANGLE;
    world[3]->tri = malloc(sizeof(t_quad));
    world[3]->tri->q = vec_init(0, 1, 2);
    world[3]->tri->u = vec_init(-1, 0, 4);
    world[3]->tri->v = vec_init(1, 0, 4);
    world[3]->tri->material = malloc(sizeof(t_material));
    world[3]->tri->material->albedo = vec_init(1.0, 0.5, 0.0);
    world[3]->tri->material->type = LAMBERTIAN;
    world[3]->tri->material->fuzz = 0.0;
    world[4] = malloc(sizeof(t_object_list));
    world[4]->sphere = malloc(sizeof(t_sphere));
    world[4]->type = SPHERE;
    world[4]->quad = NULL;
    world[4]->tri = NULL;
    world[5] = malloc(sizeof(t_object_list));
    world[5]->sphere = malloc(sizeof(t_sphere));
    world[5]->type = SPHERE;
    world[5]->quad = NULL;
    world[5]->tri = NULL;
    world[6] = malloc(sizeof(t_object_list));
    world[6]->sphere = malloc(sizeof(t_sphere));
    world[6]->type = SPHERE;
    world[6]->quad = NULL;
    world[6]->tri = NULL;
    world[7] = malloc(sizeof(t_object_list));
    world[7]->sphere = malloc(sizeof(t_sphere));
    world[7]->type = SPHERE;
    world[7]->quad = NULL;
    world[7]->tri = NULL;
    world[4]->sphere->center = vec_init(0.0, -100.5, 2.0);
    world[4]->sphere->radius = 100.0;
    world[4]->sphere->material = malloc(sizeof(t_material));
    world[4]->sphere->material->albedo = vec_init(0.8, 0.8, 0.0);
    world[4]->sphere->material->type = LAMBERTIAN;
    world[4]->sphere->material->fuzz = 0.0;
    world[5]->sphere->center = vec_init(0.0, 0.0, 5.0);
    world[5]->sphere->radius = 0.5;
    world[5]->sphere->material = malloc(sizeof(t_material));
    world[5]->sphere->material->albedo = vec_init(0.1, 0.2, 0.5);
    world[5]->sphere->material->type = LAMBERTIAN;
    world[5]->sphere->material->fuzz = 0.0;
    world[6]->sphere->center = vec_init(-1.0, 0.0, 5.0);
    world[6]->sphere->radius = 0.4;
    world[6]->sphere->material = malloc(sizeof(t_material));
    world[6]->sphere->material->albedo = vec_init(0.8, 0.8, 0.8);
    world[6]->sphere->material->type = METAL;
    world[6]->sphere->material->fuzz = 0.2;
    world[7]->sphere->center = vec_init(1.0, 0.0, 5.0);
    world[7]->sphere->radius = 0.5;
    world[7]->sphere->material = malloc(sizeof(t_material));
    world[7]->sphere->material->albedo = vec_init(0.8, 0.6, 0.2);
    world[7]->sphere->material->type = METAL;
    world[7]->sphere->material->fuzz = 0.6;
    world[8] = malloc(sizeof(t_object_list));
    world[8]->sphere = NULL;
    world[8]->quad = NULL;
    world[8]->tri = NULL;
    world[8]->type = CYLINDER;
    world[8]->cyl = malloc(sizeof(t_cylinder));
    world[8]->cyl->center = vec_init(3.0, 0.0, 3.0);
    world[8]->cyl->axis = vec_init(0.0, 1.0, 0.0);
    world[8]->cyl->radius = 1.0;
    world[8]->cyl->height = 1.0;
    world[8]->cyl->material = malloc(sizeof(t_material));
    world[8]->cyl->material->albedo = vec_init(0.5, 0.2, 0.1);
    world[8]->cyl->material->fuzz = 0;
    world[8]->cyl->material->type = LAMBERTIAN;
    world[9] = NULL;*/
}
