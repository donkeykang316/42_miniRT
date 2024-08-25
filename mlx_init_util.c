/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 15:35:15 by kaan              #+#    #+#             */
/*   Updated: 2024/08/25 15:36:12 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	render_frame(t_mlx_context *ctx)
{
	t_camera	camera;
	t_image		image;

	camera = ctx->camera;
	if (ctx->samples >= camera.samples_per_pixel)
		return (0);
	image = ctx->sum;
	ctx->samples++;
	render(ctx->world, camera, image);
	display_image(ctx);
	debug_info(ctx);
	return (ctx->samples < camera.samples_per_pixel);
}

void	setup_hooks(t_mlx_context *ctx)
{
	mlx_do_key_autorepeaton(ctx->mlx_context);
	mlx_hook(ctx->window, 2, 1, &on_key_up, ctx);
	mlx_expose_hook(ctx->window, &on_expose, ctx);
	mlx_loop_hook(ctx->mlx_context, render_frame, ctx);
	mlx_hook(ctx->window, 17, 0, &on_close_button, ctx);
	mlx_clear_window(ctx->mlx_context, ctx->window);
}
