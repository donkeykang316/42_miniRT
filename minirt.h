/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 14:33:49 by kaan              #+#    #+#             */
/*   Updated: 2024/07/29 20:48:28 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stdint.h>
# include "lib/get_next_line/inc/get_next_line.h"
# include "lib/libft/inc/libft.h"

// linear congruential generator constants
#define A 1664525
#define C 1013904223
#define M 0xFFFFFFFF

//pi
#define PI 3.1415926535897932385

//material types
typedef enum e_material_type
{
    LAMBERTIAN,
    METAL,
    DIELECTRIC
}   t_material_type;

typedef struct s_vector
{
    double  x;
    double  y;
    double  z;
}   t_vector;

typedef struct s_camera
{
    double      aspect_ratio;
    int         image_width;
    int         samples_per_pixel;
    int         image_height;
    double      pixel_samples_scale;
    int         max_depth;
    t_vector    *pixel_delta_u;
    t_vector    *pixel_delta_v;
    t_vector    *center;
    t_vector    *pixel00_loc;
} t_camera;

typedef struct s_ray
{
    t_vector    *origin;
    t_vector    *direction;
}   t_ray;

typedef struct s_material
{
    t_vector        *albedo;
    t_material_type type;
}   t_material;

typedef struct s_hit_rec
{
    t_vector    *p;
    t_vector    *normal;
    t_material *material;
    double      t;
    bool        front_face;
    int         object_index;
}   t_hit_rec;

typedef struct s_sphere
{
    t_vector    *center;
    double      radius;
    t_material *material;
}   t_sphere;

typedef struct s_object_list
{
    t_sphere    **t_sphere;
}   t_object_list;

typedef struct s_interval
{
    double  min;
    double  max;
}   t_interval;

//camera
t_ray       *get_ray(t_camera *camera, int i, int j);
void        write_color(t_vector *pixel_color);
t_vector    *ray_color(t_ray *ray, int depth, t_object_list *world);
void        render(t_camera *camera);

//camera util
t_vector    *random_in_unit_sphere(void);
t_vector    *random_unit_vector(void);
t_vector    *random_on_hemisphere(t_vector *normal);
double      linear_to_gamma(double linear_component);

//render
void        secene_render(t_camera *camera);

//data init
void    camera_init(t_camera *camera);
void    world_init(t_object_list *world);

//objects
bool    hit_objects(t_ray *ray, t_interval *ray_t, t_hit_rec *rec, t_object_list *object_list);
bool    hit_sphere(t_ray *ray, t_interval *ray_t, t_hit_rec *rec, t_sphere *sphere);

//material
bool    scatter_dielectric(t_ray *r_in, t_hit_rec *rec, t_vector *attenuation,t_ray *scattered, t_material *material);
bool    scatter_metal(t_ray *r_in, t_hit_rec *rec, t_vector *attenuation,t_ray *scattered, t_material *material);
bool    scatter_lambertian(t_ray *r_in, t_hit_rec *rec, t_vector *attenuation,t_ray *scattered, t_material *material);
void    set_face_normal(t_ray *r, t_vector *outward_normal, t_hit_rec *rec);

//material util
t_vector    *reflect(t_vector *vec1, t_vector *vec2);
double      fmin(double x, double y);
t_vector    *refract(t_vector *uv, t_vector *n, double etai_over_etat);

//interval
double  size(t_interval *ray_t);
bool    contains(t_interval *ray_t, double x);
bool    surrounds(t_interval *ray_t, double x);
double  clamp(t_interval *ray_t, double x);

//vector init
t_vector	*vec_init(double x, double y, double z);
t_vector	*vec_free_init(t_vector *vec, double x, double y, double z);

//vector operation
t_vector    *add_vec_vec(t_vector *vec1, t_vector *vec2);
t_vector    *subtrac_vec_vec(t_vector *vec1, t_vector *vec2);
t_vector    *multi_vec_vec(t_vector *vec1, t_vector *vec2);
t_vector    *divi_vec_vec(t_vector *vec1, t_vector *vec2);
t_vector    *add_vec_int(t_vector *vec, int inte);
t_vector    *subtrac_vec_int(t_vector *vec, int inte);
t_vector    *multi_vec_int(t_vector *vec, int inte);
t_vector    *divi_vec_int(t_vector *vec, int inte);
t_vector    *add_vec_doub(t_vector *vec, double doub);
t_vector    *subtrac_vec_doub(t_vector *vec, double doub);
t_vector    *multi_vec_doub(t_vector *vec, double doub);
t_vector    *divi_vec_doub(t_vector *vec, double doub);
double      dot_vec(t_vector *vec1, t_vector *vec2);
t_vector    *at_vec(t_ray *ray, double t);
double      length_squared(t_vector *vec);
double      vec_length(t_vector *vec);
t_vector    *unit_vector(t_vector *vec);
t_vector    *increment_vec_vec(t_vector *vec_inc, t_vector *vec);
t_vector    *normalize_vec(t_vector *vec);
t_vector    *increment_vec_vec(t_vector *vec_inc, t_vector *vec);
double      fabs(double x);
bool        near_zero(t_vector *vec);

//util
unsigned int ft_rand(void);

//random generator
double  random_double(void);
double  random_double_range(double min, double max);
double  degrees_to_radians(double degrees);
t_vector	*random_vec(void);
t_vector    *random_vec_range(double min, double max);

//tester
void    print_vector(t_vector *v);

#endif