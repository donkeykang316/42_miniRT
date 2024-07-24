#include "minirt.h"

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

t_vector    *ray_color(t_ray *ray, t_object_list *world)
{
    t_hit_rec   *rec;
    t_vector    *ray_color;
    t_vector    *color1;
    t_vector    *color2;
    t_vector    *unit_direction;
    t_interval  interval;
    double       a;

    ray_color = malloc(sizeof(t_vector));
    rec = malloc(sizeof(t_hit_rec));
    interval.min = 0;
    interval.max = INFINITY;
    if (hit_objects(ray, &interval, rec, world))
    {
        color1 = vec_init(1, 1, 1);
        ray_color = multi_vec_doub(add_vec_vec(rec->normal, color1), 0.5);
        free(color1);
        free(rec->normal);
        free(rec->p);
        free(rec);
        return (ray_color);
    }
    color1 = vec_init(1.0, 1.0, 1.0);
    color2 = vec_init(0.5, 0.7, 1.0);
    unit_direction = vec_init(ray->direction->x, ray->direction->y, ray->direction->z);
    a = 0.5 * (unit_direction->y + 1.0);
    ray_color = add_vec_vec(multi_vec_doub(color1, (1.0 - a)), multi_vec_doub(color2, a));
    free(color1);
    free(color2);
    free(unit_direction);
    /*if (rec->normal)
        free(rec->normal);
    if (rec->p)
        free(rec->p);
    free(rec);*/
    return (ray_color);
}

void    render(t_img *image, t_camera *camera, t_viewport *viewport)
{
    t_vector        *pixel_center;
    t_vector        *pixel_color;
    t_ray           *ray;
    t_object_list   *world;
    int         i;
    int         j;

    i = 0;
    j = 0;
    ray = malloc(sizeof(t_ray));
    world = malloc(sizeof(t_object_list));
    world_init(world);
    printf("P3\n%d %d\n255\n", (int)image->image_width, (int)image->image_height);
    while (j < image->image_height)
    {
        i = 0;
        while (i < image->image_width)
        {
            pixel_center = add_vec_vec(viewport->pixel00_loc, add_vec_vec(multi_vec_int(viewport->pixel_delta_u, i), multi_vec_int(viewport->pixel_delta_v, j)));
            ray->direction = subtrac_vec_vec(pixel_center, camera->camera_center);
            ray->origin = vec_init(camera->camera_center->x, camera->camera_center->y, camera->camera_center->z);
            pixel_color = ray_color(ray, world);
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
