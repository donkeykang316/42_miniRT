/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operation_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:24:06 by kaan              #+#    #+#             */
/*   Updated: 2024/08/06 12:24:08 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector  add_vec_int(t_vector vec, int inte)
{
    t_vector result;

    result.x = vec.x + inte;
    result.y = vec.y + inte;
    result.z = vec.z + inte;
    return (result);
}

t_vector  subtrac_vec_int(t_vector vec, int inte)
{
    t_vector result;

    result.x = vec.x - inte;
    result.y = vec.y - inte;
    result.z = vec.z - inte;
    return (result);
}

t_vector  multi_vec_int(t_vector vec, int inte)
{
    t_vector result;

    result.x = vec.x * inte;
    result.y = vec.y * inte;
    result.z = vec.z * inte;
    return (result);
}

t_vector  divi_vec_int(t_vector vec, int inte)
{
    t_vector result;

    result.x = vec.x / inte;
    result.y = vec.y / inte;
    result.z = vec.z / inte;
    return (result);
}
