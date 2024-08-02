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

bool    surrounds(t_interval ray_t, double x)
{
    if (ray_t.min < x && x < ray_t.max)
        return (true);
    return (false);
}

double  clamp(t_interval ray_t, double x)
{
    if (x < ray_t.min)
        return (ray_t.min);
    if (x > ray_t.max)
        return (ray_t.max);
    return (x);
}

/*t_interval  expand(double delta)
{
    t_interval  interval;
    double      padding;

    padding = delta / 2;
    interval.min = interval.min - padding;
    interval.max = interval.max + padding;
    return (interval);
}*/
