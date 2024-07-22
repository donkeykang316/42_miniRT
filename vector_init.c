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
