#include "minirt.h"

double    hit_sphere(t_vector *center, double radius, t_ray *ray)
{
    t_sphere    *sphere;
    double      discriminant;
    double      sphere_value;

    sphere = malloc(sizeof(t_sphere));
    sphere->oc = subtrac_vec_vec(center, ray->origin);
    sphere->a = length_squared(ray->direction);
    sphere->h = dot_vec(ray->direction, sphere->oc);
    sphere->c = length_squared(sphere->oc) - (radius * radius);
    discriminant = (sphere->h * sphere->h) - (sphere->a * sphere->c);
    sphere_value = (sphere->h - sqrt(discriminant)) / sphere->a;
    free(sphere);
    if (discriminant < 0)
        return (-1.0);
    return (sphere_value);
}