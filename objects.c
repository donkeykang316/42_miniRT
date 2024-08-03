#include "minirt.h"

bool    hit_objects(t_ray ray, t_interval ray_t, t_hit_rec *rec, t_object_list **object)
{
    bool            hit_anything;
    t_interval      interval;
    double          closest_so_far;
    int             i;

    (void)rec;
    hit_anything = false;
    closest_so_far = ray_t.max;
    i = 0;
    rec->material = malloc(sizeof(t_material));
    while (object[i])
    {
        interval.min = ray_t.min;
        interval.max = closest_so_far;
        if (object[i]->type == QUAD)
        {
            if (hit_quad(ray, interval, rec, object[i]->quad))
            {
                hit_anything = true;
                closest_so_far = rec->t;
                rec->object_index = i;
                rec->material->fuzz = object[i]->quad->material->fuzz;
            }
        }
        else if (object[i]->type == TRIANGLE)
        {
            if (hit_tri(ray, interval, rec, object[i]->tri))
            {
                hit_anything = true;
                closest_so_far = rec->t;
                rec->object_index = i;
                rec->material->fuzz = object[i]->tri->material->fuzz;
            }
        }
        else if (object[i]->type == SPHERE)
        {
            if (hit_sphere(ray, interval, rec, object[i]->sphere))
            {
                hit_anything = true;
                closest_so_far = rec->t;
                rec->object_index = i;
                rec->material->fuzz = object[i]->sphere->material->fuzz;
            }
        }
        else if (object[i]->type == CYLINDER)
        {
            if (hit_cylinder(ray, interval, rec, object[i]->cyl))
            {
                hit_anything = true;
                closest_so_far = rec->t;
                rec->object_index = i;
                rec->material->fuzz = object[i]->cyl->material->fuzz;
            }
        }
        i++;
    }
    return (hit_anything);
}