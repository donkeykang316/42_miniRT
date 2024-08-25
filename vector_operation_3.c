/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operation_3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:24:13 by kaan              #+#    #+#             */
/*   Updated: 2024/08/25 17:46:18 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec	add_vec_double(t_vec vec, double doub)
{
	t_vec	result;

	result.x = vec.x + doub;
	result.y = vec.y + doub;
	result.z = vec.z + doub;
	return (result);
}

t_vec	sub_vec_double(t_vec vec, double doub)
{
	t_vec	result;

	result.x = vec.x - doub;
	result.y = vec.y - doub;
	result.z = vec.z - doub;
	return (result);
}

t_vec	mul_vec_double(t_vec vec, double doub)
{
	t_vec	result;

	result.x = vec.x * doub;
	result.y = vec.y * doub;
	result.z = vec.z * doub;
	return (result);
}

t_vec	div_vec_double(t_vec vec, double doub)
{
	t_vec	result;

	result.x = vec.x / doub;
	result.y = vec.y / doub;
	result.z = vec.z / doub;
	return (result);
}
