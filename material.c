#include "minirt.h"

/*bool    scatter_dielectric(t_ray *r_in, t_hit_rec *rec, t_vector *attenuation,t_ray *scattered, t_material *material)
{
    t_vector    *unit_direction;
    double      ri;

    attenuation = vec_init(1.0, 1.0, 1.0);
    if (rec->front_face)
        ri = 1.0 / material->ref_idx;
    else
        ri = material->ref_idx;
    unit_direction = unit_vector(r_in->direction);
    scattered->origin = vec_init(rec->p->x, rec->p->y, rec->p->z);
    scattered->direction = refract(unit_direction, rec->normal, ri);
    return (true);
}*/

bool    scatter_lambertian(t_ray *r_in, t_hit_rec *rec, t_vector *attenuation,t_ray *scattered, t_material *material)
{
    t_vector    *scatter_direction;

    (void)attenuation;
    (void)r_in;
    scatter_direction = add_vec_vec(rec->normal, random_unit_vector());
    scattered->origin = vec_init(rec->p->x, rec->p->y, rec->p->z);
    scattered->direction = vec_init(scatter_direction->x, scatter_direction->y, scatter_direction->z);
    free(scatter_direction);
    attenuation = vec_init(material->albedo->x, material->albedo->y, material->albedo->z);
    return (true);
}

bool    scatter_metal(t_ray *r_in, t_hit_rec *rec, t_vector *attenuation,t_ray *scattered, t_material *material)
{
    t_vector    *reflected;

    (void)attenuation;
    reflected = reflect(r_in->direction, rec->normal);
    scattered->origin = vec_init(rec->p->x, rec->p->y, rec->p->z);
    scattered->direction = vec_init(reflected->x, reflected->y, reflected->z);
    attenuation = vec_init(material->albedo->x, material->albedo->y, material->albedo->z);
    return (true);
}

void    set_face_normal(t_ray *r, t_vector *outward_normal, t_hit_rec *rec)
{
    rec->front_face = dot_vec(r->direction, rec->normal) < 0;
    if (rec->normal->x < 0)
        outward_normal->x = -rec->normal->x;
    if (rec->normal->y < 0)
        outward_normal->y = -rec->normal->y;
    if (rec->normal->z < 0)
        outward_normal->z = -rec->normal->z;
}
