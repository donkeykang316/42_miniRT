/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:21:43 by kaan              #+#    #+#             */
/*   Updated: 2024/08/10 14:44:09 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	parser_init(t_parser *parser)
{
	int	i;

	i = 0;
	parser->amblight = NULL;
	parser->camera = NULL;
	parser->light = NULL;
	parser->count = 0;
	if (parser->object_nbr == 0)
	{
		parser_free(parser);
		exit(error_msg("Error: No object found"));
	}
	parser->object_list = malloc(sizeof(t_object_list) * parser->object_nbr);
	while (i < parser->object_nbr)
	{
		parser->object_list[i] = malloc(sizeof(t_object_list));
		if (parser->object_list[i] == NULL)
			exit(error_msg("Error: Malloc failed"));
		i++;
	}
}

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
		parser_init(parser);
		parsing(parser, av[1]);
		if (parser->amblight == NULL || parser->camera == NULL || parser->light == NULL)
		{
			parser_free(parser);
			exit (error_msg("Error: Missing element(s)"));
		}
		/*if (!init_mlx_context(&ctx, 400, 300)) {
        	return 1;
    	}
		setup_hooks(&ctx);
		mlx_loop(ctx.mlx_context);*/
		parser_free(parser);
	}
	else
	{
		free(parser);
		exit(1);
	}
	return (0);
}
