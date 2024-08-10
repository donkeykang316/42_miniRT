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
    init_image(&ctx->image, ctx->width, ctx->height);
    init_image(&ctx->sum, ctx->width, ctx->height);
	mlx_put_image_to_window(ctx->mlx_context, ctx->window, ctx->mlx_image,
		0, 0);
    return 1;
}

double clamp_double(double x, double low, double high) {
    if (x < low)
        return low;
    if (x > high)
        return high;
    return x;
}

t_vector trim_color(t_vector color) {
    color.x = clamp_double(color.x, 0, 1);
    color.y = clamp_double(color.y, 0, 1);
    color.z = clamp_double(color.z, 0, 1);
    return color;
}

void display_image(t_mlx_context* ctx) {
    int y = 0;
    while(y < ctx->height) {
        int x = 0;
        while(x < ctx->width) {
            set_pixel(ctx, x, y, trim_color(ctx->image.data[y * ctx->width + x]));
            x++;
        }
        y++;
    }
	mlx_put_image_to_window(ctx->mlx_context, ctx->window, ctx->mlx_image,
		0, 0);
    mlx_flush(ctx->mlx_context);
}

int render_frame(t_mlx_context* ctx) {
    t_camera    camera;
    camera_init(&camera, ctx->width, ctx->height);

    if (ctx->samples >= camera.samples_per_pixel) {
        return 0;
    }

    t_image image = ctx->image;

    ctx->samples++;
    render(camera, image);

    for(int i = 0; i < image.width*image.height; i++) {
        ctx->sum.data[i] = add_vec_vec(ctx->sum.data[i], image.data[i]);
        ctx->image.data[i] = divi_vec_int(ctx->sum.data[i], ctx->samples);
    }
    display_image(ctx);

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
