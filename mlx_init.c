#include "minirt.h"

int	init_mlx_image(t_mlx_context *ctx)
{
	ctx->mlx_image = mlx_new_image(ctx->mlx_context, ctx->width, ctx->height);
	ctx->mlx_image_data = mlx_get_data_addr(ctx->mlx_image, &ctx->bits_per_px,
			&ctx->line_size, &ctx->big_endian);
	return (1);
}

void init_image(t_image* img, int width, int height) {
    img->width = width;
    img->height = height;
    img->data = ft_calloc(width * height, sizeof(t_vector));
}

int	init_mlx_context(t_mlx_context *ctx, int width, int height)
{
    ctx->width = width;
    ctx->height = height;
    void* mlx = mlx_init();
	if (!mlx)
		return (0);
	ctx->mlx_context = mlx;
	ctx->window = mlx_new_window(mlx, width, height, "MiniRT");
    init_mlx_image(ctx);
    ctx->samples = 0;
    init_image(&ctx->sum, ctx->width, ctx->height);
    camera_init(&ctx->camera, ctx->world->camera, ctx->width, ctx->height);
	mlx_put_image_to_window(ctx->mlx_context, ctx->window, ctx->mlx_image,
		0, 0);
    return 1;
}

void display_image(t_mlx_context* ctx) {
    int y = 0;
    while(y < ctx->height) {
        int x = 0;
        while(x < ctx->width) {
            t_vector color = gamma_correct(divi_vec_doub(ctx->sum.data[y * ctx->width + x], ctx->samples));
            set_pixel(ctx, x, y, color);
            x++;
        }
        y++;
    }
	mlx_put_image_to_window(ctx->mlx_context, ctx->window, ctx->mlx_image,
		0, 0);
    mlx_flush(ctx->mlx_context);
}

void debug_info(t_mlx_context* ctx) {
    t_vector coords = ctx->camera.center;
    char* s = ft_calloc(1024, sizeof(char));
    sprintf(s, "camera coords: x=%f y=%f z=%f", coords.x, coords.y, coords.z);
    mlx_string_put(ctx->mlx_context, ctx->window, 1, 10, 0xff0000, s);
    ft_memset(s, 0, 1024);
    t_vector direction = ctx->world->camera.direction;
    sprintf(s, "camera direction: x=%f y=%f z=%f", direction.x, direction.y, direction.z);
    mlx_string_put(ctx->mlx_context, ctx->window, 1, 20, 0xff0000, s);
    free(s);
}

int render_frame(t_mlx_context* ctx) {
    t_camera camera = ctx->camera;

    if (ctx->samples >= camera.samples_per_pixel) {
        return 0;
    }

    t_image image = ctx->sum;

    ctx->samples++;
    render(ctx->world, camera, image);

    display_image(ctx);
    debug_info(ctx);

    return ctx->samples < camera.samples_per_pixel;
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
