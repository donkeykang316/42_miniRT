#include "minirt.h"

double  dot_vec(t_vector *vec1, t_vector *vec2)
{
    double  result;

    result = (vec1->x * vec2->x) + (vec1->y * vec2->y) + (vec1->z * vec2->z);
    return (result);
}

t_vector    *at_vec(t_ray *ray, double t)
{
    t_vector    *result;

    result = malloc(sizeof(t_vector));
    result = add_vec_vec(ray->origin, multi_vec_doub(ray->direction, t));
    return (result);
}

double  length_squared(t_vector *vec)
{
    double  result;

    result = dot_vec(vec, vec);
    return (result);
}

double  vec_length(t_vector *vec)
{
    double  result;

    result = sqrt(length_squared(vec));
    return (result);
}

t_vector    *unit_vector(t_vector *vec)
{
    t_vector    *result;

    result = malloc(sizeof(t_vector));
    result = divi_vec_doub(vec, vec_length(vec));
    return (result);
}
