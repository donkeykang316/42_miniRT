/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 18:56:01 by kaan              #+#    #+#             */
/*   Updated: 2024/08/10 16:18:04 by kaan             ###   ########.fr       */
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
	if (parser->amblight)
		free(parser->amblight);
	if (parser->camera)
		free(parser->camera);
	if (parser->light)
		free(parser->light);
	if (parser->object_nbr > 0)
	{
		while (i < parser->object_nbr)
		{
			free(parser->object[i]);
			i++;
		}
		free(parser->object);
	}
	free(parser);
}