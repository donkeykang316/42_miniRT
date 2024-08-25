/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:23:32 by kaan              #+#    #+#             */
/*   Updated: 2024/08/25 17:42:05 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec	vec(double x, double y, double z)
{
	t_vec	output;

	output.x = x;
	output.y = y;
	output.z = z;
	return (output);
}
