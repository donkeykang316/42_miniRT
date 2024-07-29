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
    outward_normal = divi_vec_doub(subtrac_vec_vec(rec->p, sphere->center), sphere->radius);
    set_face_normal(ray, outward_normal, rec);
    rec->material = sphere->material;
    return (true);
}

bool    hit_objects(t_ray *ray, t_interval *ray_t, t_hit_rec *rec, t_object_list *object_list)
{
    t_hit_rec       temp;
    bool            hit_anything;
    t_interval      interval;
    double          closest_so_far;
    int             i;

    (void)rec;
    hit_anything = false;
    closest_so_far = ray_t->max;
    interval.max = closest_so_far;
    interval.min = ray_t->min;
    i = 0;
    if (object_list->t_sphere)
    {
        while (object_list->t_sphere[i])
        {
            if (hit_sphere(ray, &interval, &temp, object_list->t_sphere[i]))
            {
                hit_anything = true;
                closest_so_far = temp.t;
                rec->front_face = temp.front_face;
                rec->normal = vec_init(temp.normal->x, temp.normal->y, temp.normal->z);
                //free(temp.normal);
                rec->p = vec_init(temp.p->x, temp.p->y, temp.p->z);
                //free(temp.p);
                rec->t = temp.t;
            }
            i++;
        }
    }
    return (hit_anything);
}