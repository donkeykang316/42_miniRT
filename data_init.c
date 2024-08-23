/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrei <andrei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:21:18 by kaan              #+#    #+#             */
/*   Updated: 2024/08/23 19:13:17 by andrei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void    camera_init(t_camera *camera, t_camera_spec spec, int width, int height)
{
    double      focal_length;
    t_vec    viewport_u;
    t_vec    viewport_v;
    double      viewport_height;
    double      viewport_width;
    t_vec    viewport_upper_left;
    double      theta;
    double      h;
    t_vec    u;
    t_vec    v;
    t_vec    w;
 
    camera->image_width = width;
    camera->samples_per_pixel = 10000;
    camera->image_height = height;
    camera->aspect_ratio = (float)(width) / (float)(height);
    if (camera->image_height < 1)
        camera->image_height = 1;
    camera->hfov = spec.hfov;
    camera->lookfrom = spec.view_point;
    camera->vup = vec(0, 10, 0);
    theta = degrees_to_radians(camera->hfov / camera->aspect_ratio);
    h = tan(theta / 2);
    camera->center = camera->lookfrom;
    focal_length = length(spec.direction);
    viewport_height = 2.0 * h * focal_length;
    viewport_width = viewport_height * (double)(camera->image_width / camera->image_height);
    w = normalize(sub_vec_vec(vec(0,0,0),spec.direction));
    u = normalize(cross_vec(camera->vup, w));
    v = cross_vec(w, u);
    viewport_u = mul_vec_double(u, viewport_width);
    viewport_v = mul_vec_double(mul_vec_int(v, -1), viewport_height);
    camera->pixel_samples_scale = 1.0 / camera->samples_per_pixel;
    camera->max_depth = 50;
    viewport_upper_left = sub_vec_vec(camera->center, add_vec_vec(mul_vec_double(w, focal_length), add_vec_vec(div_vec_int(viewport_u, 2), div_vec_int(viewport_v, 2))));
    camera->pixel_delta_u = div_vec_int(viewport_u, camera->image_width);
    camera->pixel_delta_v = div_vec_int(viewport_v, camera->image_height);
    camera->pixel00_loc = add_vec_vec(viewport_upper_left, mul_vec_double(add_vec_vec(camera->pixel_delta_u, camera->pixel_delta_v), 0.5));
}

void    light_init(t_light *light)
{
    t_vec position = vec(-2, 5, 0);
    double intensity = 1.0;

    light->position = vec(position.x, position.y, position.z);
    light->intensity = intensity;
    light->color = vec(0.0 + intensity, 0.0 + intensity, 0.0 + intensity);
}
