#include "minirt.h"

t_vector    *random_in_unit_sphere(void)
{
    t_vector    *p;

    while (1)
    {
        p = random_vec_range(-1, 1);
        if (length_squared(p) < 1)
            return (p);
        free(p);
    }
    return (NULL);
}

t_vector    *random_unit_vector(void)
{
    return (unit_vector(random_in_unit_sphere()));
}

t_vector    *random_on_hemisphere(t_vector *normal)
{
    t_vector    *on_unit_sphere;

    on_unit_sphere = random_in_unit_sphere();
    if (dot_vec(on_unit_sphere, normal) > 0.0)
        return (on_unit_sphere);
    return (vec_init(on_unit_sphere->x * -1, on_unit_sphere->y * -1, on_unit_sphere->z * -1));
}

double linear_to_gamma(double linear_component)
{
    if (linear_component > 0)
        return (sqrt(linear_component));
    return (0);
}

t_vector    *reflect(t_vector *vec1, t_vector *vec2)
{
    return (subtrac_vec_vec(vec1, multi_vec_doub(vec2, 2 * dot_vec(vec1, vec2))));
}
