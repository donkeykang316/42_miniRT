#include "minirt.h"

t_vector    *ray_color(t_ray *ray)
{
    t_vector    *ray_color;
    t_vector    *unit_direction;
    double       a;
    t_vector    *color1;
    t_vector    *color2;
    t_vector    *center;
    
    center = vec_init(0, 0, -1);
    if (hit_sphere(center, 0.5, ray))
    {
        ray_color = vec_init(1, 0, 0);
        free(center);
        return (ray_color);
    }
    free(center);
    ray_color = malloc(sizeof(t_vector));
    color1 = vec_init(1.0, 1.0, 1.0);
    color2 = vec_init(0.5, 0.7, 1.0);
    unit_direction = vec_init(ray->direction->x, ray->direction->y, ray->direction->z);
    a = 0.5 * (unit_direction->y + 1.0);
    ray_color = add_vec_vec(multi_vec_doub(color1, (1.0 - a)), multi_vec_doub(color2, a));
    free(color1);
    free(color2);
    free(unit_direction);
    return (ray_color);
}



void    write_color(t_vector *pixel_color)
{
    double  r;
    double  g;
    double  b;
    int     rbyte;
    int     gbyte;
    int     bbyte;

    r = pixel_color->x;
    g = pixel_color->y;
    b = pixel_color->z;

    rbyte = (int)(255.999 * r);
    gbyte = (int)(255.999 * g);
    bbyte = (int)(255.999 * b);
    printf("%d %d %d\n", rbyte, gbyte, bbyte);

}

void    render(t_img *image, t_camera *camera, t_viewport *viewport)
{
    t_vector    *pixel_center;
    t_vector    *pixel_color;
    t_ray       *ray;
    int         i;
    int         j;

    i = 0;
    j = 0;
    ray = malloc(sizeof(t_ray));
    printf("P3\n%d %d\n255\n", (int)image->image_width, (int)image->image_height);
    while (j < image->image_height)
    {
        i = 0;
        while (i < image->image_width)
        {
            pixel_center = add_vec_vec(viewport->pixel00_loc, add_vec_vec(multi_vec_int(viewport->pixel_delta_u, i), multi_vec_int(viewport->pixel_delta_v, j)));
            ray->direction = subtrac_vec_vec(pixel_center, camera->camera_center);
            ray->origin = vec_init(camera->camera_center->x, camera->camera_center->y, camera->camera_center->z);
            pixel_color = ray_color(ray);
            write_color(pixel_color);
            free(pixel_center);
            free(pixel_color);
            free(ray->origin);
            free(ray->direction);
            i++;
        }
        j++;
    }
}

void    secene_render(t_img *image, t_camera *camera, t_viewport *viewport)
{
    image_init(image);
    camera_init(camera, image);
    viewport_init(viewport, image, camera);
    render(image, camera, viewport);
}
