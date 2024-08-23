/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrei <andrei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:23:24 by kaan              #+#    #+#             */
/*   Updated: 2024/08/23 19:13:27 by andrei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double  degrees_to_radians(double degrees)
{
    double  radian;

    radian = degrees * M_PI /180.0;
    return (radian);
}
