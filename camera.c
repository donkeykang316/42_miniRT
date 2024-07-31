#include "minirt.h"

t_vector    sample_square(void)
{
    t_vector    square;

    square = vec_init(random_double() - 0.5, random_double() - 0.5, 0);
    return (square);
}

t_ray   get_ray(t_camera camera, int i, int j)
{
    t_vector    offset;
    t_ray       ray;
    t_vector    pixel_sample;

    offset = sample_square();
    pixel_sample = add_vec_vec(camera.pixel00_loc, add_vec_vec(multi_vec_doub(camera.pixel_delta_u, (i + offset.x)), multi_vec_doub(camera.pixel_delta_v, (j + offset.y))));
    ray.origin = vec_init(camera.center.x, camera.center.y, camera.center.z);
    ray.direction = subtrac_vec_vec(pixel_sample, ray.origin);
    return (ray);
}

void    write_color(t_vector pixel_color)
{
    double      r;
    double      g;
    double      b;
    int         rbyte;
    int         gbyte;
    int         bbyte;
    t_interval  intensity;

    r = linear_to_gamma(pixel_color.x);
    g = linear_to_gamma(pixel_color.y);
    b = linear_to_gamma(pixel_color.z);
    intensity.min = 0.000;
    intensity.max = 0.999;
    rbyte = (int)(256 * clamp(intensity, r));
    gbyte = (int)(256 * clamp(intensity, g));
    bbyte = (int)(256 * clamp(intensity, b));
    printf("%d %d %d\n", rbyte, gbyte, bbyte);

}

t_vector    ray_color(t_ray ray, t_hit_rec *rec, int depth, t_object_list *world)
{
    t_vector    r_color;
    t_vector    color1;
    t_vector    color2;
    t_vector    unit_direction;
    t_interval  interval;
    t_ray       scattered;
    t_vector    attenuation;
    double       a;

    (void)attenuation;
    if (depth <= 0)
        return (vec_init(0, 0, 0));
    interval.min = 0.001;
    interval.max = INFINITY;
    if (hit_objects(ray, interval, rec, world))
    {
        if (world->sphere[rec->object_index]->material->type == LAMBERTIAN)
        {
            if (scatter_lambertian(ray, rec, attenuation, scattered, rec->material))
            {
                //print_vector(rec->material->albedo);
                t_vector albedo = vec_init(rec->material->albedo.x, rec->material->albedo.y, rec->material->albedo.z);
                t_vector    r_color1 = ray_color(scattered, rec, depth - 1, world);
                r_color = multi_vec_vec(albedo, r_color1);
                //print_vector(r_color);
                return (r_color);
            }
        }
        else if (world->sphere[rec->object_index]->material->type == METAL)
        {
            if (scatter_metal(ray, rec, attenuation, scattered, rec->material))
            {
                t_vector    r_color1 = ray_color(scattered, rec, depth - 1, world);
                //print_vector(r_color1);
                r_color = multi_vec_vec(rec->material->albedo, r_color1);
                return (r_color);
            }
        }
        r_color = vec_init(0, 0, 0);
        return (r_color);
    }
    color1 = vec_init(1.0, 1.0, 1.0);
    color2 = vec_init(0.5, 0.7, 1.0);
    unit_direction = normalize_vec(ray.direction);
    a = 0.5 * (unit_direction.y + 1.0);
    r_color = add_vec_vec(multi_vec_doub(color1, (1.0 - a)), multi_vec_doub(color2, a));
    return (r_color);
}

void    render(t_camera camera)
{
    t_vector        pixel_color;
    t_ray           ray;
    t_object_list   world;
    t_hit_rec       rec;
    int             i;
    int             j;
    int             sample;

    i = 0;
    j = 0;
    sample = 0;
    world_init(&world);
    //printf("P3\n%d %d\n255\n", (int)camera.image_width, (int)camera.image_height);
    while (j < camera.image_height)
    {
        //ft_putstr_fd("Remaining line ", 2);
        //ft_putstr_fd("--------------------------", 2);
        //ft_putnbr_fd(camera.image_height - j, 2);
        //ft_putstr_fd("\n", 2);
        i = 0;
        while (i < camera.image_width)
        {
            pixel_color = vec_init(0, 0, 0);
            sample = 0;
            while (sample < camera.samples_per_pixel)
            {
                ray = get_ray(camera, i, j);
                pixel_color = increment_vec_vec(pixel_color, ray_color(ray, &rec, camera.max_depth, &world));
                sample++;
            }
            //print_vector(pixel_color);
            //write_color(multi_vec_doub(pixel_color, camera.pixel_samples_scale));
            i++;
        }
        j++;
    }
}
