#include "minirt.h"

t_vector  *add_vec_vec(t_vector *vec1, t_vector *vec2)
{
    t_vector *result;

    result = malloc(sizeof(t_vector));
    result->x = vec1->x + vec2->x;
    result->y = vec1->y + vec2->y;
    result->z = vec1->z + vec2->z;
    return (result);
}

t_vector  *subtrac_vec_vec(t_vector *vec1, t_vector *vec2)
{
    t_vector *result;

    result = malloc(sizeof(t_vector));
    result->x = vec1->x - vec2->x;
    result->y = vec1->y - vec2->y;
    result->z = vec1->z - vec2->z;
    return (result);
}

t_vector  *multi_vec_vec(t_vector *vec1, t_vector *vec2)
{
    t_vector *result;

    result = malloc(sizeof(t_vector));
    result->x = vec1->x * vec2->x;
    result->y = vec1->y * vec2->y;
    result->z = vec1->z * vec2->z;
    return (result);
}

t_vector  *divi_vec_vec(t_vector *vec1, t_vector *vec2)
{
    t_vector *result;

    result = malloc(sizeof(t_vector));
    result->x = vec1->x / vec2->x;
    result->y = vec1->y / vec2->y;
    result->z = vec1->z / vec2->z;
    return (result);
}

t_vector  *increment_vec_vec(t_vector *vec_inc, t_vector *vec)
{
    t_vector *result;

    result = malloc(sizeof(t_vector));
    result->x = vec_inc->x + vec->x;
    result->y = vec_inc->y + vec->y;
    result->z = vec_inc->z + vec->z;
    free(vec_inc);
    return (result);
}
