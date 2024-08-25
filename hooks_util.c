/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 18:21:40 by kaan              #+#    #+#             */
/*   Updated: 2024/08/25 18:24:44 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	reset_context(t_mlx_context *ctx)
{
	ft_memset(ctx->sum.data, 0, ctx->width * ctx->height * sizeof(t_vec));
	ctx->samples = 0;
}

void	handle_key_w(t_mlx_context *ctx)
{
	ctx->camera.center.z -= 1.0;
	reset_context(ctx);
}

void	handle_key_s(t_mlx_context *ctx)
{
	ctx->camera.center.z += 1.0;
	reset_context(ctx);
}

void	handle_key_a(t_mlx_context *ctx)
{
	ctx->camera.center.x -= 1.0;
	reset_context(ctx);
}

void	handle_key_d(t_mlx_context *ctx)
{
	ctx->camera.center.x += 1.0;
	reset_context(ctx);
}
