#include "minirt.h"

double	*vec_3d_init(double x, double y, double z)
{
    double  *output;

    output = malloc(3 * sizeof(double));
    output[0] = x;
    output[1] = y;
    output[2] = z;
    return (output);
}
