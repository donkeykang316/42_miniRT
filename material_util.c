/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:21:58 by kaan              #+#    #+#             */
/*   Updated: 2024/08/06 12:22:00 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector    reflect(t_vector vec1, t_vector vec2)
{
    return (subtrac_vec_vec(vec1, multi_vec_doub(vec2, 2 * dot_vec(vec1, vec2))));
}

t_vector    refract(t_vector uv, t_vector n, double etai_over_etat)
{
    double cos_theta;
    t_vector r_out_perp;
    t_vector r_out_parallel;
    
    cos_theta = fmin(dot_vec(n, multi_vec_doub(uv, -1)), 1.0);
    r_out_perp = multi_vec_doub(add_vec_vec(uv, multi_vec_doub(n, cos_theta)), etai_over_etat);
    r_out_parallel = multi_vec_doub(n, -sqrt(fabs(1.0 - length_squared(r_out_perp))));
    return (add_vec_vec(r_out_perp, r_out_parallel));
}

double fuzz(double fuzz)
{
    if (fuzz >= 1)
        return (1.0);
    return (fuzz);
}
