#include "minirt.h"

bool    is_interior(double alpha, double beta)
{
    t_interval  unit_interval;

    unit_interval.min = 0;
    unit_interval.max = 1;
    if (!contains(&unit_interval, alpha) || !contains(&unit_interval, beta))
        return (false);
    return (true);
}

bool    hit_quad(t_ray ray, t_interval ray_t, t_hit_rec *rec, t_quad *quad)
{
    t_vector    n;
    double      denom;
    double      t;
    t_vector    intersection;
    t_vector    planar_hitpt_vector;
    double      alpha;
    double      beta;

    n = cross_vec(quad->u, quad->v);
    quad->normal = unit_vector(n);
    quad->d = dot_vec(quad->normal, quad->q);
    quad->w = divi_vec_doub(n, length_squared(n));
    denom = dot_vec(quad->normal, ray.direction);
    if (fabs(denom) < EPSILON)
        return (false);
    t = (quad->d - dot_vec(quad->normal, ray.origin)) / denom;
    if (!contains(&ray_t, t))
        return (false);
    intersection = at_vec(ray, t);
    planar_hitpt_vector = subtrac_vec_vec(intersection, quad->q);
    alpha = dot_vec(quad->w, cross_vec(planar_hitpt_vector, quad->v));
    beta = dot_vec(quad->w, cross_vec(quad->u, planar_hitpt_vector));
    if (!is_interior(alpha, beta))
        return (false);
    rec->t = t;
    rec->p = vec_init(intersection.x, intersection.y, intersection.z); 
    rec->material->albedo = vec_init(quad->material->albedo.x, quad->material->albedo.y, quad->material->albedo.z);
    rec->material->fuzz = quad->material->fuzz;
    rec->material->type = quad->material->type;
    set_face_normal(ray, quad->normal, rec);
    return (true);
}