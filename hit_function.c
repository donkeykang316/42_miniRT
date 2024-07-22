#include "minirt.h"

double    hit_sphere(t_vector *center, double radius, t_ray *ray)
{
    t_sphere    *sphere;
    double      discriminant;

    sphere = malloc(sizeof(t_sphere));
    sphere->oc = subtrac_vec_vec(center, ray->origin);
    sphere->a = dot_vec(ray->direction, ray->direction);
    sphere->b = -2.0 * dot_vec(ray->direction, sphere->oc);
    sphere->c = dot_vec(sphere->oc, sphere->oc) - (radius * radius);
    discriminant = sphere->b * sphere->b - 4 * sphere->a * sphere->c;
    free(sphere);
    if (discriminant < 0)
        return (-1.0);
    else
        return ((-(sphere->b) - sqrt(discriminant)) / (2.0 * sphere->a));
}