#include "minirt.h"

typedef struct s_vector t_vector;
typedef struct s_camera t_camera;
typedef struct s_sphere t_sphere;
typedef struct s_material t_material;
typedef struct s_object_list t_object_list;
typedef struct s_ray t_ray;
typedef struct s_hit_rec t_hit_rec;
typedef struct s_quad t_quad;

void    print_vector(t_vector v);
void    print_camera(t_camera camera);
void    print_sphere(t_sphere sphere);
void    print_quad(t_quad quad);
void    print_material(t_material material);
void    print_world(t_object_list **world);
void    print_ray(t_ray ray);
void    print_rec(t_hit_rec rec);
void    ft_putdouble_fd(double n, int fd);
