#include "minirt.h"

double  size(t_interval *ray_t)
{
    double  diff;

    diff = ray_t->max - ray_t->min;
    return (diff);
}

bool    contains(t_interval *ray_t, double x)
{
    if (ray_t->min <= x && x <= ray_t->max)
        return (true);
    return (false);
}

bool    surrounds(t_interval *ray_t, double x)
{
    if (ray_t->min < x && x < ray_t->max)
        return (true);
    return (false);
}