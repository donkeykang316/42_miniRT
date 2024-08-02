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
    /*if (object_list->sphere)
    {
        rec->material = malloc(sizeof(t_material));
        rec->object_index = 0;
        while (object_list->sphere[i])
        {
            interval.min = ray_t.min;
            interval.max = closest_so_far;
            if (hit_sphere(ray, interval, rec, object_list->sphere[i]))
            {
                hit_anything = true;
                closest_so_far = rec->t;
                rec->object_index = i;
                rec->material->fuzz = object_list->sphere[i]->material->fuzz;
            }
            i++;
        }
    }*/
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
        i++;
    }
    return (hit_anything);
}