/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 14:33:49 by kaan              #+#    #+#             */
/*   Updated: 2024/07/23 14:40:28 by kaan             ###   ########.fr       */
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

typedef struct s_vector
{
    double  x;
    double  y;
    double  z;
}   t_vector;

typedef struct s_img
{
    double  aspect_ratio;
    int     image_width;
    int     image_height;
}   t_img;

typedef struct s_camera
{
    double      focal_length;
    double      viewport_height;
    double      viewport_width;
    t_vector    *camera_center;
} t_camera;

typedef struct s_viewport
{
    t_vector    *viewport_u;
    t_vector    *viewport_v;
    t_vector    *pixel_delta_u;
    t_vector    *pixel_delta_v;
    t_vector    *viewport_upper_left;
    t_vector    *pixel00_loc;
}   t_viewport;


typedef struct s_ray
{
    t_vector    *origin;
    t_vector    *direction;
}   t_ray;

/*typedef struct s_world
{
    t_vector    
}   t_world;*/

typedef struct s_sphere
{
    t_vector    *oc;
    double      a;
    double      b;
    double      c;
    double      h;
}   t_sphere;

//render
t_vector    *ray_color(t_ray *ray);
void        write_color(t_vector *pixel_color);
void        render(t_img *image, t_camera *camera, t_viewport *viewport);
void        secene_render(t_img *image, t_camera *camera, t_viewport *viewport);

//data init
void    image_init(t_img  *image);
void    camera_init(t_camera *camera, t_img *image);
void    viewport_init(t_viewport *viewport, t_img *image, t_camera *camera);

//hit function
double    hit_sphere(t_vector *center, double radius, t_ray *ray);

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

#endif