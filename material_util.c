#include "minirt.h"

t_vector    *reflect(t_vector *vec1, t_vector *vec2)
{
    return (subtrac_vec_vec(vec1, multi_vec_doub(vec2, 2 * dot_vec(vec1, vec2))));
}

double  fmin(double x, double y)
{
    if (x < y)
        return (x);
    return (y);
}

t_vector    *refract(t_vector *uv, t_vector *n, double etai_over_etat)
{
    double      cos_theta;
    t_vector    *r_out_perpendicular;
    t_vector    *r_out_parallel;

    cos_theta = fmin(dot_vec(multi_vec_doub(uv, -1), n), 1.0);
    r_out_perpendicular = multi_vec_doub(add_vec_vec(uv, multi_vec_doub(n, cos_theta)), etai_over_etat);
    r_out_parallel = multi_vec_doub(n, -sqrt(fabs(1.0 - length_squared(r_out_perpendicular))));
    return (add_vec_vec(r_out_perpendicular, r_out_parallel));
}
