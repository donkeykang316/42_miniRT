/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 14:33:49 by kaan              #+#    #+#             */
/*   Updated: 2024/07/24 15:45:51 by kaan             ###   ########.fr       */
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
# include "lib/get_next_line/inc/get_next_line.h"
# include "lib/libft/inc/libft.h"

// linear congruential generator constants
#define RAND_A 1103515245
#define RAND_C 12345
#define RAND_M 2147483648

//pi
#define PI 3.1415926535897932385

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

typedef struct s_hit_rec
{
    t_vector    *p;
    t_vector    *normal;
    double      t;
    bool        front_face;
}   t_hit_rec;

typedef struct s_sphere
{
    t_vector    *center;
    double      radius;
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
void        write_color(t_vector *pixel_color);
t_vector    *ray_color(t_ray *ray, t_object_list *world);
void        render(t_camera *camera);

//render
void        secene_render(t_camera *camera);

//data init
void    camera_init(t_camera *camera);
void    world_init(t_object_list *world);

//objects
bool    hit_objects(t_ray *ray, t_interval *ray_t, t_hit_rec *rec, t_object_list *object_list);
bool    hit_sphere(t_ray *ray, t_interval *ray_t, t_hit_rec *rec, t_sphere *sphere);

//interval
double  size(t_interval *ray_t);
bool    contains(t_interval *ray_t, double x);
bool    surrounds(t_interval *ray_t, double x);
double  clamp(t_interval *ray_t, double x);

//vector init
t_vector	*vec_init(double x, double y, double z);

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

//util
int ft_rand();
double  random_double_a();
double  random_double(double min, double max);
double  degrees_to_radians(double degrees);

#endif