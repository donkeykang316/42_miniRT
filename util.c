/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:23:24 by kaan              #+#    #+#             */
/*   Updated: 2024/08/26 15:13:14 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	degrees_to_radians(double degrees)
{
	double	radian;

	radian = degrees * M_PI / 180.0;
	return (radian);
}

void	free_mem(t_mlx_context *ctx)
{
	if (ctx->world->point_lights)
		free(ctx->world->point_lights);
	if (ctx->world->objects)
		free(ctx->world->objects);
	if (ctx->sum.data)
		free(ctx->sum.data);
}
