#include "minirt.h"

t_vector    *sample_square(void)
{
    t_vector    *square;

    square = vec_init(random_double_a() - 0.5, random_double_a() - 0.5, 0);
    return (square);
}

t_ray   *get_grey(t_camera *camera, int i, int j)
{
    t_vector    *offset;
    t_ray       *ray;
    t_vector    *pixel_sample;

    offset = sample_square();
    pixel_sample = add_vec_vec(camera->pixel00_loc, add_vec_vec(add_vec_doub(camera->pixel_delta_u, (i + offset->x)), add_vec_doub(camera->pixel_delta_v, (j + offset->y))));
    ray = malloc(sizeof(t_ray));
    ray->origin = vec_init(camera->center->x, camera->center->y, camera->center->z);
    ray->direction = subtrac_vec_vec(pixel_sample, ray->origin);
    free (pixel_sample);
    free(offset);
    return (ray);
}

void    write_color(t_vector *pixel_color)
{
    double      r;
    double      g;
    double      b;
    int         rbyte;
    int         gbyte;
    int         bbyte;
    t_interval  intensity;

    r = pixel_color->x;
    g = pixel_color->y;
    b = pixel_color->z;
    intensity.min = 0.000;
    intensity.max = 0.999;
    rbyte = (int)(256 * clamp(&intensity, r));
    gbyte = (int)(256 * clamp(&intensity, g));
    bbyte = (int)(256 * clamp(&intensity, b));
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

void    render(t_camera *camera)
{
    t_vector        *pixel_color;
    t_ray           *ray;
    t_object_list   *world;
    int             i;
    int             j;
    int             sample;

    i = 0;
    j = 0;
    sample = 0;
    ray = malloc(sizeof(t_ray));
    world = malloc(sizeof(t_object_list));
    world_init(world);
    printf("P3\n%d %d\n255\n", (int)camera->image_width, (int)camera->image_height);
    while (j < camera->image_height)
    {
        i = 0;
        while (i < camera->image_width)
        {
            pixel_color = vec_init(0, 0, 0);
            while (sample < camera->samples_per_pixel)
            {
                ray = get_grey(camera, i, j);
                pixel_color = increment_vec_vec(pixel_color, ray_color(ray, world));
                free(ray->origin);
                free(ray->direction);
                free(ray);
                sample++;
            }
            write_color(pixel_color);
            free(pixel_color);
            i++;
        }
        j++;
    }
}
