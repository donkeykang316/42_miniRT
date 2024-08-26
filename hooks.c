/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 14:41:55 by kaan              #+#    #+#             */
/*   Updated: 2024/08/26 15:14:30 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	on_expose(t_mlx_context *ctx)
{
	render_frame(ctx);
	return (1);
}

void	quit(t_mlx_context *ctx)
{
	void	*mlx;

	mlx = ctx->mlx_context;
	mlx_destroy_image(mlx, ctx->mlx_image);
	mlx_destroy_window(mlx, ctx->window);
	mlx_loop_end(mlx);
	mlx_destroy_display(mlx);
	free(mlx);
	free_mem(ctx);
	exit (0);
}

int	on_key_up(int keycode, t_mlx_context *ctx)
{
	if (keycode == KEY_ESC)
	{
		quit(ctx);
		return (1);
	}
	else if (keycode == 'w')
		handle_key_w(ctx);
	else if (keycode == 's')
		handle_key_s(ctx);
	else if (keycode == 'a')
		handle_key_a(ctx);
	else if (keycode == 'd')
		handle_key_d(ctx);
	return (1);
}

int	on_close_button(t_mlx_context *ctx)
{
	quit(ctx);
	return (1);
}
