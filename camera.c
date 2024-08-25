/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apago <apago@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:20:58 by kaan              #+#    #+#             */
/*   Updated: 2024/08/25 19:34:37 by apago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec    sample_square(void)
{
    t_vec    square;

    square = vec(random_double() - 0.5, random_double() - 0.5, 0);
    return (square);
}

t_ray   get_ray(t_camera camera, int i, int j)
{
    t_vec    offset;
    t_ray       ray;
    t_vec    pixel_sample;

    offset = sample_square();
    pixel_sample = add_vec_vec(camera.pixel00_loc, add_vec_vec(mul_vec_double(camera.pixel_delta_u, (i + offset.x)), mul_vec_double(camera.pixel_delta_v, (j + offset.y))));
    ray.origin = camera.center;
    ray.direction = sub_vec_vec(pixel_sample, ray.origin);
    return (ray);
}

t_vec gamma_correct(t_vec pixel_color) {

    double      r;
    double      g;
    double      b;
    t_interval  intensity;
    t_vec result;

    r = linear_to_gamma(pixel_color.x);
    g = linear_to_gamma(pixel_color.y);
    b = linear_to_gamma(pixel_color.z);
    intensity.min = 0.000;
    intensity.max = 0.999;
    result.x = clamp(intensity, r);
    result.y = clamp(intensity, g);
    result.z = clamp(intensity, b);
    return result;
}

void    write_color(int fd, t_vec pixel_color)
{
    t_vec rgb = gamma_correct(pixel_color);
    dprintf(fd, "%d %d %d\n", (int)(rgb.x * 256), (int)(rgb.y * 256), (int)(rgb.z * 256));
}

t_vec contrast(double value) {
    return vec(fmax(0, value),0,fmax(0, -value));
}

void    render(t_world* world, t_camera camera, t_image image)
{
    t_vec        pixel_color;
    t_ray           ray;
    int             i;
    int             j;

    i = 0;
    j = 0;

    world->camera.view_point = camera.center;
    camera_init(&camera, world->camera, camera.image_width, camera.image_height);
    camera.max_depth = 1;

    while (j < image.height)
    {
        i = 0;
        while (i < image.width)
        {
            ray = get_ray(camera, i, j);
            pixel_color = ray_trace(ray, camera.max_depth, world);

            // distance debug
            // double t = fabs(atan(fmin(rec.hit_distance,100))/atan(100));
            // double d = (rec.hit_distance - floor(10*rec.hit_distance)/10)*10;
            // pixel_color = vec_init(t,t,t);

            // normal debug
            // pixel_color = contrast(dot_vec(vec_init(0,0,1), rec.normal)/vec_length(rec.normal));

            // pixel_color = multi_vec_vec(normalize_vec(rec.hit_point),normalize_vec(rec.hit_point));

            image.data[j * image.width + i] = add_vec_vec(image.data[j * image.width + i], pixel_color);
            i++;
        }
        j++;
    }
}
