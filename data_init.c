#include "minirt.h"

void    camera_init(t_camera *camera)
{
    double      focal_length;
    t_vector    *viewport_u;
    t_vector    *viewport_v;
    double      viewport_height;
    double      viewport_width;
    t_vector    *viewport_upper_left;
    t_vector    *vec;

    camera->aspect_ratio = 16.0 / 9.0;
    camera->image_width = 400;
    camera->samples_per_pixel = 100;
    camera->image_height = (int)(camera->image_width / camera->aspect_ratio);
    if (camera->image_height < 1)
        camera->image_height = 1;
    focal_length = 1.0;
    vec = vec_init(0, 0, focal_length);
    viewport_height = 2.0;
    viewport_width = viewport_height * (double)(camera->image_width / camera->image_height);
    viewport_u = vec_init(viewport_width, 0, 0);
    viewport_v = vec_init(0, -(viewport_height), 0);
    camera->center = vec_init(0, 0, 0);
    camera->pixel_samples_scale = 1.0 / camera->samples_per_pixel;
    camera->max_depth = 50;
    viewport_upper_left = subtrac_vec_vec(camera->center, add_vec_vec(vec, add_vec_vec(divi_vec_int(viewport_u, 2), divi_vec_int(viewport_v, 2))));
    camera->pixel_delta_u = divi_vec_int(viewport_u, camera->image_width);
    camera->pixel_delta_v = divi_vec_int(viewport_v, camera->image_height);
    camera->pixel00_loc = add_vec_vec(viewport_upper_left, multi_vec_doub(add_vec_vec(camera->pixel_delta_u, camera->pixel_delta_v), 0.5));
    free(vec);
}

void    world_init(t_object_list *world)
{
    t_material     *material_ground;
    t_material     *material_center;
    t_material     *material_left;
    t_material     *material_right;

    material_ground = malloc(sizeof(t_material));
    material_center = malloc(sizeof(t_material));
    material_left = malloc(sizeof(t_material));
    material_right = malloc(sizeof(t_material));
    material_ground->albedo = vec_init(0.8, 0.8, 0.0);
    material_center->albedo = vec_init(0.1, 0.2, 0.5);
    material_left->albedo = vec_init(0.8, 0.8, 0.8);
    material_right->albedo = vec_init(0.8, 0.6, 0.2);
    world->t_sphere = malloc(4 * sizeof(t_sphere));
    world->t_sphere[0] = malloc(sizeof(t_sphere));
    world->t_sphere[1] = malloc(sizeof(t_sphere));
    world->t_sphere[2] = malloc(sizeof(t_sphere));
    world->t_sphere[3] = malloc(sizeof(t_sphere));
    world->t_sphere[0]->center = vec_init(0.0, -100.5, -1.0);
    world->t_sphere[0]->radius = 100.0;
    world->t_sphere[0]->material = material_ground;
    world->t_sphere[1]->center = vec_init(0.0, 0.0, -1.2);
    world->t_sphere[1]->radius = 0.5;
    world->t_sphere[1]->material = material_center;
    world->t_sphere[2]->center = vec_init(-1.0, 0.0, -1.0);
    world->t_sphere[2]->radius = 0.5;
    world->t_sphere[2]->material = material_left;
    world->t_sphere[3]->center = vec_init(1.0, 0.0, -1.0);
    world->t_sphere[3]->radius = 0.5;
    world->t_sphere[3]->material = material_right;
}
