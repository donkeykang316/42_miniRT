/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:21:11 by kaan              #+#    #+#             */
/*   Updated: 2024/08/26 15:42:55 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	swap_double(double *a, double *b)
{
	double	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

t_matrix	identity(void)
{
	t_matrix	a;

	a.col0 = vec(1, 0, 0);
	a.col1 = vec(0, 1, 0);
	a.col2 = vec(0, 0, 1);
	return (a);
}

t_matrix	add_matrix_matrix(t_matrix a, t_matrix b)
{
	t_matrix	res;

	res.col0 = add_vec_vec(a.col0, b.col0);
	res.col1 = add_vec_vec(a.col1, b.col1);
	res.col2 = add_vec_vec(a.col2, b.col2);
	return (res);
}

t_matrix	mul_matrix_matrix(t_matrix a, t_matrix b)
{
	t_matrix	res;

	res.col0.x = a.col0.x * b.col0.x + a.col1.x
		* b.col0.y + a.col2.x * b.col0.z;
	res.col1.x = a.col0.x * b.col1.x + a.col1.x
		* b.col1.y + a.col2.x * b.col1.z;
	res.col2.x = a.col0.x * b.col2.x + a.col1.x
		* b.col2.y + a.col2.x * b.col2.z;
	res.col0.y = a.col0.y * b.col0.x + a.col1.y
		* b.col0.y + a.col2.y * b.col0.z;
	res.col1.y = a.col0.y * b.col1.x + a.col1.y
		* b.col1.y + a.col2.y * b.col1.z;
	res.col2.y = a.col0.y * b.col2.x + a.col1.y
		* b.col2.y + a.col2.y * b.col2.z;
	res.col0.z = a.col0.z * b.col0.x + a.col1.z
		* b.col0.y + a.col2.z * b.col0.z;
	res.col1.z = a.col0.z * b.col1.x + a.col1.z
		* b.col1.y + a.col2.z * b.col1.z;
	res.col2.z = a.col0.z * b.col2.x + a.col1.z
		* b.col2.y + a.col2.z * b.col2.z;
	return (res);
}

t_matrix	mul_matrix_double(t_matrix m, double d)
{
	m.col0 = mul_vec_double(m.col0, d);
	m.col1 = mul_vec_double(m.col1, d);
	m.col2 = mul_vec_double(m.col2, d);
	return (m);
}
