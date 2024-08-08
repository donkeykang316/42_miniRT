/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:21:43 by kaan              #+#    #+#             */
/*   Updated: 2024/08/08 19:31:48 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int ac, char **av)
{
	//t_mlx_context   	ctx;

	if (ac != 2)
		error_msg("Usage: ./minirt [scene.rt]");
	else if (open_file(av[1]))
		printf("parser success\n");
	else
		error_msg("Failed to open file");
    /*if (!init_mlx_context(&ctx, 400, 300)) {
        return 1;
    }
	setup_hooks(&ctx);
	mlx_loop(ctx.mlx_context);*/
	return (0);
}
