/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 15:36:26 by kaan              #+#    #+#             */
/*   Updated: 2024/08/26 16:06:40 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_material	default_material(void)
{
	t_material	mat;

	mat.albedo = vec(0, 0, 0);
	return (mat);
}

int	parse_space(char **scene, int *total)
{
	int	parsed;

	parsed = 0;
	while (isspace((*scene)[parsed]))
		parsed++;
	*scene += parsed;
	*total += parsed;
	return (parsed);
}

int	parse_char(char	**scene, char c, int *total)
{
	int	parsed;

	parsed = 0;
	if (**scene == c)
		parsed = 1;
	*scene += parsed;
	*total += parsed;
	return (parsed);
}

int	parse_whitespace(char **scene, int *total)
{
	int	parsed;

	parsed = 0;
	while ((*scene)[parsed] == ' ')
		parsed++;
	*scene += parsed;
	*total += parsed;
	return (parsed);
}

int	parse_decimal(char **scene, int *dst, int *total)
{
	int	parsed;

	parsed = 0;
	*dst = 0;
	while (isdigit((*scene)[parsed]))
	{
		*dst = *dst * 10 + ((*scene)[parsed] - '0');
		parsed++;
	}
	*scene += parsed;
	*total += parsed;
	return (parsed);
}
