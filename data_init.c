/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrei <andrei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:21:18 by kaan              #+#    #+#             */
/*   Updated: 2024/08/20 22:02:25 by andrei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void    camera_init(t_camera *camera, t_camera_spec spec, int width, int height)
{
    double      focal_length;
    t_vector    viewport_u;
    t_vector    viewport_v;
    double      viewport_height;
    double      viewport_width;
    t_vector    viewport_upper_left;
    double      theta;
    double      h;
    t_vector    u;
    t_vector    v;
    t_vector    w;
 
    camera->image_width = width;
    camera->samples_per_pixel = 10000;
    camera->image_height = height;
    camera->aspect_ratio = (float)(width) / (float)(height);
    if (camera->image_height < 1)
        camera->image_height = 1;
    camera->hfov = spec.hfov;
    camera->lookfrom = spec.view_point;
    camera->vup = vec_init(0, 10, 0);
    theta = degrees_to_radians(camera->hfov / camera->aspect_ratio);
    h = tan(theta / 2);
    camera->center = camera->lookfrom;
    focal_length = vec_length(spec.direction);
    viewport_height = 2.0 * h * focal_length;
    viewport_width = viewport_height * (double)(camera->image_width / camera->image_height);
    w = unit_vector(subtrac_vec_vec(vec_init(0,0,0),spec.direction));
    u = unit_vector(cross_vec(camera->vup, w));
    v = cross_vec(w, u);
    viewport_u = multi_vec_doub(u, viewport_width);
    viewport_v = multi_vec_doub(multi_vec_int(v, -1), viewport_height);
    camera->pixel_samples_scale = 1.0 / camera->samples_per_pixel;
    camera->max_depth = 50;
    viewport_upper_left = subtrac_vec_vec(camera->center, add_vec_vec(multi_vec_doub(w, focal_length), add_vec_vec(divi_vec_int(viewport_u, 2), divi_vec_int(viewport_v, 2))));
    camera->pixel_delta_u = divi_vec_int(viewport_u, camera->image_width);
    camera->pixel_delta_v = divi_vec_int(viewport_v, camera->image_height);
    camera->pixel00_loc = add_vec_vec(viewport_upper_left, multi_vec_doub(add_vec_vec(camera->pixel_delta_u, camera->pixel_delta_v), 0.5));
}

void    light_init(t_light *light)
{
    t_vector position = vec_init(-2, 5, 0);
    double intensity = 1.0;

    light->position = vec_init(position.x, position.y, position.z);
    light->intensity = intensity;
    light->color = vec_init(0.0 + intensity, 0.0 + intensity, 0.0 + intensity);
}

t_object  quad_init(t_vector coord, t_vector normal, t_vector color, t_material material)
{
    t_object  quad;

    quad.type = QUAD;
    quad.value.quad.q = coord;
    quad.value.quad.u = normal;
    quad.value.quad.v = vec_init(0, 4, 0);
    quad.material = material;
    quad.material.albedo = color;
    return (quad);
}
