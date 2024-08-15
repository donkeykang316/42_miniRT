/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrei <andrei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:20:58 by kaan              #+#    #+#             */
/*   Updated: 2024/08/15 21:09:23 by andrei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
    ray.origin = camera.center;
    ray.direction = subtrac_vec_vec(pixel_sample, ray.origin);
    return (ray);
}

t_vector gamma_correct(t_vector pixel_color) {

    double      r;
    double      g;
    double      b;
    t_interval  intensity;
    t_vector result;

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

void    write_color(int fd, t_vector pixel_color)
{
    t_vector rgb = gamma_correct(pixel_color);
    dprintf(fd, "%d %d %d\n", (int)(rgb.x * 256), (int)(rgb.y * 256), (int)(rgb.z * 256));
}

t_vector contrast(double value) {
    return vec_init(fmax(0, value),0,fmax(0, -value));
}

void    render(t_world* world, t_camera camera, t_image image)
{
    t_vector        pixel_color;
    t_ray           ray;
    t_hit_rec       rec;
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
            rec.hit_distance = INFINITY;
            ray = get_ray(camera, i, j);
            pixel_color = ray_color(&ray, &rec, camera.max_depth, world);

            // distance debug
            // double t = fabs(atan(rec.hit_distance)/PI*2);
            // double d = (rec.hit_distance - floor(10*rec.hit_distance)/10)*10;
            // pixel_color = vec_init(d*0.5+t*0.5,t,t);

            // normal debug
            pixel_color = contrast(dot_vec(vec_init(1,0,0), rec.normal)/vec_length(rec.normal));

            image.data[j * image.width + i] = pixel_color;
            i++;
        }
        j++;
    }
}
