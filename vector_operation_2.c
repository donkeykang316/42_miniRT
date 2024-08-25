/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operation_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:24:06 by kaan              #+#    #+#             */
/*   Updated: 2024/08/25 17:45:13 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec	add_vec_int(t_vec vec, int inte)
{
	t_vec	result;

	result.x = vec.x + inte;
	result.y = vec.y + inte;
	result.z = vec.z + inte;
	return (result);
}

t_vec	sub_vec_int(t_vec vec, int inte)
{
	t_vec	result;

	result.x = vec.x - inte;
	result.y = vec.y - inte;
	result.z = vec.z - inte;
	return (result);
}

t_vec	mul_vec_int(t_vec vec, int inte)
{
	t_vec	result;

	result.x = vec.x * inte;
	result.y = vec.y * inte;
	result.z = vec.z * inte;
	return (result);
}

t_vec	div_vec_int(t_vec vec, int inte)
{
	t_vec	result;

	result.x = vec.x / inte;
	result.y = vec.y / inte;
	result.z = vec.z / inte;
	return (result);
}
