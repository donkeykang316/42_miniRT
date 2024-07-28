#include "minirt.h"

t_vector    *unit_vector(t_vector *vec)
{
    t_vector    *result;

    result = malloc(sizeof(t_vector));
    result = divi_vec_doub(vec, vec_length(vec));
    return (result);
}

t_vector *normalize_vec(t_vector *vec)
{
    double length;
    t_vector *result;
    
    length = sqrt(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z);
    result = vec_init(vec->x / length, vec->y / length, vec->z / length);
    return (result);
}

double  fabs(double x)
{
    if (x < 0)
        return (-x);
    return (x);
}

bool    near_zero(t_vector *vec)
{
    double  s;

    s = 1e-8;
    return (fabs(vec->x) < s && fabs(vec->y) < s && fabs(vec->z) < s);
}
