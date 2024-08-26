/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apago <apago@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:21:18 by kaan              #+#    #+#             */
/*   Updated: 2024/08/26 20:04:54 by apago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_camera_dimensions(t_camera *camera, int width, int height)
{
	camera->image_width = width;
	camera->image_height = height;
	camera->aspect_ratio = (float)(width) / (float)(height);
	if (camera->image_height < 1)
		camera->image_height = 1;
}

void	init_camera_parameters(t_camera *camera, t_camera_spec spec)
{
	camera->samples_per_pixel = 10000;
	camera->hfov = spec.hfov;
	camera->lookfrom = spec.view_point;
	camera->vup = vec(0, 10, 0);
	if (spec.direction.x == 0 && spec.direction.z == 0)
		camera->vup = vec(0, 0, 10);
	camera->center = camera->lookfrom;
	camera->pixel_samples_scale = 1.0 / camera->samples_per_pixel;
	camera->max_depth = 50;
}

void	calculate_viewport(t_camera *camera, t_camera_spec spec, t_camtmp *tmp)
{
	tmp->theta = degrees_to_radians(camera->hfov / camera->aspect_ratio);
	tmp->h = tan(tmp->theta / 2);
	tmp->focal_length = length(spec.direction);
	tmp->viewport_height = 2.0 * tmp->h * tmp->focal_length;
	tmp->viewport_width = tmp->viewport_height * (double)(camera->image_width
			/ camera->image_height);
	tmp->w = normalize(sub_vec_vec(vec(0, 0, 0), spec.direction));
	tmp->u = normalize(cross_vec(camera->vup, tmp->w));
	tmp->v = cross_vec(tmp->w, tmp->u);
}

void	set_pixel_parameters(t_camera *camera, t_camtmp *tmp)
{
	tmp->viewport_u = mul_vec_double(tmp->u, tmp->viewport_width);
	tmp->viewport_v = mul_vec_double(mul_vec_int(tmp->v, -1),
			tmp->viewport_height);
	tmp->viewport_upper_left = sub_vec_vec(camera->center,
			add_vec_vec(mul_vec_double(tmp->w, tmp->focal_length),
				add_vec_vec(div_vec_int(tmp->viewport_u, 2),
					div_vec_int(tmp->viewport_v, 2))));
	camera->pixel_delta_u = div_vec_int(tmp->viewport_u, camera->image_width);
	camera->pixel_delta_v = div_vec_int(tmp->viewport_v, camera->image_height);
	camera->pixel00_loc = add_vec_vec(tmp->viewport_upper_left,
			mul_vec_double(add_vec_vec(camera->pixel_delta_u,
					camera->pixel_delta_v), 0.5));
}

void	camera_init(t_camera *camera, t_camera_spec spec, int width, int height)
{
	t_camtmp	tmp;

	init_camera_dimensions(camera, width, height);
	init_camera_parameters(camera, spec);
	calculate_viewport(camera, spec, &tmp);
	set_pixel_parameters(camera, &tmp);
}
