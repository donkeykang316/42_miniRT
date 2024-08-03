#include "minirt.h"

double  dot_vec_cyl(t_vector vec1, t_vector vec2)
{
    double  result;

    result = (vec1.x * vec2.x) + (vec1.y * vec2.y);
    return (result);
}

bool    hit_cylinder(t_ray ray, t_interval ray_t, t_hit_rec *rec, t_cylinder *cylinder)
{
    t_vector    oc;
    t_vector    outward_normal;
    double      a;
    double      h;
    double      c;
    double      discriminant;
    double      root;
    t_vector    hit_point;
    double      projection_length;

    oc = subtrac_vec_vec(cylinder->center, ray.origin);
    a = dot_vec_cyl(ray.direction, ray.direction) - pow(dot_vec_cyl(ray.direction, cylinder->axis), 2);
    h = dot_vec_cyl(oc, ray.direction) - (dot_vec_cyl(oc, cylinder->axis) * dot_vec_cyl(ray.direction, cylinder->axis));
    c = dot_vec_cyl(oc, oc) - pow(dot_vec_cyl(oc, cylinder->axis), 2) - (cylinder->radius * cylinder->radius);
    discriminant = (h * h) - (a * c);
    if (discriminant < 0)
        return (false);
    root = (h - sqrt(discriminant)) / a;
    if (!surrounds(ray_t, root))
    {
        root = (h + sqrt(discriminant)) / a;
        if (!surrounds(ray_t, root))
            return (false);
    }
    hit_point = at_vec(ray, root);
    projection_length = dot_vec(subtrac_vec_vec(hit_point, cylinder->center), cylinder->axis);
    if (projection_length < 0 || projection_length > cylinder->height)
        return (false);
    rec->t = root;
    rec->p = vec_init(hit_point.x, hit_point.y, hit_point.z);
    outward_normal = unit_vector(subtrac_vec_vec(hit_point, add_vec_vec(cylinder->center, multi_vec_doub(cylinder->axis, projection_length))));
    set_face_normal(ray, outward_normal, rec);
    rec->material->albedo = vec_init(cylinder->material->albedo.x, cylinder->material->albedo.y, cylinder->material->albedo.z);
    return (true);
}