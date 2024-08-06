/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:21:43 by kaan              #+#    #+#             */
/*   Updated: 2024/08/06 12:21:47 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
    init_image(&ctx->image, ctx->width, ctx->height);
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
    int fd = open("img.ppm", O_WRONLY | O_TRUNC | O_CREAT, 0644);

    dprintf(fd, "P3\n%d %d\n255\n", (int)ctx->width, (int)ctx->height);
    int y = 0;
    while(y < ctx->height) {
        int x = 0;
        while(x < ctx->width) {
            set_pixel(ctx, x, y, trim_color(ctx->image.data[y * ctx->width + x]));
            write_color(fd, ctx->image.data[y * ctx->width + x]);
            x++;
        }
        y++;
    }
    close(fd);
	mlx_put_image_to_window(ctx->mlx_context, ctx->window, ctx->mlx_image,
		0, 0);
}

int render_frame(t_mlx_context* ctx) {
    t_camera    camera;

    camera_init(&camera, ctx->width, ctx->height);
    printf("rendering frame...\n");
    render(camera, ctx->image);
    printf("rendered\n");
    display_image(ctx);
    return 1;
}

void	setup_hooks(t_mlx_context *ctx)
{
	mlx_do_key_autorepeaton(ctx->mlx_context);
	mlx_hook(ctx->window, 2, 1, &on_key_up, ctx);
	mlx_expose_hook(ctx->window, &on_expose, ctx);
	mlx_hook(ctx->window, 17, 0, &on_close_button, ctx);
	mlx_clear_window(ctx->mlx_context, ctx->window);
}

int	main()
{
	t_mlx_context   	ctx;

    if (!init_mlx_context(&ctx, 400, 300)) {
        return 1;
    }
	setup_hooks(&ctx);
	mlx_loop(ctx.mlx_context);
	return (0);
}