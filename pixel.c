#include "minirt.h"


unsigned int	flip_bytes(unsigned int x)
{
	unsigned int	a;
	unsigned int	b;
	unsigned int	c;
	unsigned int	d;

	a = x & 0xff;
	b = (x & 0xff00) >> 8;
	c = (x & 0xff0000) >> 16;
	d = (x & 0xff000000) >> 24;
	return (a << 24 | b << 16 | c << 8 | d);
}

void	fix_endian(unsigned int *data, int big_endian)
{
	int	x;
	int	computer_big_endian;

	x = 1;
	computer_big_endian = *(char *)(&x) == 0;
	if (computer_big_endian != big_endian)
		*data = flip_bytes(*data);
}

int	set_pixel(t_mlx_context *ctx, int x, int y, t_vector rgb)
{
	unsigned int	color;
	size_t			offset;
    int cl = (int)(rgb.x * 255.) << 16 | (int)(rgb.y * 255.) << 8 | (int)(rgb.z * 255.);

	if (x >= ctx->width || x < 0 || y < 0 || y >= ctx->height)
		return (0);
	offset = ctx->line_size * y + x * ctx->bits_per_px / 8;
	color = mlx_get_color_value(ctx->mlx_context, cl);
	fix_endian(&color, ctx->big_endian);
	ft_memcpy(&ctx->mlx_image_data[offset], &color, ctx->bits_per_px / 8);
	return (1);
}