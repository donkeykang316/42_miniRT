/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operation_4.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:24:25 by kaan              #+#    #+#             */
/*   Updated: 2024/08/06 12:24:26 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double  dot_vec(t_vector vec1, t_vector vec2)
{
    double  result;

    result = (vec1.x * vec2.x) + (vec1.y * vec2.y) + (vec1.z * vec2.z);
    return (result);
}

t_vector    cross_vec(t_vector vec1, t_vector vec2)
{
    t_vector    result;

    result.x = (vec1.y * vec2.z) - (vec1.z * vec2.y);
    result.y = (vec1.z * vec2.x) - (vec1.x * vec2.z);
    result.z = (vec1.x * vec2.y) - (vec1.y * vec2.x);
    return (result);
}

t_vector    at_vec(t_ray ray, double t)
{
    t_vector    result;

    result = add_vec_vec(ray.origin, multi_vec_doub(ray.direction, t));
    return (result);
}

double  length_squared(t_vector vec)
{
    double  result;

    result = dot_vec(vec, vec);
    return (result);
}

double  vec_length(t_vector vec)
{
    double  result;

    result = sqrt(length_squared(vec));
    return (result);
}
