#include "minirt.h"

double  *double_3(double x, double y, double z)
{
    double  *ptr;

    ptr = malloc(sizeof(double) * 3);
    ptr[0] = x;
    ptr[1] = y;
    ptr[2] = z;
    return (ptr);
}

t_interval  axis_interval(t_aabb aabb, int n)
{
    if (n == 1)
        return (aabb.y);
    else if (n == 2)
        return (aabb.z);
    else
        return (aabb.x);
}

bool    hit_aabb(t_aabb aabb, t_ray ray, t_interval ray_t)
{
    double      *ray_origin;
    double      *ray_dir;
    int         axis;
    t_interval  ax;
    double      adinv;
    double      t0;
    double      t1;

    ray_origin = double_3(ray.origin.x, ray.origin.y, ray.origin.z);
    ray_dir = double_3(ray.direction.x, ray.direction.y, ray.direction.z);
    axis = 0;
    while (axis < 3)
    {
        ax = axis_interval(aabb, axis);
        adinv = 1.0 / ray_dir[axis];
        t0 = (ax.min - ray_origin[axis]) * adinv;
        t1 = (ax.max - ray_origin[axis]) * adinv;
        if (t0 < t1)
        {
            if (t0 > ray_t.min)
                ray_t.min = t0;
            if (t1 < ray_t.max)
                ray_t.max = t1;
        }
        else
        {
            if (t1 > ray_t.min)
                ray_t.min = t1;
            if (t0 < ray_t.max)
                ray_t.max = t0;
        }
        if (ray_t.max <= ray_t.min)
            return (false);
        axis++;
    }
    return (true);
}
