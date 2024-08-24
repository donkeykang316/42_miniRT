/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrei <andrei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 14:16:34 by kaan              #+#    #+#             */
/*   Updated: 2024/08/23 17:32:35 by andrei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double cos_angle_between(t_vec a, t_vec b) {
    float len = length(a) * length(b);
    if (len == 0)
        return 1;
    return dot_vec(a, b) / len;
}

double angle_between(t_vec a, t_vec b) {
    return acos(cos_angle_between(a,b));
}
