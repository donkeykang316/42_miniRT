/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_util_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 16:14:50 by kaan              #+#    #+#             */
/*   Updated: 2024/08/25 18:49:33 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_double(char **scene, double *flt, int *total)
{
	t_parsedoubtmp	tmp;

	tmp.parsed = 0;
	tmp.whole = 0;
	tmp.fraction = 0;
	tmp.sc = *scene;
	tmp.minus = parse_char(&tmp.sc, '-', &tmp.parsed);
	tmp.decimal_places = 0;
	parse_decimal(&tmp.sc, &tmp.whole, &tmp.parsed);
	if (parse_char(&tmp.sc, '.', &tmp.parsed))
		tmp.decimal_places = parse_decimal(&tmp.sc, &tmp.fraction, &tmp.parsed);
	if (!(tmp.parsed - tmp.minus)
		|| ((tmp.parsed - tmp.minus) == 1 && (*scene)[tmp.minus] == '.'))
		return (0);
	*flt = make_double(tmp.whole, tmp.fraction, tmp.decimal_places);
	if (tmp.minus)
		*flt = -*flt;
	*scene += tmp.parsed;
	*total += tmp.parsed;
	return (tmp.parsed);
}

int	parse_byte(char **scene, int *byte, int *total)
{
	int		parsed;
	char	*sc;

	parsed = 0;
	sc = *scene;
	if (!parse_decimal(&sc, byte, &parsed))
		return (0);
	if ((parsed > 3) || (*byte > 255))
		return (0);
	*total += parsed;
	*scene += parsed;
	return (parsed);
}

int	parse_color(char **scene, t_vec *clr, int *total)
{
	int		parsed;
	char	*sc;
	int		rgb[3];

	parsed = 0;
	sc = *scene;
	if (!parse_byte(&sc, &rgb[0], &parsed))
		return (0);
	if (!parse_char(&sc, ',', &parsed))
		return (0);
	if (!parse_byte(&sc, &rgb[1], &parsed))
		return (0);
	if (!parse_char(&sc, ',', &parsed))
		return (0);
	if (!parse_byte(&sc, &rgb[2], &parsed))
		return (0);
	clr->x = rgb[0] / 255.;
	clr->y = rgb[1] / 255.;
	clr->z = rgb[2] / 255.;
	*scene += parsed;
	*total += parsed;
	return (parsed);
}

int	parse_vector(char **scene, t_vec *vec, int *total)
{
	int		parsed;
	char	*sc;

	parsed = 0;
	sc = *scene;
	if (!parse_double(&sc, &vec->x, &parsed))
		return (0);
	if (!parse_char(&sc, ',', &parsed))
		return (0);
	if (!parse_double(&sc, &vec->y, &parsed))
		return (0);
	if (!parse_char(&sc, ',', &parsed))
		return (0);
	if (!parse_double(&sc, &vec->z, &parsed))
		return (0);
	*total += parsed;
	*scene += parsed;
	return (parsed);
}
