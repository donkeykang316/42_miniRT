/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrei <andrei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:21:58 by kaan              #+#    #+#             */
/*   Updated: 2024/08/23 00:28:28 by andrei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec    reflect(t_vec vec1, t_vec vec2)
{
    return sub_vec_vec(mul_vec_double(projection(vec1, vec2), 2), vec1);
}

t_vec    refract(t_vec uv, t_vec n, double etai_over_etat)
{
    double cos_theta;
    t_vec r_out_perp;
    t_vec r_out_parallel;
    
    cos_theta = fmin(dot_vec(n, mul_vec_double(uv, -1)), 1.0);
    r_out_perp = mul_vec_double(add_vec_vec(uv, mul_vec_double(n, cos_theta)), etai_over_etat);
    r_out_parallel = mul_vec_double(n, -sqrt(fabs(1.0 - length_squared(r_out_perp))));
    return (add_vec_vec(r_out_perp, r_out_parallel));
}

double  reflectance(double cosine, double ref_idx)
{
    double r0;
    
    r0 = (1 - ref_idx) / (1 + ref_idx);
    r0 = r0 * r0;
    return (r0 + (1 - r0) * pow((1 - cosine), 5));
}

double fuzz(double fuzz)
{
    if (fuzz >= 1)
        return (1.0);
    return (fuzz);
}
