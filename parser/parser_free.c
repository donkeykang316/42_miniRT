/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 18:56:01 by kaan              #+#    #+#             */
/*   Updated: 2024/08/10 06:50:40 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	free_double(char **double_str)
{
	int	i;

	i = 0;
	if (double_str == NULL)
		return ;
	while (double_str[i] != NULL)
	{
		free(double_str[i]);
		i++;
	}
	free(double_str);
}

void	parser_free(t_parser *parser)
{
	int	i;

	i = 0;
	free(parser->amblight);
	free(parser->camera);
	free(parser->light);
	while (i < parser->object_nbr)
	{
		if (parser->object_list[i]->type == SPHERE)
		{
			free(parser->object_list[i]->sphere->material);
			free(parser->object_list[i]->sphere);
		}
		else if (parser->object_list[i]->type == QUAD)
		{
			free(parser->object_list[i]->quad->material);
			free(parser->object_list[i]->quad);
		}
		else if (parser->object_list[i]->type == TRIANGLE)
		{
			free(parser->object_list[i]->tri->material);
			free(parser->object_list[i]->tri);
		}
		else if (parser->object_list[i]->type == CYLINDER)
		{
			free(parser->object_list[i]->cyl->material);
			free(parser->object_list[i]->cyl);
		}
		free(parser->object_list[i]);
		i++;
	}
	free(parser->object_list);
}