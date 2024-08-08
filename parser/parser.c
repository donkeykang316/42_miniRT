/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 18:46:17 by kaan              #+#    #+#             */
/*   Updated: 2024/08/08 19:28:32 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	parser(char *line)
{
	if (ft_strncmp(line, "R", 1) == 0)
		printf("line:%s\n", line);
	if (ft_strncmp(line, "A", 1) == 0)
		printf("line:%s\n", line);
	if (ft_strncmp(line, "C", 1) == 0)
		printf("line:%s\n", line);
	if (ft_strncmp(line, "L", 1) == 0)
		printf("line:%s\n", line);
	if (ft_strncmp(line, "sp", 2) == 0)
		printf("line:%s\n", line);
	if (ft_strncmp(line, "pl", 2) == 0)
		printf("line:%s\n", line);
	if (ft_strncmp(line, "cy", 2) == 0)
		printf("line:%s\n", line);
	if (ft_strncmp(line, "co", 2) == 0)
		printf("line:%s\n", line);
	if (ft_strncmp(line, "tr", 2) == 0)
		printf("line:%s\n", line);
	if (ft_strncmp(line, "to", 2) == 0)
		printf("line:%s\n", line);
	return (0);
}
