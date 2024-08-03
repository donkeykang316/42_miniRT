#include "minirt.h"

bool    hit_cylinder(t_ray ray, t_interval ray_t, t_hit_rec *rec, t_cylinder *cylinder)
{
    t_vector    oc;
    t_vector    direction_ortho;
    t_vector    oc_ortho;
    t_vector    outward_normal;
    double      a;
    double      b;
    double      c;
    double      discriminant;
    double      root;
    t_vector    hit_point;
    double      projection_length;

    oc = subtrac_vec_vec(cylinder->center, ray.origin);
    direction_ortho = subtrac_vec_vec(multi_vec_doub(cylinder->axis, dot_vec(ray.direction, cylinder->axis)), ray.direction);
    oc_ortho = subtrac_vec_vec(multi_vec_doub(cylinder->axis, dot_vec(oc, cylinder->axis)), oc);
    a = length_squared(direction_ortho);
    b = dot_vec(direction_ortho, oc_ortho);
    c = length_squared(oc_ortho) - (cylinder->radius * cylinder->radius);
    discriminant = (b * b) - (a * c);
    if (discriminant < 0)
        return (false);
    root = (b - sqrt(discriminant)) / a;
    if (!surrounds(ray_t, root))
    {
        root = (b + sqrt(discriminant)) / a;
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