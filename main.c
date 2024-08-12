/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrei <andrei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:21:43 by kaan              #+#    #+#             */
/*   Updated: 2024/08/12 20:10:35 by andrei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char* read_file(char* name) {
	int fd = open(name, O_RDONLY, 0666);
	if (fd < 0)
		return 0;
	
	int len = 0;
	int cap = 1024;
	char* res = ft_calloc(cap, sizeof(char));

	while(1) {
		int rd = read(fd, &res[len], cap - len);
		if (rd < 0) {
			free(res);
			close(fd);
			return 0;
		}
		if (rd == 0) {
			close(fd);
			return res;
		}

		len += rd;
		if (len == cap) {
			char* newres = ft_calloc(cap*2, sizeof(char));
			ft_memcpy(newres, res, cap);
			free(res);
			cap *= 2;
		}
	}
}

int	main(int ac, char **av)
{
	t_mlx_context   	ctx;

	if (ac != 2)
		error_msg("Usage: ./minirt [scene.rt]");
	
	char* text = read_file(av[1]);
	if (!text)
		exit(error_msg("Error: failed to open file"));
	
	t_world world;
	if (!parse_world(text, &world))
		exit(error_msg("Parsing error"));
	free(text);
	print_world(&world);

	if (!init_mlx_context(&ctx, 400, 300)) {
		return 1;
	}
	// ctx.camera = world.camera;
	ctx.world = &world;
	setup_hooks(&ctx);
	mlx_loop(ctx.mlx_context);
	
	return (0);
}

