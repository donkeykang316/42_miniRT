#include "minirt.h"

typedef struct s_vector t_vector;
typedef struct s_camera t_camera;
typedef struct s_sphere t_sphere;
typedef struct s_material t_material;
typedef struct s_object_list t_object_list;
typedef struct s_ray t_ray;
typedef struct s_hit_rec t_hit_rec;
typedef struct s_quad t_quad;
typedef struct s_tri t_tri;
typedef struct s_cylinder t_cylinder;
typedef struct s_amblight t_amblight;
typedef struct s_light t_light;
typedef struct s_parser t_parser;

void    print_vector(t_vector v, int fd);
void    print_camera(t_camera camera, int fd);
void    print_sphere(t_sphere sphere, int fd);
void    print_quad(t_quad quad, int fd);
void    print_material(t_material material, int fd);
void    print_world(t_object_list **world, int fd);
void    print_ray(t_ray ray, int fd);
void    print_rec(t_hit_rec rec, int fd);
void    ft_putdouble_fd(double n, int fd);
void    print_parser(t_parser *parser, int fd);
void    print_light(t_light light, int fd);
void    print_amblight(t_amblight amblight, int fd);
void    print_cylinder(t_cylinder cylinder, int fd);
void    print_tri(t_tri tri, int fd);
