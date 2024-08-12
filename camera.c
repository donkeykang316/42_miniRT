/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrei <andrei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:20:58 by kaan              #+#    #+#             */
/*   Updated: 2024/08/12 19:44:03 by andrei           ###   ########.fr       */
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

void    render(t_world* world, t_camera camera, t_image image)
{
    t_vector        pixel_color;
    t_ray           ray;
    t_hit_rec       rec;
    int             i;
    int             j;

    i = 0;
    j = 0;

    while (j < image.height)
    {
        i = 0;
        while (i < image.width)
        {
            ray = get_ray(camera, i, j);
            pixel_color = ray_color(&ray, &rec, camera.max_depth, world);
            image.data[j * image.width + i] = pixel_color;
            i++;
        }
        j++;
    }
}
