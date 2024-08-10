/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:20:58 by kaan              #+#    #+#             */
/*   Updated: 2024/08/10 14:59:59 by kaan             ###   ########.fr       */
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
    ray.origin = vec_init(camera.center.x, camera.center.y, camera.center.z);
    ray.direction = subtrac_vec_vec(pixel_sample, ray.origin);
    return (ray);
}

void    write_color(int fd, t_vector pixel_color)
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
    dprintf(fd, "%d %d %d\n", rbyte, gbyte, bbyte);
}

void    render(t_camera camera, t_image image)
{
    t_vector        pixel_color;
    t_ray           ray;
    t_object        *world;
    t_hit_rec       rec;
    int             i;
    int             j;
    int             sample;

    i = 0;
    j = 0;
    sample = 0;

    // int quantity = 11;

    world = world_init();
    while (j < image.height)
    {
        //ft_putstr_fd("Remaining line ", 2);
        //ft_putstr_fd("--------------------------", 2);
        //ft_putnbr_fd(camera.image_height - j, 2);
        //ft_putstr_fd("\n", 2);
        i = 0;
        while (i < image.width)
        {
            pixel_color = vec_init(0, 0, 0);
            sample = 0;
            while (sample < camera.samples_per_pixel)
            {
                ray = get_ray(camera, i, j);
                pixel_color = increment_vec_vec(pixel_color, ray_color(&ray, &rec, camera.max_depth, world));
                sample++;
            }
            image.data[j * image.width + i] = multi_vec_doub(pixel_color, camera.pixel_samples_scale);
            i++;
        }
        j++;
    }
    free(world);
}
