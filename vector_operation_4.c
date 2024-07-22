#include "minirt.h"

double  dot_vec(t_vector *vec1, t_vector *vec2)
{
    double  result;

    result = (vec1->x * vec2->x) + (vec1->y * vec2->y) + (vec1->z * vec2->z);
    return (result);
}