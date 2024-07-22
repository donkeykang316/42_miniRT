#include "minirt.h"

void    image_init(t_img  *image)
{
    image->aspect_ratio = 16.0 / 9.0;
    image->image_width = 400;
    image->image_height = (int)(image->image_width / image->aspect_ratio);
    if (image->image_height < 1)
        image->image_height = 1;
}

void    camera_init(t_camera *camera, t_img *image)
{
    camera->focal_length = 1.0;
    camera->viewport_height = 2.0;
    camera->viewport_width = camera->viewport_height * (double)(image->image_width / image->image_height);
    camera->camera_center = vec_init(0, 0, 0);
}

void   viewport_init(t_viewport *viewport, t_img *image, t_camera *camera)
{
    t_vector    *vec;

    vec = vec_init(0, 0, camera->focal_length);
    viewport->viewport_u = vec_init(camera->viewport_width, 0, 0);
    viewport->viewport_v = vec_init(0, -(camera->viewport_height), 0);
    viewport->pixel_delta_u = divi_vec_int(viewport->viewport_u, image->image_width);
    viewport->pixel_delta_v = divi_vec_int(viewport->viewport_v, image->image_height);
    viewport->viewport_upper_left = subtrac_vec_vec(camera->camera_center, add_vec_vec(vec, add_vec_vec(divi_vec_int(viewport->viewport_u, 2), divi_vec_int(viewport->viewport_v, 2))));
    viewport->pixel00_loc = add_vec_vec(viewport->viewport_upper_left, multi_vec_doub(add_vec_vec(viewport->pixel_delta_u, viewport->pixel_delta_v), 0.5));
    free(vec);
}

bool    hit_sphere(t_vector *center, double radius, t_ray *ray)
{
    t_sphere    *sphere;
    double      discriminant;

    sphere = malloc(sizeof(t_sphere));
    sphere->oc = subtrac_vec_vec(center, ray->origin);
    sphere->a = dot_vec(ray->direction, ray->direction);
    sphere->b = -2.0 * dot_vec(ray->direction, sphere->oc);
    sphere->c = dot_vec(sphere->oc, sphere->oc) - (radius * radius);
    discriminant = sphere->b * sphere->b - 4 * sphere->a * sphere->c;
    free(sphere);
    if (discriminant >= 0)
        return (true);
    return (false);
}
