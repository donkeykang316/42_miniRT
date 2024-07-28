#include "minirt.h"

bool    scatter_material(t_ray *r_in, t_hit_rec *rec, t_vector *attenuation,t_ray *scattered, t_material *material)
{
    (void)r_in;
    (void)rec;
    (void)attenuation;
    (void)scattered;
    (void)material;
    return (false);
}

bool    scatter_lambertian(t_ray *r_in, t_hit_rec *rec, t_vector *attenuation,t_ray *scattered, t_lamertian *lamertian)
{
    t_vector    *scatter_direction;

    (void)attenuation;
    (void)r_in;
    scatter_direction = add_vec_vec(random_unit_vector(), rec->normal);
    if (near_zero(scatter_direction))
        scatter_direction = vec_init(rec->normal->x, rec->normal->y, rec->normal->z);
    scattered->origin = rec->p;
    scattered->direction = vec_init(scatter_direction->x, scatter_direction->y, scatter_direction->z);
    free(scatter_direction);
    attenuation = lamertian->albedo;
    return (true);
}

bool    scatter_metal(t_ray *r_in, t_hit_rec *rec, t_vector *attenuation,t_ray *scattered, t_metal *metal)
{
    t_vector    *reflected;

    (void)attenuation;
    reflected = reflect(r_in->direction, rec->normal);
    scattered->origin = rec->p;
    scattered->direction = reflected;
    attenuation = metal->albedo;
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
