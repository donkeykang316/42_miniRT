/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apago <apago@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:21:11 by kaan              #+#    #+#             */
/*   Updated: 2024/08/25 19:44:53 by apago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void    swap_double(double *a, double *b)
{
    double  temp;

    temp = *a;
    *a = *b;
    *b = temp;
}

typedef struct s_matrix {
    t_vec col0;
    t_vec col1;
    t_vec col2;
} t_matrix;

t_matrix identity() {
    t_matrix a;
    a.col0 = vec(1,0,0);
    a.col1 = vec(0,1,0);
    a.col2 = vec(0,0,1);
    return a;
}

t_matrix add_matrix_matrix(t_matrix a, t_matrix b) {
    t_matrix res;
    res.col0 = add_vec_vec(a.col0, b.col0);
    res.col1 = add_vec_vec(a.col1, b.col1);
    res.col2 = add_vec_vec(a.col2, b.col2);
    return res;
}

t_matrix mul_matrix_matrix(t_matrix a, t_matrix b) {
    t_matrix res;
    res.col0.x = a.col0.x * b.col0.x + a.col1.x * b.col0.y + a.col2.x * b.col0.z;
    res.col1.x = a.col0.x * b.col1.x + a.col1.x * b.col1.y + a.col2.x * b.col1.z;
    res.col2.x = a.col0.x * b.col2.x + a.col1.x * b.col2.y + a.col2.x * b.col2.z;

    res.col0.y = a.col0.y * b.col0.x + a.col1.y * b.col0.y + a.col2.y * b.col0.z;
    res.col1.y = a.col0.y * b.col1.x + a.col1.y * b.col1.y + a.col2.y * b.col1.z;
    res.col2.y = a.col0.y * b.col2.x + a.col1.y * b.col2.y + a.col2.y * b.col2.z;

    res.col0.z = a.col0.z * b.col0.x + a.col1.z * b.col0.y + a.col2.z * b.col0.z;
    res.col1.z = a.col0.z * b.col1.x + a.col1.z * b.col1.y + a.col2.z * b.col1.z;
    res.col2.z = a.col0.z * b.col2.x + a.col1.z * b.col2.y + a.col2.z * b.col2.z;
    return res;
}

t_matrix mul_matrix_double(t_matrix m, double d) {
    m.col0 = mul_vec_double(m.col0, d);
    m.col1 = mul_vec_double(m.col1, d);
    m.col2 = mul_vec_double(m.col2, d);
    return m;
}

t_matrix rotation_matrix(t_vec turn_vec, t_vec into_vec) {
    // https://math.stackexchange.com/questions/180418/calculate-rotation-matrix-to-align-vector-a-to-vector-b-in-3d

    t_vec v = cross_vec(turn_vec, into_vec);
    double s = length(v);
    double c = dot_vec(turn_vec, into_vec);

    t_matrix v_cross;
    v_cross.col0.x = 0;
    v_cross.col0.y = v.z;
    v_cross.col0.z = -v.y;
    v_cross.col1.x = -v.z;
    v_cross.col1.y = 0;
    v_cross.col1.z = v.x;
    v_cross.col2.x = v.y;
    v_cross.col2.y = -v.x;
    v_cross.col2.z = 0;

    t_matrix r = add_matrix_matrix(add_matrix_matrix(identity(), v_cross), mul_matrix_double(mul_matrix_matrix(v_cross, v_cross), (1-c)/pow(s,2)));
    return r;
}

t_vec mul_matrix_vec(t_matrix m, t_vec v) {
    return vec(
        m.col0.x*v.x + m.col1.x*v.y + m.col2.x*v.z,
        m.col0.y*v.x + m.col1.y*v.y + m.col2.y*v.z,
        m.col0.z*v.x + m.col1.z*v.y + m.col2.z*v.z
    );
}

bool root1(double a, double b, double c, double* root) {
    double d = b*b-4*a*c;
    if (d < 0)
        return false;
    *root = (-b-sqrt(d))/2/a;
    return true;
}

bool root2(double a, double b, double c, double* root) {
    double d = b*b-4*a*c;
    if (d < 0)
        return false;
    *root = (-b+sqrt(d))/2/a;
    return true;
}

t_hit render_caps(t_ray ray, t_object* obj, t_vec source_rotated, t_vec ray_hat_rotated, t_interval interval) {
    double delta = obj->value.cylinder.height/2;

    int i = 1;
    if (dot_vec(obj->value.cylinder.axis, ray.direction) > 0)
        i = -1;

    double vertical_speed = projection_length(normalize(ray.direction), obj->value.cylinder.axis);
    double vertical_distance  =projection_length(sub_vec_vec(obj->value.cylinder.center, ray.origin), obj->value.cylinder.axis) + delta*i;
    double times = vertical_distance / vertical_speed;
    if (times<0)
        return no_hit();

    t_vec intersection_2d = add_vec_vec(source_rotated, mul_vec_double(ray_hat_rotated, times));
    if (hypot(intersection_2d.x, intersection_2d.y) > obj->value.cylinder.radius) {
        return no_hit();
    }

    t_hit hit;
    hit.hit = true;
    hit.object = obj;
    hit.point = add_vec_vec(ray.origin, mul_vec_double(normalize(ray.direction), times));
    hit.distance = length(sub_vec_vec(hit.point, ray.origin));
    hit.normal = obj->value.cylinder.axis;
    if (dot_vec(hit.normal, ray.direction)>0)
        hit.normal = vec_neg(hit.normal);
    if (!surrounds(interval, hit.distance))
        return no_hit();
    return hit;
}

t_hit    ray_cast_cylinder(t_ray ray, t_interval interval, t_object* obj)
{
    (void)interval;
    t_vec ray_source_tick = sub_vec_vec(ray.origin, obj->value.cylinder.center);
    t_vec d_hat = normalize(obj->value.cylinder.axis);

    t_matrix R = rotation_matrix(d_hat, vec(0,0,1));
    t_vec ray_hat_rotated = mul_matrix_vec(R, normalize(ray.direction));
    t_vec source_rotated = mul_matrix_vec(R, ray_source_tick);


    double a = pow(ray_hat_rotated.x, 2) +pow(ray_hat_rotated.y, 2);
    double b = 2*(source_rotated.x*ray_hat_rotated.x+source_rotated.y*ray_hat_rotated.y);
    double c = pow(source_rotated.x,2)+pow(source_rotated.y,2)-pow(obj->value.cylinder.radius,2);

    double distance;
    if (!root1(a,b,c,&distance))
        return no_hit();
    if (distance <= 0)
        root2(a,b,c,&distance);
    if (distance <= 0)
        return no_hit();

    t_vec intersect_tick = vec(source_rotated.x + ray_hat_rotated.x*distance,source_rotated.y + ray_hat_rotated.y*distance,0);
    t_vec normal = mul_matrix_vec(rotation_matrix(vec(0,0,1), d_hat), intersect_tick);
    if (dot_vec(normal, ray.direction) > 0)
        normal = vec_neg(normal);

    t_hit hit;
    hit.hit = true;
    hit.object = obj;
    hit.point = add_vec_vec(ray.origin, mul_vec_double(normalize(ray.direction), distance));
    hit.distance = length(sub_vec_vec(hit.point, ray.origin));
    hit.normal = normalize(normal);

    if (hypot(obj->value.cylinder.radius, obj->value.cylinder.height/2) < length(sub_vec_vec(hit.point, obj->value.cylinder.center))) {
        return render_caps(ray, obj, source_rotated, ray_hat_rotated, interval);
    }
    if (!surrounds(interval, hit.distance))
            return no_hit();
    return (hit);
}
