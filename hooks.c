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
	exit(0);
}

int	on_key_up(int keycode, t_mlx_context *ctx)
{
	if (keycode == KEY_ESC)
	{
		quit(ctx);
		return (1);
	}
	return (1);
}

int	on_close_button(t_mlx_context *ctx)
{
	quit(ctx);
	return (1);
}