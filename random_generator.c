/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_generator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrei <andrei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:22:38 by kaan              #+#    #+#             */
/*   Updated: 2024/08/23 00:28:28 by andrei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

unsigned int	ft_rand(void)
{
	static unsigned int	seed = 1;

	seed = A * seed + C;
	return (seed);
}

double	random_double(void)
{
	return (ft_rand() / (M + 1.0));
}

double	random_double_range(double min, double max)
{
	return (min + (max - min) * random_double());
}

t_vec	random_vec(void)
{
	return (vec(random_double(), random_double(), random_double()));
}

t_vec    random_vec_range(double min, double max)
{
    return (vec(random_double_range(min, max),
            random_double_range(min, max),
            random_double_range(min, max)));
}