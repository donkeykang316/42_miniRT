#include "minirt.h"

t_vector    reflect(t_vector vec1, t_vector vec2)
{
    return (subtrac_vec_vec(vec1, multi_vec_doub(vec2, 2 * dot_vec(vec1, vec2))));
}

double fuzz(double fuzz)
{
    if (fuzz >= 1)
        return (1.0);
    return (fuzz);
}
