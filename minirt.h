/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 14:33:49 by kaan              #+#    #+#             */
/*   Updated: 2024/07/21 22:48:52 by kaan             ###   ########.fr       */
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

typedef struct s_img
{
    double  aspect_ratio;
    int     image_width;
    int     image_height;
} t_img;

typedef struct s_camera
{
    double  focal_length;
    double  viewport_height;
    double  viewport_width;
    double  *camera_center;
} t_camera;

//render prototype
void    simple_render();
void    alt_write_color(double *e);
void    alt_render();

//render 
void    render(t_img *image, t_camera *camera, double *pixel00_loc, double *pixel_delta_u, double *pixel_delta_v);


//struct init
void    img_init(t_img  *image);
void    camera_init(t_camera *camera);

//vector init
double	*vec_3d_init(double x, double y, double z);

//vector operation
double  *add_vec_vec(double *vec1, double *vec2);
double  *subtrac_vec_vec(double *vec1, double *vec2);
double  *multi_vec_vec(double *vec1, double *vec2);
double  *divi_vec_vec(double *vec1, double *vec2);
double  *add_vec_int(double *vec, int inte);
double  *subtrac_vec_int(double *vec, int inte);
double  *multi_vec_int(double *vec, int inte);
double  *divi_vec_int(double *vec, int inte);
double  *add_vec_doub(double *vec, double doub);
double  *subtrac_vec_doub(double *vec, double doub);
double  *multi_vec_doub(double *vec, double doub);
double  *divi_vec_doub(double *vec, double doub);

#endif