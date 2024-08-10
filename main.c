/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:21:43 by kaan              #+#    #+#             */
/*   Updated: 2024/08/10 06:47:24 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int ac, char **av)
{
	//t_mlx_context   	ctx;
	t_parser		*parser;

	if (ac != 2)
		error_msg("Usage: ./minirt [scene.rt]");
	parser = malloc(sizeof(t_parser));
	parser->object_nbr = 0;
	if (file_valid(av[1], &(parser->object_nbr)) == 0)
	{
		parser->object_list = malloc(sizeof(t_object_list) * parser->object_nbr);
		parser->count = 0;
		parsing(parser, av[1]);
		//print_parser(parser, 2);
	}
	else
	{
		free(parser);
		exit(1);
	}
    /*if (!init_mlx_context(&ctx, 400, 300)) {
        return 1;
    }
	setup_hooks(&ctx);
	mlx_loop(ctx.mlx_context);*/
	parser_free(parser);
	return (0);
}
