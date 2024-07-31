#include <stdio.h>
# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stdint.h>
# include <string.h>

typedef struct  s_vector
{
    double  x;
    double  y;
    double  z;
}   t_vector;

typedef struct s_ray
{
    t_vector    origin;
    t_vector    direction;
}   t_ray;

typedef struct s_sphere
{
    t_vector    oc;
    double      a;
    double      b;
    double      c;
}   t_sphere;

typedef struct s_camera
{
    double      aspect_ratio;
    int         image_width;
    int         image_height;
    double      focal_length;
    double      viewport_height;
    double      viewport_width;
    t_vector    viewport_u;
    t_vector    viewport_v;
    t_vector    pixel_delta_u;
    t_vector    pixel_delta_v;
    t_vector    viewport_upper_left;
    t_vector    pixel00_loc;
    t_vector    camera_center;
} t_camera;

void    ft_putstr_fd(char *s, int fd)
{
    write(fd, s, strlen(s));
}

void    ft_putdouble_fd(double n, int fd)
{
    char    c;
    int     precision = 6;

    // Handle negative numbers
    if (n < 0)
    {
        write(fd, "-", 1);
        n = -n;
    }

    // Extract and print integer part
    long long int_part = (long long)n;
    double fraction_part = n - int_part;

    if (int_part == 0)
        write(fd, "0", 1);
    else
    {
        // Recursive function to print each digit of integer part
        if (int_part >= 10)
            ft_putdouble_fd(int_part / 10, fd); // Use precision 0 here for recursive calls
        c = (int_part % 10) + '0';
        write(fd, &c, 1);
    }

    // If precision is zero, no need to print decimal point
    if (precision == 0)
        return;

    // Print decimal point
    write(fd, ".", 1);

    // Print fractional part up to specified precision
    while (precision-- > 0)
    {
        fraction_part *= 10;
        int digit = (int)fraction_part;
        c = digit + '0';
        write(fd, &c, 1);
        fraction_part -= digit;
    }
}

void    print_vector(t_vector v, int fd)
{
    ft_putstr_fd("x: ", fd);
    ft_putdouble_fd(v.x, fd);
    ft_putstr_fd("\ny: ", fd);
    ft_putdouble_fd(v.y, fd);
    ft_putstr_fd("\nz: ", fd);
    ft_putdouble_fd(v.z, fd);
    ft_putstr_fd("\n", fd);
}

t_vector	vec_init(double x, double y, double z)
{
    t_vector output;

    output.x = x;
    output.y = y;
    output.z = z;
    return (output);
}

t_vector  add_vec_vec(t_vector vec1, t_vector vec2)
{
    t_vector result;

    result.x = vec1.x + vec2.x;
    result.y = vec1.y + vec2.y;
    result.z = vec1.z + vec2.z;
    return (result);
}

t_vector  subtrac_vec_vec(t_vector vec1, t_vector vec2)
{
    t_vector result;

    result.x = vec1.x - vec2.x;
    result.y = vec1.y - vec2.y;
    result.z = vec1.z - vec2.z;
    return (result);
}

t_vector  multi_vec_vec(t_vector vec1, t_vector vec2)
{
    t_vector result;

    result.x = vec1.x * vec2.x;
    result.y = vec1.y * vec2.y;
    result.z = vec1.z * vec2.z;
    return (result);
}

t_vector  divi_vec_vec(t_vector vec1, t_vector vec2)
{
    t_vector result;

    result.x = vec1.x / vec2.x;
    result.y = vec1.y / vec2.y;
    result.z = vec1.z / vec2.z;
    return (result);
}

t_vector  add_vec_int(t_vector vec, int inte)
{
    t_vector result;

    result.x = vec.x + inte;
    result.y = vec.y + inte;
    result.z = vec.z + inte;
    return (result);
}

t_vector  subtrac_vec_int(t_vector vec, int inte)
{
    t_vector result;

    result.x = vec.x - inte;
    result.y = vec.y - inte;
    result.z = vec.z - inte;
    return (result);
}

t_vector  multi_vec_int(t_vector vec, int inte)
{
    t_vector result;

    result.x = vec.x * inte;
    result.y = vec.y * inte;
    result.z = vec.z * inte;
    return (result);
}

t_vector  divi_vec_int(t_vector vec, int inte)
{
    t_vector result;

    result.x = vec.x / inte;
    result.y = vec.y / inte;
    result.z = vec.z / inte;
    return (result);
}

t_vector  add_vec_doub(t_vector vec, double doub)
{
    t_vector result;

    result.x = vec.x + doub;
    result.y = vec.y + doub;
    result.z = vec.z + doub;
    return (result);
}

t_vector  subtrac_vec_doub(t_vector vec, double doub)
{
    t_vector result;

    result.x = vec.x - doub;
    result.y = vec.y - doub;
    result.z = vec.z - doub;
    return (result);
}

t_vector  multi_vec_doub(t_vector vec, double doub)
{
    t_vector result;

    result.x = vec.x * doub;
    result.y = vec.y * doub;
    result.z = vec.z * doub;
    return (result);
}

t_vector  divi_vec_doub(t_vector vec, double doub)
{
    t_vector result;

    result.x = vec.x / doub;
    result.y = vec.y / doub;
    result.z = vec.z / doub;
    return (result);
}

double  dot_vec(t_vector vec1, t_vector vec2)
{
    double  result;

    result = (vec1.x * vec2.x) + (vec1.y * vec2.y) + (vec1.z * vec2.z);
    return (result);
}

void    write_color(t_vector pixel_color)
{
    double  r;
    double  g;
    double  b;
    int     rbyte;
    int     gbyte;
    int     bbyte;

    r = pixel_color.x;
    g = pixel_color.y;
    b = pixel_color.z;

    rbyte = (int)(255.999 * r);
    gbyte = (int)(255.999 * g);
    bbyte = (int)(255.999 * b);
    printf("%d %d %d\n", rbyte, gbyte, bbyte);

}

void    camera_init(t_camera *camera)
{
    t_vector    vec;

    camera->aspect_ratio = 1;
    camera->image_width = 400;
    camera->image_height = (int)(camera->image_width / camera->aspect_ratio);
    if (camera->image_height < 1)
        camera->image_height = 1;
    camera->focal_length = 1.0;
    camera->viewport_height = 2.0;
    camera->viewport_width = camera->viewport_height * (double)(camera->image_width / camera->image_height);
    camera->camera_center = vec_init(0, 0, 0);
    vec = vec_init(0, 0, camera->focal_length);
    camera->viewport_u = vec_init(camera->viewport_width, 0, 0);
    camera->viewport_v = vec_init(0, -(camera->viewport_height), 0);
    camera->pixel_delta_u = divi_vec_int(camera->viewport_u, camera->image_width);
    camera->pixel_delta_v = divi_vec_int(camera->viewport_v, camera->image_height);
    camera->viewport_upper_left = subtrac_vec_vec(camera->camera_center, add_vec_vec(vec, add_vec_vec(divi_vec_int(camera->viewport_u, 2), divi_vec_int(camera->viewport_v, 2))));
    camera->pixel00_loc = add_vec_vec(camera->viewport_upper_left, multi_vec_doub(add_vec_vec(camera->pixel_delta_u, camera->pixel_delta_v), 0.5));
}

bool    hit_sphere(t_vector center, double radius, t_ray ray)
{
    t_sphere    sphere;
    double      discriminant;

    sphere.oc = subtrac_vec_vec(center, ray.origin);
    sphere.a = dot_vec(ray.direction, ray.direction);
    sphere.b = -2.0 * dot_vec(ray.direction, sphere.oc);
    sphere.c = dot_vec(sphere.oc, sphere.oc) - (radius * radius);
    discriminant = sphere.b * sphere.b - 4 * sphere.a * sphere.c;
    if (discriminant >= 0)
        return (true);
    return (false);
}

t_vector    ray_color(t_ray ray)
{
    t_vector    ray_color;
    t_vector    center;
    
    center = vec_init(0, 0, -1);
    if (hit_sphere(center, 0.5, ray))
    {
        ray_color = vec_init(1, 0, 0);
        return (ray_color);
    }
    return (ray_color = vec_init(0, 0, 0));
}

void    render()
{
    t_vector    pixel_center;
    t_vector    pixel_color;
    t_ray       ray;
    t_camera    camera;
    int         i;
    int         j;

    i = 0;
    j = 0;
    camera_init(&camera);
    ft_putstr_fd("aspect_ratio: ", 2);
    ft_putdouble_fd(camera.aspect_ratio, 2);
    ft_putstr_fd("\nimage_width: ", 2);
    ft_putdouble_fd(camera.image_width, 2);
    ft_putstr_fd("\nimage_height: ", 2);
    ft_putdouble_fd(camera.image_height, 2);
    ft_putstr_fd("\nfocal_length: ", 2);
    ft_putdouble_fd(camera.focal_length, 2);
    ft_putstr_fd("\ncamera_center: ", 2);
    print_vector(camera.camera_center, 2);
    ft_putstr_fd("\nviewport_height: ", 2);
    ft_putdouble_fd(camera.viewport_height, 2);
    ft_putstr_fd("\npixel00_loc: ", 2);
    print_vector(camera.pixel00_loc, 2);
    ft_putstr_fd("\nviewport_u: ", 2);
    print_vector(camera.viewport_u, 2);
    ft_putstr_fd("\npixel_delta_u: ", 2);
    print_vector(camera.pixel_delta_u, 2);
    ft_putstr_fd("\nviewport_v: ", 2);
    print_vector(camera.pixel_delta_v, 2);
    ft_putstr_fd("\nviewport_upper_left: ", 2);
    print_vector(camera.viewport_upper_left, 2);
    printf("P3\n%d %d\n255\n", (int)camera.image_width, (int)camera.image_height);
    while (j < camera.image_height)
    {
        i = 0;
        while (i < camera.image_width)
        {
            pixel_center = add_vec_vec(camera.pixel00_loc, add_vec_vec(multi_vec_int(camera.pixel_delta_u, i), multi_vec_int(camera.pixel_delta_v, j)));
            ray.direction = subtrac_vec_vec(pixel_center, camera.camera_center);
            ray.origin = vec_init(camera.camera_center.x, camera.camera_center.y, camera.camera_center.z);
            pixel_color = ray_color(ray);
            write_color(pixel_color);
            i++;
        }
        j++;
    }
}

int main()
{
    render();
}