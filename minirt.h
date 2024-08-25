/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apago <apago@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 14:33:49 by kaan              #+#    #+#             */
/*   Updated: 2024/08/25 20:00:14 by apago            ###   ########.fr       */
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

// linear congruential generator constants
# define A 1664525
# define C 1013904223
# define M 0xFFFFFFFF
# define EPSILON 1e-8

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}	t_vec;


typedef struct s_parser	t_parser;

typedef struct s_material
{
	t_vec	albedo;
}	t_material;

typedef enum e_object_type
{
	OBJECT_TYPE_NONE,
	OBJECT_TYPE_SPHERE,
	OBJECT_TYPE_CYLINDER,
	OBJECT_TYPE_PLANE
}	t_object_type;

typedef struct s_sphere
{
	t_vec	center;
	double	radius;
}	t_sphere;

typedef struct s_plane
{
	t_vec	point;
	t_vec	normal;
}	t_plane;

typedef struct s_cylinder
{
	t_vec	center;
	t_vec	axis;
	double	radius;
	double	height;
}	t_cylinder;

typedef struct s_object {
	t_object_type	type;
	union
	{
		t_sphere	sphere;
		t_plane		plane;
        t_cylinder cylinder;
	}	u_value;
	t_material		material;
}	t_object;

typedef struct s_hit
{
	bool		hit;
	t_vec		point;
	t_vec		normal;
	t_object	*object;
	double		distance;
}	t_hit;

typedef struct s_camera
{
	double	aspect_ratio;
	int		image_width;
	int		samples_per_pixel;
	int		image_height;
	double	pixel_samples_scale;
	int		max_depth;
	double	hfov;
	t_vec	lookfrom;
	t_vec	vup;
	t_vec	pixel_delta_u;
	t_vec	pixel_delta_v;
	t_vec	center;
	t_vec	pixel00_loc;
}	t_camera;

typedef struct s_camtmp
{
	double	focal_length;
	t_vec	viewport_u;
	t_vec	viewport_v;
	double	viewport_height;
	double	viewport_width;
	t_vec	viewport_upper_left;
	double	theta;
	double	h;
	t_vec	u;
	t_vec	v;
	t_vec	w;
}	t_camtmp;

typedef struct s_ray
{
	t_vec	origin;
	t_vec	direction;
}	t_ray;


typedef struct s_interval
{
	double	min;
	double	max;
}	t_interval;

typedef struct s_light
{
	t_vec	position;
	t_vec	color;
	double	intensity;
}	t_light;

typedef struct s_amblight
{
	double	intensity;
	t_vec	color;
}	t_amblight;

typedef struct s_aabb
{
	t_interval	x;
	t_interval	y;
	t_interval	z;
}	t_aabb;

typedef struct s_image
{
	int		width;
	int		height;
	t_vec	*data;
}	t_image;

typedef struct s_camera_spec
{
	t_vec	view_point;
	t_vec	direction;
	double	hfov;
}	t_camera_spec;

typedef struct s_world
{
	int				point_lights_len;
	int				objects_len;
	t_light			*point_lights;
	t_amblight		ambient_light;
	t_object		*objects;
	t_camera_spec	camera;
}	t_world;

typedef struct s_mlx_context
{
	void		*mlx_context;
	void		*window;
	void		*mlx_image;
	char		*mlx_image_data;
	int			bits_per_px;
	int			big_endian;
	int			line_size;
	int			width;
	int			height;
	t_image		sum;
	int			samples;
	int			start_time;
	t_camera	camera;
	t_world		*world;
}	t_mlx_context;

typedef struct s_readtmp
{
	int		fd;
	int		len;
	int		cap;
	char	*res;
	int		rd;
	char	*newres;
}	t_readtmp;

typedef struct s_parsedoubtmp
{
	int		parsed;
	int		whole;
	int		fraction;
	char	*sc;
	int		minus;
	int		decimal_places;
}	t_parsedoubtmp;

typedef struct s_smpphong
{
	double	em;
	double	es;
	t_vec	n;
	t_vec	lambert;
	t_vec	r;
	t_vec	specular;
}	t_smpphong;

typedef struct s_licotmp
{
	int				i;
	t_vec			res;
	t_light			*light;
	t_ray			light_ray;
	t_hit			obstacle;
	t_interval		interval;
	double			r_px ;
	double			intensity;
	double			point_brdf;
}	t_licotmp;

typedef struct s_raytracetmp
{
	t_interval	interval;
	t_hit		hit;
	t_vec		lighting;
	t_ray		secondary_ray;
	t_vec		to_reflect;
	t_vec		reflected;
}	t_raytracetmp;

typedef struct s_raycassphtmp
{
	t_vec	oc;
	double	a;
	double	h;
	double	c;
	double	discriminant;
	double	root;
	t_vec	hit_point;
}	t_raycassphtmp;


int				error_msg(char *msg);
double			angle_between(t_vec a, t_vec b);
double			cos_angle_between(t_vec a, t_vec b);
int				parse_world(char *scene, t_world *world);

//camera
t_ray			get_ray(t_camera camera, int i, int j);
void			render(t_world *world, t_camera camera, t_image image);
t_vec			gamma_correct(t_vec pixel_color);

//camera util
void			write_color(int fd, t_vec pixel_color);
t_vec			random_in_unit_sphere(void);
t_vec			random_normalize_vec(void);
t_vec			random_on_hemisphere(t_vec normal);
double			linear_to_gamma(double linear_component);

//data init
void			camera_init(t_camera *camera,
					t_camera_spec spec, int width, int height);
t_object		*world_init(void);

void			print_world(t_world *world);

t_hit			hit_object(t_object *object,
					double distance, t_vec point, t_vec normal);

//sphere
double			find_root1(double discriminant, double h, double a);
double			find_root2(double discriminant, double h, double a);
t_hit			ray_cast_sphere(t_ray ray,
					t_interval interval, t_object *object);
t_hit ray_cast_cylinder(t_ray ray, t_interval interval, t_object* obj);
//cylinder

//plane
t_hit			ray_cast_plane(t_ray ray,
					t_interval interval, t_object *object);

//render
t_hit			no_hit(void);
t_hit			hit_object(t_object *object,
					double distance, t_vec point, t_vec normal);
t_hit			ray_cast_at(t_ray ray, t_interval interval, t_object *object);
t_hit			ray_cast(t_ray ray, t_interval interval, t_world *world);
double			brdf(t_vec incident, t_vec reflected, t_vec normal);

//render util
t_vec			sample_phong_brdf(t_vec incident, t_vec normal);
t_ray			new_ray(t_vec origin, t_vec direction);
t_ray			ray_from_to(t_vec from, t_vec to);
t_vec			lighting_color(t_ray ray, t_hit hit, t_world *world);
t_vec			ray_trace(t_ray ray, int depth, t_world *world);

// light
void			light_init(t_light *light);
t_vec			ambient_light(t_amblight light);
double			projection_length(t_vec of, t_vec onto);
t_vec			projection(t_vec of, t_vec onto);

//material util
t_vec			reflect(t_vec vec1, t_vec vec2);
double			reflectance(double cosine, double ref_idx);
double			fuzz(double fuzz);
t_vec			refract(t_vec uv, t_vec n, double etai_over_etat);

//interval
double			size(t_interval *ray_t);
bool			contains(t_interval *ray_t, double x);
bool			surrounds(t_interval ray_t, double x);
double			clamp(t_interval ray_t, double x);
t_interval		expand(double delta);

//vector init
t_vec			vec(double x, double y, double z);

//vector operation
t_vec			vec_neg(t_vec v);
t_vec			add_vec_vec(t_vec vec1, t_vec vec2);
t_vec			sub_vec_vec(t_vec vec1, t_vec vec2);
t_vec			mul_vec_vec(t_vec vec1, t_vec vec2);
t_vec			div_vec_vec(t_vec vec1, t_vec vec2);
t_vec			add_vec_int(t_vec vec, int inte);
t_vec			sub_vec_int(t_vec vec, int inte);
t_vec			mul_vec_int(t_vec vec, int inte);
t_vec			div_vec_int(t_vec vec, int inte);
t_vec			add_vec_double(t_vec vec, double doub);
t_vec			sub_vec_double(t_vec vec, double doub);
t_vec			mul_vec_double(t_vec vec, double doub);
t_vec			div_vec_double(t_vec vec, double doub);
double			dot_vec(t_vec vec1, t_vec vec2);
t_vec			at_ray(t_ray ray, double t);
double			length_squared(t_vec vec);
double			length(t_vec vec);
t_vec			normalize(t_vec vec);
t_vec			cross_vec(t_vec vec1, t_vec vec2);

//util
unsigned int	ft_rand(void);

//random generator
double			random_double(void);
double			random_double_range(double min, double max);
double			degrees_to_radians(double degrees);
t_vec			random_vec(void);
t_vec			random_vec_range(double min, double max);

//mlx
int				on_expose(t_mlx_context *ctx);
int				on_close_button(t_mlx_context *ctx);
int				on_key_up(int keycode, t_mlx_context *ctx);
int				render_frame(t_mlx_context *ctx);
int				set_pixel(t_mlx_context *ctx, int x, int y, t_vec rgb);
void			setup_hooks(t_mlx_context *ctx);
int				init_mlx_context(t_mlx_context *ctx, int width, int height);
void			display_image(t_mlx_context *ctx);
void			debug_info(t_mlx_context *ctx);

//hooks util
void			reset_context(t_mlx_context *ctx);
void			handle_key_w(t_mlx_context *ctx);
void			handle_key_s(t_mlx_context *ctx);
void			handle_key_a(t_mlx_context *ctx);
void			handle_key_d(t_mlx_context *ctx);


//parser
t_material		default_material(void);
int				parse_char(char	**scene, char c, int *total);
int				parse_space(char **scene, int *total);
int				parse_whitespace(char **scene, int *total);
int				parse_decimal(char **scene, int *dst, int *total);

//parser util 1
int				parse_double(char **scene, double *flt, int *total);
int				parse_byte(char **scene, int *byte, int *total);
int				parse_color(char **scene, t_vec *clr, int *total);
int				parse_vector(char **scene, t_vec *vec, int *total);

//parser util 2
int				parse_ambient_light(char **_scene,
					t_amblight *light, int *total);
int				parse_camera(char **_scene, t_camera_spec *camera, int *total);
void			add_light(t_world *world, t_light light);
void			add_object(t_world *world, t_object object);

//parser util 3
int				parse_light(char **_scene, t_world *world, int *total);
int				parse_string(char **scene, char *str, int *total);
int				parse_sphere(char **_scene, t_world *world, int *total);
int				parse_cylinder(char **_scene, t_world *world, int *total);

//parser util 4
int				parse_plane(char **_scene, t_world *world, int *total);
int				parse_world(char *scene, t_world *world);
double			make_double(int whole, int fraction, int position);

//read file
int				open_file_and_init(t_readtmp *tmp, char *name);
int				expand_buffer(t_readtmp *tmp);
int				read_file_content(t_readtmp *tmp);
void			cleanup_on_error(t_readtmp *tmp);
char			*read_file(char *name);


# define PHONG_MAX_ANGLE 0.1
# define PHONG_GLOSS 0.5

#endif
