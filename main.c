/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apago <apago@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:21:43 by kaan              #+#    #+#             */
/*   Updated: 2024/08/26 19:08:06 by apago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int ac, char **av)
{
	t_mlx_context	ctx;
	char			*text;
	t_world			world;

	if (ac != 2)
		error_msg("Usage: ./minirt [scene.rt]");
	text = read_file(av[1]);
	if (!text)
		exit(error_msg("Error: failed to open file"));
	if (!parse_world(text, &world))
	{
		if (world.point_lights)
			free(world.point_lights);
		if (world.objects)
			free(world.objects);
		free(text);
		exit(error_msg("Parsing error"));
	}
	free(text);
	ctx.world = &world;
	if (!init_mlx_context(&ctx, 800, 600))
		return (1);
	setup_hooks(&ctx);
	mlx_loop(ctx.mlx_context);
	return (0);
}
