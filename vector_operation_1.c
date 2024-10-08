/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operation_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:23:39 by kaan              #+#    #+#             */
/*   Updated: 2024/08/26 16:07:32 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec	add_vec_vec(t_vec vec1, t_vec vec2)
{
	t_vec	result;

	result.x = vec1.x + vec2.x;
	result.y = vec1.y + vec2.y;
	result.z = vec1.z + vec2.z;
	return (result);
}

t_vec	sub_vec_vec(t_vec vec1, t_vec vec2)
{
	t_vec	result;

	result.x = vec1.x - vec2.x;
	result.y = vec1.y - vec2.y;
	result.z = vec1.z - vec2.z;
	return (result);
}

t_vec	mul_vec_vec(t_vec vec1, t_vec vec2)
{
	t_vec	result;

	result = vec(vec1.x * vec2.x, vec1.y * vec2.y, vec1.z * vec2.z);
	return (result);
}

t_vec	div_vec_vec(t_vec vec1, t_vec vec2)
{
	t_vec	result;

	result.x = vec1.x / vec2.x;
	result.y = vec1.y / vec2.y;
	result.z = vec1.z / vec2.z;
	return (result);
}

t_vec	vec_neg(t_vec v)
{
	return (vec(-v.x, -v.y, -v.z));
}
