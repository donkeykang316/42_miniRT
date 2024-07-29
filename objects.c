#include "minirt.h"

double  find_root1(double discriminant, double h, double a)
{
    double      sqrtd;
    double      root;

    sqrtd = sqrt(discriminant);
    root = (h - sqrtd) / a;
    return (root);
}

double  find_root2(double discriminant, double h, double a)
{
    double      sqrtd;
    double      root;

    sqrtd = sqrt(discriminant);
    root = (h + sqrtd) / a;
    return (root);
}

bool    hit_sphere(t_ray *ray, t_interval *ray_t, t_hit_rec *rec, t_sphere *sphere)
{
    t_vector    *oc;
    t_vector    *outward_normal;
    double      a;
    double      h;
    double      c;
    double      discriminant;
    double      root;

    oc = subtrac_vec_vec(sphere->center, ray->origin);
    a = length_squared(ray->direction);
    h = dot_vec(ray->direction, oc);
    c = length_squared(oc) - (sphere->radius * sphere->radius);
    discriminant = (h * h) - (a * c);
    if (discriminant < 0)
        return (false);
    root = find_root1(discriminant, h, a);
    if (!surrounds(ray_t, root))
    {
        root = find_root2(discriminant, h, a);
        if (!surrounds(ray_t, root))
            return (false);   
    }
    rec->t = root;
    rec->p = at_vec(ray, rec->t);
    rec->normal = divi_vec_doub(subtrac_vec_vec(rec->p, sphere->center), sphere->radius);
    outward_normal = divi_vec_doub(subtrac_vec_vec(rec->p, sphere->center), sphere->radius);
    set_face_normal(ray, outward_normal, rec);
    rec->material->albedo = vec_free_init(rec->material->albedo, sphere->material->albedo->x, sphere->material->albedo->y, sphere->material->albedo->z);
    return (true);
}

bool    hit_objects(t_ray *ray, t_interval *ray_t, t_hit_rec *rec, t_object_list *object_list)
{
    bool            hit_anything;
    t_interval      interval;
    double          closest_so_far;
    int             i;

    (void)rec;
    hit_anything = false;
    closest_so_far = ray_t->max;
    i = 0;
    if (object_list->t_sphere)
    {
        rec->material = malloc(sizeof(t_material));
        rec->material->albedo = malloc(sizeof(t_vector));
        while (object_list->t_sphere[i])
        {
            interval.min = ray_t->min;
            interval.max = closest_so_far;
            if (hit_sphere(ray, &interval, rec, object_list->t_sphere[i]))
            {
                hit_anything = true;
                closest_so_far = rec->t;
            }
            i++;
        }
    }
    return (hit_anything);
}