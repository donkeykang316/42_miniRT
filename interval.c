/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interval.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:21:26 by kaan              #+#    #+#             */
/*   Updated: 2024/08/25 14:46:32 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	size(t_interval *ray_t)
{
	double	diff;

	diff = ray_t->max - ray_t->min;
	return (diff);
}

bool	contains(t_interval *ray_t, double x)
{
	if (ray_t->min <= x && x <= ray_t->max)
		return (true);
	return (false);
}

bool	surrounds(t_interval ray_t, double x)
{
	if (ray_t.min < x && x < ray_t.max)
		return (true);
	return (false);
}

double	clamp(t_interval ray_t, double x)
{
	if (x < ray_t.min)
		return (ray_t.min);
	if (x > ray_t.max)
		return (ray_t.max);
	return (x);
}
