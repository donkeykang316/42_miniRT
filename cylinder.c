#include "minirt.h"

double  dot_vec_cyl(t_vector vec1, t_vector vec2)
{
    double  result;

    result = (vec1.x * vec2.x) + (vec1.z * vec2.z);
    return (result);
}

double  at_vec_cyl(t_ray ray, double t)
{
    double  result;

    result = ray.origin.y + (t * ray.direction.y);
    return (result);
}

bool    hit_cylinder(t_ray ray, t_interval ray_t, t_hit_rec *rec, t_cylinder *cylinder)
{
    //t_vector    outward_normal;
    double      a;
    double      h;
    double      c;
    double      discriminant;
    double      root;
    double      hit_point;

    (void)rec;

    a = dot_vec_cyl(ray.direction, ray.direction);
    cylinder->center = multi_vec_int(cylinder->center, -1);
    h = dot_vec_cyl(cylinder->center, ray.direction);
    c = dot_vec_cyl(cylinder->center, cylinder->center) - (cylinder->radius * cylinder->radius);
    discriminant = (h * h) - (a * c);
    if (discriminant < 0)
        return (false);
    root = (h - sqrt(discriminant)) / a;
    hit_point = at_vec_cyl(ray, root);
    if (hit_point < 0 || hit_point > cylinder->height)
        return (false);
    if (!surrounds(ray_t, root))
    {
        root = (h + sqrt(discriminant)) / a;
        hit_point = at_vec_cyl(ray, root);
        if (hit_point < 0 || hit_point > cylinder->height)
            return (false);
        if (!surrounds(ray_t, root))
            return (false);
    }
    /*rec->t = root;
    rec->p = vec_init(hit_point.x, hit_point.y, hit_point.z);
    rec->normal = divi_vec_doub(subtrac_vec_vec(rec->p, cylinder->center), cylinder->radius);
    outward_normal = unit_vector(subtrac_vec_vec(hit_point, add_vec_vec(cylinder->center, multi_vec_doub(cylinder->axis, projection_length))));
    set_face_normal(ray, outward_normal, rec);
    rec->material->albedo = vec_init(cylinder->material->albedo.x, cylinder->material->albedo.y, cylinder->material->albedo.z);*/
    rec->material->albedo = vec_init(cylinder->material->albedo.x, cylinder->material->albedo.y, cylinder->material->albedo.z);
    return (true);
}