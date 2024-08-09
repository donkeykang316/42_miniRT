/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:21:43 by kaan              #+#    #+#             */
/*   Updated: 2024/08/09 22:55:02 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int ac, char **av)
{
	//t_mlx_context   	ctx;

	if (ac != 2)
		error_msg("Usage: ./minirt [scene.rt]");
	printf("file valid: %d\n", file_valid(av[1]));
	if (file_valid(av[1]) == 0)
		printf("parser success\n");
	else
		exit(1);
    /*if (!init_mlx_context(&ctx, 400, 300)) {
        return 1;
    }
	setup_hooks(&ctx);
	mlx_loop(ctx.mlx_context);*/
	return (0);
}
