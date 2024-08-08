/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apago <apago@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 14:33:49 by kaan              #+#    #+#             */
/*   Updated: 2024/08/08 18:33:08 by apago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define KEY_ESC 65307

# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stdint.h>
# include "mlx.h"
# include "lib/get_next_line/inc/get_next_line.h"
# include "lib/libft/inc/libft.h"

#include "tester.h"

// linear congruential generator constants
#define A 1664525
#define C 1013904223
#define M 0xFFFFFFFF
#define EPSILON 1e-8

//pi
#define PI 3.1415926535897932385

//material types
typedef enum e_material_type
{
    LAMBERTIAN,
    METAL,
    DIELECTRIC
}   t_material_type;

typedef enum e_object_type
{
    SPHERE,
    QUAD,
    TRIANGLE,
    CUBE,
    CYLINDER
}   t_object_type;

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
    double      vfov;
    t_vector    lookfrom;
    t_vector    lookat;
    t_vector    vup;
    t_vector    pixel_delta_u;
    t_vector    pixel_delta_v;
    t_vector    center;
    t_vector    pixel00_loc;
} t_camera;

typedef struct s_ray
{
    t_vector    origin;
    t_vector    direction;
}   t_ray;

typedef struct s_material
{
    t_vector        albedo;
    double          fuzz;
    double          ref_idx;
    t_material_type type;
}   t_material;

typedef struct s_hit_rec
{
    t_vector    p;
    t_vector    normal;
    t_material *material;
    double      t;
    bool        front_face;
    int         object_index;
}   t_hit_rec;

typedef struct s_sphere
{
    t_vector    center;
    double      radius;
    t_material *material;
}   t_sphere;

typedef struct s_cylinder
{
    t_vector    center;
    t_vector    axis;
    double      radius;
    double      height;
    t_material  *material;
}   t_cylinder;

typedef struct  s_quad
{
    t_vector    q;
    t_vector    u;
    t_vector    v;
    t_vector    w;
    t_vector    normal;
    double      d;
    t_material  *material;
}   t_quad;

typedef struct  s_tri
{
    t_vector    q;
    t_vector    u;
    t_vector    v;
    t_vector    w;
    t_vector    normal;
    double      d;
    t_material  *material;
}   t_tri;

typedef struct s_object_list
{
    t_sphere        *sphere;
    t_quad          *quad;
    t_tri           *tri;
    t_cylinder      *cyl;
    t_object_type   type;
}   t_object_list;

typedef struct s_interval
{
    double  min;
    double  max;
}   t_interval;

typedef struct s_light
{
    t_vector    position;
    t_vector    albedo;
    double      intensity;
}   t_light;

typedef struct s_aabb
{
    t_interval  x;
    t_interval  y;
    t_interval  z;
}   t_aabb;

typedef struct s_image {
    int width;
    int height;
    t_vector* data;
} t_image;

typedef struct s_mlx_context {
	void				*mlx_context;
	void				*window;
	void				*mlx_image;
    char*               mlx_image_data;
	int					bits_per_px;
	int					big_endian;
	int					line_size;

    int width;
    int height;
    t_image image;
} t_mlx_context;

//camera
t_ray       get_ray(t_camera camera, int i, int j);
void        write_color(int fd, t_vector pixel_color);
void        render(t_camera camera, t_image image);

//ray color
t_vector    ray_color_util(t_ray scattered, t_hit_rec *rec, int depth, t_object_list **world);
t_vector    ray_quad(t_ray *ray, t_hit_rec *rec, int depth, t_object_list **world);
t_vector    ray_sphere(t_ray *ray, t_hit_rec *rec, int depth, t_object_list **world);
t_vector    ray_tri(t_ray *ray, t_hit_rec *rec, int depth, t_object_list **world);
t_vector    ray_color(t_ray *ray, t_hit_rec *rec, int depth, t_object_list **world);

//camera util
t_vector    random_in_unit_sphere(void);
t_vector    random_unit_vector(void);
t_vector    random_on_hemisphere(t_vector normal);
double      linear_to_gamma(double linear_component);

//data init
void    camera_init(t_camera *camera, int width, int height);
void    light_init(t_light *light);
void    world_init(t_object_list **world);

//sphere
bool    hit_sphere(t_ray ray, t_interval ray_t, t_hit_rec *rec, t_sphere *sphere);
double  find_root1(double discriminant, double h, double a);
double  find_root2(double discriminant, double h, double a);

//quad
bool    is_interior_quad(double alpha, double beta);
bool    hit_quad(t_ray ray, t_interval ray_t, t_hit_rec *rec, t_quad *quad);

//triangle
bool    is_interior_tri(double alpha, double beta);
bool    hit_tri(t_ray ray, t_interval ray_t, t_hit_rec *rec, t_tri *tri);

//cylinder
bool    hit_cylinder(t_ray ray, t_interval ray_t, t_hit_rec *rec, t_cylinder *cylinder);

//objects
bool    hit_objects(t_ray ray, t_interval ray_t, t_hit_rec *rec, t_object_list **object);
bool    obj_intersec(t_hit_rec *rec, double fuzz, double ref_idx, int i);

//material
bool    scatter_metal(t_ray *r_in, t_hit_rec *rec, t_vector attenuation, t_ray *scattered, t_material *material);
bool    scatter_lambertian(t_ray *r_in, t_hit_rec *rec, t_vector attenuation, t_ray *scattered, t_material *material);
bool    scatter_dieletric(t_ray *r_in, t_hit_rec *rec, t_vector attenuation, t_ray *scattered, t_material *material);
void    set_face_normal(t_ray r, t_vector outward_normal, t_hit_rec *rec);

//material util
t_vector    reflect(t_vector vec1, t_vector vec2);
double  reflectance(double cosine, double ref_idx);
double      fuzz(double fuzz);
t_vector    refract(t_vector uv, t_vector n, double etai_over_etat);

//interval
double  size(t_interval *ray_t);
bool    contains(t_interval *ray_t, double x);
bool    surrounds(t_interval ray_t, double x);
double  clamp(t_interval ray_t, double x);
t_interval  expand(double delta);

//aabb
double  *double_3(double x, double y, double z);
t_interval  axis_interval(t_aabb aabb, int n);
bool    hit_aabb(t_aabb aabb, t_ray ray, t_interval ray_t);

//vector init
t_vector	*vec_ptr_init(double x, double y, double z);
t_vector	vec_init(double x, double y, double z);
t_vector	*vec_free_init(t_vector *vec, double x, double y, double z);

//vector operation
t_vector    add_vec_vec(t_vector vec1, t_vector vec2);
t_vector    subtrac_vec_vec(t_vector vec1, t_vector vec2);
t_vector    multi_vec_vec(t_vector vec1, t_vector vec2);
t_vector    divi_vec_vec(t_vector vec1, t_vector vec2);
t_vector    add_vec_int(t_vector vec, int inte);
t_vector    subtrac_vec_int(t_vector vec, int inte);
t_vector    multi_vec_int(t_vector vec, int inte);
t_vector    divi_vec_int(t_vector vec, int inte);
t_vector    add_vec_doub(t_vector vec, double doub);
t_vector    subtrac_vec_doub(t_vector vec, double doub);
t_vector    multi_vec_doub(t_vector vec, double doub);
t_vector    divi_vec_doub(t_vector vec, double doub);
double      dot_vec(t_vector vec1, t_vector vec2);
t_vector    at_vec(t_ray ray, double t);
double      length_squared(t_vector vec);
double      vec_length(t_vector vec);
t_vector    unit_vector(t_vector vec);
t_vector    increment_vec_vec(t_vector vec_inc, t_vector vec);
t_vector    normalize_vec(t_vector vec);
t_vector    cross_vec(t_vector vec1, t_vector vec2);

//util
unsigned int ft_rand(void);

//random generator
double      random_double(void);
double      random_double_range(double min, double max);
double      degrees_to_radians(double degrees);
t_vector	random_vec(void);
t_vector    random_vec_range(double min, double max);


int						on_expose(t_mlx_context *ctx);
int						on_close_button(t_mlx_context *ctx);
int						on_key_up(int keycode, t_mlx_context *ctx);
int render_frame(t_mlx_context* ctx);
int	set_pixel(t_mlx_context *ctx, int x, int y, t_vector rgb);
void	setup_hooks(t_mlx_context *ctx);
int	init_mlx_context(t_mlx_context *ctx, int width, int height);

#endif
