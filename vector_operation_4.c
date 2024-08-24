/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operation_4.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrei <andrei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:24:25 by kaan              #+#    #+#             */
/*   Updated: 2024/08/23 00:28:28 by andrei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double  dot_vec(t_vec vec1, t_vec vec2)
{
    double  result;

    result = (vec1.x * vec2.x) + (vec1.y * vec2.y) + (vec1.z * vec2.z);
    return (result);
}

t_vec    cross_vec(t_vec vec1, t_vec vec2)
{
    t_vec    result;

    result.x = (vec1.y * vec2.z) - (vec1.z * vec2.y);
    result.y = (vec1.z * vec2.x) - (vec1.x * vec2.z);
    result.z = (vec1.x * vec2.y) - (vec1.y * vec2.x);
    return (result);
}

t_vec    at_ray(t_ray ray, double t)
{
    t_vec    result;

    result = add_vec_vec(ray.origin, mul_vec_double(ray.direction, t));
    return (result);
}

double  length_squared(t_vec vec)
{
    double  result;

    result = dot_vec(vec, vec);
    return (result);
}

double  length(t_vec vec)
{
    double  result;

    result = sqrt(length_squared(vec));
    return (result);
}
