/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:21:33 by kaan              #+#    #+#             */
/*   Updated: 2024/08/06 12:21:37 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool    scatter_light(t_ray *r_in, t_hit_rec *rec, t_vector attenuation, t_ray *scattered, t_material *material)
{
    t_vector    scatter_direction;

    (void)attenuation;
    (void)scattered;
    (void)r_in;
    scatter_direction = add_vec_vec(rec->normal, random_unit_vector());
    scattered->origin = vec_init(rec->p.x, rec->p.y, rec->p.z);
    scattered->direction = vec_init(scatter_direction.x, scatter_direction.y, scatter_direction.z);
    attenuation = vec_init(material->albedo.x, material->albedo.y, material->albedo.z);
    return (true);
}