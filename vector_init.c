#include "minirt.h"

t_vector	*vec_init(double x, double y, double z)
{
    t_vector *output;

    output = malloc(sizeof(t_vector));
    output->x = x;
    output->y = y;
    output->z = z;
    return (output);
}

t_vector	*vec_free_init(t_vector *vec, double x, double y, double z)
{
    free(vec);
    vec = malloc(sizeof(t_vector));
    vec->x = x;
    vec->y = y;
    vec->z = z;
    return (vec);
}
